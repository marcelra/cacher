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
#include "BinaryBlob.h"



const char* toServerFifoName = "/tmp/to_server";
const char* fromServerFifoName = "/tmp/from_server";



////////////////////////////////////////////////////////////////////////////////
/// handleSignal
////////////////////////////////////////////////////////////////////////////////
void handleSignal(int) {
   /**
    * Handles SIGTERM and SIGINT signals
    */
   std::cout << "Shutdown server..." << std::endl;
   unlink(toServerFifoName);
   unlink(fromServerFifoName);
   exit(0);
}



////////////////////////////////////////////////////////////////////////////////
/// Server class definition
////////////////////////////////////////////////////////////////////////////////
class Server : public FifoCommunicator
{
   public:
      /**
       * Create a server connecting to @param toServerFifoName for reading and
       * @param from ServerFifoName for writing.
       */
      Server(const std::string& toServerFifoName, const std::string& fromServerFifoName);

      /**
       * Server destructor. Does nothing, since the run function is blocking and app will
       * generally hang there. App should be closed by SIGTERM or SIGINT signals.
       */
      ~Server();

   private:
      Server(const Server& other);
      Server& operator=(const Server& other);

   public:
      /**
       * Run server. Blocking call.
       */
      void run();

   private:
      /// Handle a store request
      void handleStoreRequest(const Request& request);

      /// Handle a retrieve request
      void handleRetrieveRequest(const Request& request);

   private:
      std::map<std::string, BinaryBlob*> m_store;  //! BinaryBlob storage
};



////////////////////////////////////////////////////////////////////////////////
/// Server constructor
////////////////////////////////////////////////////////////////////////////////
Server::Server(const std::string& toServerFifoName, const std::string& fromServerFifoName) :
   FifoCommunicator(fromServerFifoName, toServerFifoName)
{
   signal(SIGINT, handleSignal);

   mkfifo(toServerFifoName.c_str(), 0666);
   mkfifo(fromServerFifoName.c_str(), 0666);
}



////////////////////////////////////////////////////////////////////////////////
/// Server destructor
////////////////////////////////////////////////////////////////////////////////
Server::~Server()
{
}



////////////////////////////////////////////////////////////////////////////////
/// Server::run
////////////////////////////////////////////////////////////////////////////////
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



////////////////////////////////////////////////////////////////////////////////
/// Server::handleStoreRequest
////////////////////////////////////////////////////////////////////////////////
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



////////////////////////////////////////////////////////////////////////////////
/// Server::handleRetrieveRequest
////////////////////////////////////////////////////////////////////////////////
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



////////////////////////////////////////////////////////////////////////////////
/// main function
////////////////////////////////////////////////////////////////////////////////
int main()
/// Comments
{

   Server server(toServerFifoName, fromServerFifoName);
   server.run();

   return 0;
}


