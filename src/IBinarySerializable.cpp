#include "IBinarySerializable.h"

#include <iostream>
#include <string.h>


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

