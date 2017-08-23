#include "IBinarySerializable.h"



IBinarySerializable::BinaryBlob::BinaryBlob(void *ptr, size_t size) :
   m_ptr(ptr),
   m_size(size)
{
}



IBinarySerializable::BinaryBlob::~BinaryBlob()
{
}



void* IBinarySerializable::BinaryBlob::getData() const
{
   return m_ptr;
}
