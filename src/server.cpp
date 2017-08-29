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
#include "FifoCommunicator.h"



const char* toServerFifoName = "/tmp/to_server";
const char* fromServerFifoName = "/tmp/from_server";



void handleSignal(int) {
   std::cout << "Shutdown server..." << std::endl;
   unlink(toServerFifoName);
   unlink(fromServerFifoName);
   exit(0);
}



void send(void* data, size_t numBytes)
{
   int fd_write = open(fromServerFifoName, O_WRONLY);
   write(fd_write, data, numBytes);
   close(fd_write);
}



void receive(void* buffer, size_t numBytes)
{
   int fd_read = open(toServerFifoName, O_RDONLY);
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




class Server : public FifoCommunicator
{
   public:
      Server(const std::string& toServerFifoName, const std::string& fromServerFifoName);
      ~Server();

   public:
      void run();

   private:
      void handleStoreRequest(const Request& request);
      void handleRetrieveRequest(const Request& request);

   private:
      std::map<std::string, BinaryBlob*> m_store;
};



Server::Server(const std::string& toServerFifoName, const std::string& fromServerFifoName) :
   FifoCommunicator(fromServerFifoName, toServerFifoName)
{
   signal(SIGINT, handleSignal);

   mkfifo(toServerFifoName.c_str(), 0666);
   mkfifo(fromServerFifoName.c_str(), 0666);
}



Server::~Server()
{
}



void Server::run()
{
   while (true)
   {
      std::cout << "INFO: in main loop... Waiting for request." << std::endl;

      std::unique_ptr<Request> request(receiveObj<Request>());

      if (request->isStoreRequest())
      {
         handleStoreRequest(*request);
      }
      else if (request->isRetrieveRequest())
      {
         handleRetrieveRequest(*request);
      }
      else
      {
         std::cout << "Server::run(): error 1" << std::endl;
      }
   }
}



void Server::handleStoreRequest(const Request& request)
{
   std::cout << "INFO: in handleStoreRequest()..." << std::endl;

   auto key = request.getKey();

   std::cout << "Key = '" << key << "'" << std::endl;

   /// Acknowledge
   sendObj<Response>(Response::responseAcknowledge());

   /// Receive blob
   BinaryBlob* blob = receiveBinaryBlob(request.getNumBytes());

   /// Store blob
   m_store[key] = blob;
}



void Server::handleRetrieveRequest(const Request& request)
{
   std::cout << "INFO: in handleRetrieveRequest()..." << std::endl;

   /// Get blob
   auto key = request.getKey();
   if (m_store.find(key) == m_store.end())
   {
      std::cout << "WARNING: Key not found." << std::endl;
      sendObj<Response>(Response::keyNotFound());
      return;
   }
   BinaryBlob* blob = m_store[key];

   /// Announce how many bytes will be send
   sendObj<Response>(Response::announceMessage(blob->getSize()));

   /// Wait for acknowledgement
   std::unique_ptr<Response> response(receiveObj<Response>());
   if (response->getType() != Response::ACKNOWLEDGE)
   {
      std::cout << "WARNING: No acknowledgement received." << std::endl;
      return;
   }

   /// Send blob
   sendBinaryBlob(*blob);
}



int main()
/// Comments
{

   Server server(toServerFifoName, fromServerFifoName);
   server.run();

   return 0;
}



int oldMain()
{
   std::map<std::string, BinaryBlob*> store;

   // commented out code
   signal(SIGINT, handleSignal);

   mkfifo(toServerFifoName, 0666);
   mkfifo(fromServerFifoName, 0666);

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
            std::cout << "No acknowledge received!" << std::endl;
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
