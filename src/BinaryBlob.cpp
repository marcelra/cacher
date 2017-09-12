#include "BinaryBlob.h"

#include <iostream>

namespace NewBlob
{

const size_t BinaryBlob::s_initSize = 1024;

BinaryBlob::BinaryBlob() :
   m_ptr(new char[s_initSize]),
   m_writePtr(m_ptr),
   m_readPtr(m_ptr)
{
}

BinaryBlob::~BinaryBlob()
{
   delete[] m_ptr;
}

size_t BinaryBlob::getSize()
{
   return m_writePtr - m_ptr;
}

void BinaryBlob::growIfNeeded(size_t numBytesToBeAdded)
{
   if ((getSize() + numBytesToBeAdded) > m_bytesAlloc)
   {
      grow();
   }
}

void BinaryBlob::grow()
{
   m_bytesAlloc *= 2;

   size_t writeOffset = m_writePtr - m_ptr;
   size_t readOffset = m_readPtr - m_ptr;

   m_ptr = static_cast<char*>(realloc(m_ptr, m_bytesAlloc));

   m_writePtr = m_ptr + writeOffset;
   m_readPtr = m_ptr + readOffset;
}

BinaryBlob& BinaryBlob::operator<<(size_t x)
{
   growIfNeeded(sizeof(size_t));

   memcpy(m_writePtr, &x, sizeof(size_t));
   m_writePtr += sizeof(size_t);

   return *this;
}

BinaryBlob& BinaryBlob::operator>>(size_t& x)
{
   memcpy(&x, m_readPtr, sizeof(size_t));
   m_readPtr += sizeof(size_t);
   return *this;
}

} /// namespace NewBlob



BinaryBlob::BinaryBlob(size_t size) :
   m_size(size)
{
   m_ptr = new char[size];
}



BinaryBlob::BinaryBlob(const BinaryBlob& other)
{
   *this = other;
}



BinaryBlob::BinaryBlob(const char* data, size_t size) :
   m_size(size),
   m_ptr(new char[size])
{
   memcpy(m_ptr, data, size);
}



BinaryBlob::~BinaryBlob()
{
   delete[] m_ptr;
}



BinaryBlob& BinaryBlob::operator=(const BinaryBlob& other)
{
   this->m_ptr = other.m_ptr;
   this->m_size = other.m_size;
   return *this;
}



size_t BinaryBlob::getSize() const
{
   return m_size;
}



char* BinaryBlob::getData()
{
   return const_cast<char*>(const_cast<const BinaryBlob*>(this)->getData());
}



const char* BinaryBlob::getData() const
{
   return m_ptr;
}


void BinaryBlob::append(const char* data, size_t numBytes)
{
   size_t oldSize = m_size;
   m_ptr = static_cast<char*>(realloc(m_ptr, m_size + numBytes));
   m_size += numBytes;
   memcpy(m_ptr + oldSize, data, numBytes);
}



void BinaryBlob::append(const BinaryBlob& other)
{
   append(other.getData(), other.getSize());
}



void BinaryBlob::clearData()
{
   std::cout << "Depcrecated function clearData called..." << std::endl;
}



