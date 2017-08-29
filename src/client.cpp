#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cassert>
#include <vector>

#include "Response.h"
#include "Request.h"
#include "SerializableRealVector.h"
#include "Utils.h"



const char* toServerFifoName   = "/tmp/to_server";
const char* fromServerFifoName = "/tmp/from_server";



void send(void* data, size_t numBytes)
{
   int fd_write = open(toServerFifoName, O_WRONLY);
   write(fd_write, data, numBytes);
   close(fd_write);
}



void receive(void* buffer, size_t numBytes)
{
   int fd_read = open(fromServerFifoName, O_RDONLY);
   read(fd_read, buffer, numBytes);
   close(fd_read);
}



template<class T> void sendObj(const T& obj)
{
   send(const_cast<T*>(&obj), sizeof(T));
}



template<class T> T receiveObj()
{
   T obj;
   receive(&obj, sizeof(T));
   return obj;
}



std::vector<double> generateVector(size_t length)
{
   auto result = std::vector<double>(length);
   for (size_t i = 0; i < length; ++i)
   {
      result[i] = i;
   }
   return result;
}



int main()
{
   std::cout << "Started" << std::endl;

   while (true)
   {
      std::string cmd;
      std::cout << "Command: STORE or RETRIEVE:" << std::endl;
      std::getline(std::cin, cmd);

      if (cmd == "STORE")
      {
         std::string key;
         std::string value;

         std::cout << "Key: " << std::endl;
         std::getline(std::cin, key);

         int length = 0;
         while (true)
         {
            std::cout << "Length of vector: " << std::endl;
            std::getline(std::cin, value);
            length = atoi(value.c_str());

            if (length > 0)
               break;
         }

         std::vector<double>&& vector = generateVector(length);
         SerializableRealVector srv(vector);
         BinaryBlob&& blob = srv.toBinaryBlob();

         auto request = Request::store(key, blob.getSize());
         std::cout << "Sending request " << request << std::endl;

         /// Send request
         sendObj<Request>(request);

         /// Receive acknowledgement
         auto response = receiveObj<Response>();
         std::cout << "Received response: " << response << std::endl;

         if (response.getType() == Response::ACKNOWLEDGE)
         {
            std::cout << "Sending data..." << std::endl;
            send((void*)(blob.getData()), blob.getSize());
         }
         else
         {
            std::cout << "ERROR 1" << std::endl;
         }

      }
      else if (cmd == "RETRIEVE")
      {
         std::string key;

         std::cout << "Key: " << std::endl;
         std::getline(std::cin, key);

         auto request = Request::retrieve(key);
         std::cout << "Sending request " << request << std::endl;
         sendObj<Request>(request);

         auto response = receiveObj<Response>();
         std::cout << "Received response: " << response << std::endl;
         if (response.getType() == Response::ANNOUNCE)
         {
            size_t numBytes = response.getNumBytesMessage();

            std::cout << "Sending acknowledge..." << std::endl;
            sendObj<Response>(Response::responseAcknowledge());

            char* message = new char[numBytes];
            receive(message, numBytes);

            std::cout << "Message read, building blob" << std::endl;
            BinaryBlob blob(message, numBytes);
            SerializableRealVector srv(blob);
            blob.clearData();

            std::cout << "Received vector of size " << srv.vec.size()
                      << " with last element '" << srv.vec.back() << "'" << std::endl;

         }
         else if (response.getType() == Response::KEY_NOT_FOUND)
         {
            std::cout << "Server responded that key was not found." << std::endl;
            continue;
         }
         else
         {
            std::cout << "ERROR 2" << std::endl;
         }

      }
   }
}
