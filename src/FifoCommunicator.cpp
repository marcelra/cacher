#include "FifoCommunicator.h"

#include "IBinarySerializable.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


FifoCommunicator::FifoCommunicator(const std::string& sendFifo, const std::string& receiveFifo) :
   m_sendFifo(sendFifo),
   m_receiveFifo(receiveFifo)
{}



void FifoCommunicator::send(const char* data, size_t numBytes)
{
   int fd_write = open(m_sendFifo.c_str(), O_WRONLY);
   write(fd_write, data, numBytes);
   close(fd_write);
}



char* FifoCommunicator::receive(size_t numBytes)
{
   int fd_read = open(m_receiveFifo.c_str(), O_RDONLY);
   char* buffer = new char[numBytes];
   read(fd_read, buffer, numBytes);
   close(fd_read);
   return buffer;
}



BinaryBlob* FifoCommunicator::receiveBinaryBlob(size_t numBytes)
{
   char* buf = receive(numBytes);
   return new BinaryBlob(buf, numBytes);
}



void FifoCommunicator::sendBinaryBlob(const BinaryBlob& blob)
{
   send(blob.getData(), blob.getSize());
}


