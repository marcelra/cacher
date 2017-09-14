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
#include "FifoCommunicator.h"
#include "Utils.h"
#include "Exceptions.h"
#include "BinaryBlob.h"


const char* toServerFifoName   = "/tmp/to_server";
const char* fromServerFifoName = "/tmp/from_server";



class Client : public FifoCommunicator
{
   public:
      Client(const std::string& toServerFifoName, const std::string& fromServerFifoName);
      ~Client();

   private:
      Client& operator=(const Client& other);
      Client(const Client& other);

   public:
      void store(const IBinarySerializable& object, const std::string& key);
      template<class T> T retrieve(const std::string& key);

   public:
      void run();
      void interactiveStore();
      void interactiveRetrieve();
      std::vector<double> generateVector(size_t length);
};



void Client::store(const IBinarySerializable& object, const std::string& key)
{
   BinaryBlob blob;
   object.streamToBlob(blob);

   Request request = Request::store(key, blob.getSize());
   std::cout << "Sending request " << request << std::endl;

   /// Send request
   sendObj<Request>(request);


   /// Receive acknowledgement
   auto response = std::unique_ptr<Response>(receiveObj<Response>());
   std::cout << "Received response: " << *response << std::endl;

   if (response->getType() == Response::ACKNOWLEDGE)
   {
      std::cout << "Sending data..." << std::endl;
      sendBinaryBlob(blob);
   }
   else
   {
      std::cout << "ERROR 1" << std::endl;
   }

}



template<class T> T Client::retrieve(const std::string& key)
{
   auto request = Request::retrieve(key);
   std::cout << "Sending request " << request << std::endl;
   sendObj<Request>(request);

   std::unique_ptr<Response> response(receiveObj<Response>());
   std::cout << "Received response: " << *response << std::endl;

   if (response->getType() == Response::ANNOUNCE)
   {
      size_t numBytes = response->getNumBytesMessage();
      std::cout << "Sending acknowledge..." << std::endl;
      sendObj<Response>(Response::responseAcknowledge());

      BinaryBlob* blob = receiveBinaryBlob(numBytes);
      T result(*blob);
      delete blob;
      return result;
   }
   else if (response->getType() == Response::KEY_NOT_FOUND)
   {
      std::cout << "Server responded that key was not found." << std::endl;
      throw Exception::KeyNotFound(key);
   }
   else
   {
      std::cout << "ERROR 2" << std::endl;
   }
}



Client::Client(const std::string& toServerFifoName, const std::string& fromServerFifoName) :
   FifoCommunicator(toServerFifoName, fromServerFifoName)
{
   /// TODO: check that fifo's exist, if not raise exception.
}



Client::~Client()
{}



void Client::interactiveStore()
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

   store(srv, key);
}



void Client::interactiveRetrieve()
{
   std::string key;

   std::cout << "Key: " << std::endl;
   std::getline(std::cin, key);

   try
   {
      SerializableRealVector srv = retrieve<SerializableRealVector>(key);

      std::cout << "Received vector of size " << srv.vec.size()
                << " with last element '" << srv.vec.back() << "'" << std::endl;
   }
   catch (Exception::KeyNotFound e)
   {
      std::cout << e << std::endl;
   }

}



void Client::run()
{
   while (true)
   {
      std::string cmd;
      std::cout << "Command: STORE or RETRIEVE:" << std::endl;
      std::getline(std::cin, cmd);
      if (cmd == "STORE")
      {
         interactiveStore();

      }
      else if (cmd == "RETRIEVE")
      {
         interactiveRetrieve();
      }
      else
      {
         std::cout << "Command not valid" << std::endl;
      }
   }
}



std::vector<double> Client::generateVector(size_t length)
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
   Client client(toServerFifoName, fromServerFifoName);
   client.run();

   return 0;
}
