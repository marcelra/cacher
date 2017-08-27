#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cassert>

#include "Response.h"
#include "Request.h"



const char* to_server_fifo_name   = "/tmp/to_server";
const char* from_server_fifo_name = "/tmp/from_server";



void send(void* data, size_t numBytes)
{
   int fd_write = open(to_server_fifo_name, O_WRONLY);
   write(fd_write, data, numBytes);
   close(fd_write);
}



void receive(void* buffer, size_t numBytes)
{
   int fd_read = open(from_server_fifo_name, O_RDONLY);
   read(fd_read, buffer, sizeof(Request));
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

         std::cout << "Value: " << std::endl;
         std::getline(std::cin, value);

         auto request = Request::store(key, value.length());
         std::cout << "Sending request " << request << std::endl;

         /// Send request
         sendObj<Request>(request);

         /// Receive acknowledgement
         auto response = receiveObj<Response>();
         std::cout << "Received response: " << response << std::endl;

         if (response.getType() == Response::ACKNOWLEDGE)
         {
            std::cout << "Sending data..." << std::endl;
            send(const_cast<char*>(value.c_str()), value.length());
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

            char message[numBytes + 1];
            receive(message, numBytes);

            message[numBytes] = 0;

            std::cout << "Received message: '" << std::string(message) << "'" << std::endl;
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

      // auto request = Request::store(buf.length());
      // fd_write = open(to_server_fifo_name, O_WRONLY);
      // write(fd_write, &request, sizeof(request));

      // Response response;
      // fd_read = open(from_server_fifo_name, O_RDONLY);
      // read(fd_read, &response, sizeof(response));
      // close(fd_read);

      // std::cout << "Response from server: " << response << std::endl;

      // if (response.getType() == Response::ACKNOWLEDGE)
      // {
      //    fd_write = open(to_server_fifo_name, O_WRONLY);
      //    write(fd_write, buf.c_str(), buf.length());
      //    close(fd_write);
      // }
      // else
      // {
      //    assert(false);
      // }


      // char read_buf[1024];
      // fd_read = open(from_server_fifo_name, O_RDONLY);
      // read(fd_read, read_buf, 1024);
      // close(fd_read);

      // std::cout << "Server responded: " << std::endl;
      // std::cout << read_buf << std::endl;
   }
}
