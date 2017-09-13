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

   const size_t writeOffset = m_writePtr - m_ptr;
   const size_t readOffset = m_readPtr - m_ptr;

   m_ptr = static_cast<char*>(realloc(m_ptr, m_bytesAlloc));

   m_writePtr = m_ptr + writeOffset;
   m_readPtr = m_ptr + readOffset;
}

template <>
BinaryBlob& BinaryBlob::operator<<(const std::string& x)
{
   *this << static_cast<size_t>(x.length());

   const auto writeEnd = m_writePtr + x.length() * sizeof(char);

   growIfNeeded(x.length());
   memcpy(m_writePtr, x.c_str(), x.length() * sizeof(char));
   m_writePtr = writeEnd;

   return *this;
}

template <>
BinaryBlob& BinaryBlob::operator>>(std::string& x)
{
   size_t len;
   *this >> len;

   const auto readEnd = m_readPtr + len;
   assert( readEnd <= m_writePtr);

   x.append(std::string(m_readPtr, readEnd));
   m_readPtr = readEnd;

   return *this;
}

void BinaryBlob::resetReadCursor()
{
   m_readPtr = m_ptr;
}

// BinaryBlob& BinaryBlob::operator<<(size_t x)
// {
//    write(x);
//    return *this;
// }

// BinaryBlob& BinaryBlob::operator<<(int x)
// {
//
// }


// BinaryBlob& BinaryBlob::operator>>(size_t& x)
// {
//    read(x);
//    return *this;
// }


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



