#include "IBinarySerializable.h"

#include <iostream>


BinaryBlob::BinaryBlob(size_t size) :
   m_size(size)
{
   m_ptr = new char[size];
   std::cout << "Create: " << (void*) m_ptr << std::endl;
}



BinaryBlob::BinaryBlob(const BinaryBlob& other)
{
   *this = other;
}



BinaryBlob::~BinaryBlob()
{
}



BinaryBlob& BinaryBlob::operator=(const BinaryBlob& other)
{
   this->m_ptr = other.m_ptr;
   this->m_size = other.m_size;
   return *this;
}



char* BinaryBlob::getData()
{
   return m_ptr;
}



void BinaryBlob::trash()
{
   std::cout << "Trash: " << (void*) m_ptr << std::endl;
   delete[] m_ptr;
   m_ptr = 0;
}

