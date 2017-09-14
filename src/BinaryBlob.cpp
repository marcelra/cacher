#include "BinaryBlob.h"
#include "IBinarySerializable.h"

#include <iostream>
#include <math.h>
#include <algorithm>

const size_t BinaryBlob::s_initSize = 1024;

BinaryBlob::BinaryBlob() :
   m_ptr(static_cast<char*>(malloc(s_initSize))),
   m_writePtr(m_ptr),
   m_readPtr(m_ptr),
   m_bytesAlloc(s_initSize)
{
}



BinaryBlob::BinaryBlob(char* data, size_t size) :
   m_ptr(data),
   m_writePtr(data + size),
   m_readPtr(data),
   m_bytesAlloc(size)
{}


const char* BinaryBlob::getData() const
{
   return m_ptr;
}


BinaryBlob::~BinaryBlob()
{
   free(static_cast<void*>(m_ptr));
}

size_t BinaryBlob::getSize() const
{
   return m_writePtr - m_ptr;
}

void BinaryBlob::growIfNeeded(size_t numBytesToBeAdded)
{
   if ((getSize() + numBytesToBeAdded) > m_bytesAlloc)
   {
      grow(numBytesToBeAdded);
   }
}

void BinaryBlob::grow(size_t numBytes)
{
   m_bytesAlloc *= std::max(2, static_cast<int>(1 + ceil(numBytes / m_bytesAlloc)));

   const size_t writeOffset = m_writePtr - m_ptr;
   const size_t readOffset = m_readPtr - m_ptr;

   m_ptr = static_cast<char*>(realloc(m_ptr, m_bytesAlloc));

   m_writePtr = m_ptr + writeOffset;
   m_readPtr = m_ptr + readOffset;
}

BinaryBlob& BinaryBlob::operator<<(const std::string& x)
{
   *this << static_cast<size_t>(x.length());

   const auto writeEnd = m_writePtr + x.length() * sizeof(char);

   growIfNeeded(x.length());
   memcpy(m_writePtr, x.c_str(), x.length() * sizeof(char));
   m_writePtr = writeEnd;

   return *this;
}

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

BinaryBlob& BinaryBlob::operator<<(const IBinarySerializable& object)
{
   object.streamToBlob(*this);
   return *this;
}

BinaryBlob& BinaryBlob::operator>>(IBinarySerializable& object)
{
   object.initFromBlob(*this);
   return *this;
}


void BinaryBlob::resetReadCursor()
{
   m_readPtr = m_ptr;
}

BinaryBlob& BinaryBlob::operator<<(const size_t& x) { return writeScalar(x); }
BinaryBlob& BinaryBlob::operator<<(const int& x) { return writeScalar(x); }
BinaryBlob& BinaryBlob::operator<<(const double& x) { return writeScalar(x); }

BinaryBlob& BinaryBlob::operator>>(size_t& x) { return readScalar(x); }
BinaryBlob& BinaryBlob::operator>>(int& x) { return readScalar(x); }
BinaryBlob& BinaryBlob::operator>>(double& x) { return readScalar(x); }


