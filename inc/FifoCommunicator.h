#ifndef FIFOCOMMUNICATOR_H
#define FIFOCOMMUNICATOR_H

#include <string>
#include <string.h>

class BinaryBlob;



class FifoCommunicator
{
   public:
      FifoCommunicator(const std::string& sendFifo, const std::string& receiveFifo);
      virtual ~FifoCommunicator() {}

   private:
      FifoCommunicator(const FifoCommunicator& other);
      FifoCommunicator& operator=(const FifoCommunicator& other);

   public:
      void send(const char* data, size_t numBytes);
      char* receive(size_t numBytes);

      BinaryBlob* receiveBinaryBlob(size_t numBytes);
      void sendBinaryBlob(const BinaryBlob& blob);

      template<class T> T* receiveObj();
      template<class T> void sendObj(const T& obj);

   private:
      std::string    m_sendFifo;
      std::string    m_receiveFifo;
};



template<class T> T* FifoCommunicator::receiveObj()
{
   char* buf = receive(sizeof(T));
   return reinterpret_cast<T*>(buf);
}



template<class T> void FifoCommunicator::sendObj(const T& obj)
{
   send(reinterpret_cast<const char*>(&obj), sizeof(T));
}




#endif // FIFOCOMMUNICATOR_H
