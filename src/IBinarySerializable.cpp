#include "IBinarySerializable.h"

#include <iostream>


BinaryBlob::BinaryBlob(size_t size) :
   m_size(size)
{
   m_ptr = new char[size];
}



BinaryBlob::BinaryBlob(const BinaryBlob& other)
{
   *this = other;
}



BinaryBlob::BinaryBlob(char* data, size_t size) :
   m_size(size),
   m_ptr(data)
{}



BinaryBlob::~BinaryBlob()
{
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



void BinaryBlob::clearData()
{
   delete[] m_ptr;
   m_ptr = 0;
}

