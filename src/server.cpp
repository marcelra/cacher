#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <csignal>

#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <cassert>

#include "IBinarySerializable.h"
#include "Request.h"
#include "Response.h"
#include "SerializableRealVector.h"
#include "Utils.h"



const char* to_server_fifo_name = "/tmp/to_server";
const char* from_server_fifo_name = "/tmp/from_server";



std::string to_upper(const std::string& str) {
   std::string result = str;

   for (size_t i = 0; i < str.size(); ++i) {
      result[i] = std::toupper(str[i]);
   }

   return result;
}



void startup() {
   std::cout << "Starting server..." << std::endl;
   mkfifo(to_server_fifo_name, 0666);
   mkfifo(from_server_fifo_name, 0666);
}



void shutdown() {
   std::cout << "Shutdown server..." << std::endl;
   unlink(to_server_fifo_name);
   unlink(from_server_fifo_name);
   exit(0);
}



void handleSignal(int) {
   shutdown();
}



void send(void* data, size_t numBytes)
{
   int fd_write = open(from_server_fifo_name, O_WRONLY);
   write(fd_write, data, numBytes);
   close(fd_write);
}



void receive(void* buffer, size_t numBytes)
{
   int fd_read = open(to_server_fifo_name, O_RDONLY);
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



int main()
/// Comments
{

   std::map<std::string, BinaryBlob*> store;

   // commented out code
   signal(SIGINT, handleSignal);

   mkfifo(to_server_fifo_name, 0666);
   mkfifo(from_server_fifo_name, 0666);

   int fd_read;
   int fd_write;

   while (true)
   {
      std::cout << "Server running..." << std::endl;


      /// Wait for request
      auto request = receiveObj<Request>();
      std::cout << "Received request " << request << std::endl;

      if (request.isStoreRequest())
      {
         auto key = request.getKey();

         std::cout << "Key = '" << key << "'" << std::endl;

         /// Acknowledge
         sendObj<Response>(Response::responseAcknowledge());


         /// Retrieve message
         char* msg = new char[request.getNumBytes()];
         receive(msg, request.getNumBytes());

         // std::cout << "Raw data received:" << std::endl;
         // Utils::binaryDump(msg, request.getNumBytes());

         BinaryBlob* blob = new BinaryBlob(msg, request.getNumBytes());

         std::cout << "Storing with key '" << key << "'" << std::endl;
         store[key] = blob;

         std::cout << "Store contents: " << std::endl;
         for(auto it = store.begin();
             it != store.end(); ++it)
         {
             std::cout << it->first << ": chunck of " << it->second->getSize() << std::endl;
         }
      }
      else if (request.isRetrieveRequest())
      {
         std::cout << "Store contents: " << std::endl;
         for(auto it = store.begin();
             it != store.end(); ++it)
         {
             std::cout << it->first << ": chunck of " << it->second->getSize() << std::endl;
         }

         auto key = request.getKey();
         std::cout << "Key here = '" << key << "'" << std::endl;


         if (store.find(key) == store.end())
         {
            std::cout << "WARNING: KEY NOT FOUND" << std::endl;
            sendObj<Response>(Response::keyNotFound());

            continue;
         }

         BinaryBlob* message = store[key];

         sendObj<Response>(Response::announceMessage(message->getSize()));

         auto response = receiveObj<Response>();
         std::cout << "Received response: " << response << std::endl;
         if (response.getType() == Response::ACKNOWLEDGE)
         {
            std::cout << "Sending " << message->getSize() << " bytes..." << std::endl;

            send((void*)(message->getData()), message->getSize());
         }
         else
         {
            std::cout << "Not sending data!" << std::endl;
         }
      }
      else
      {
         sendObj<Response>(Response::responseNotOk());
         std::cout << "Not a valid request received." << std::endl;
         continue;
      }
   }

   return 0;
}
