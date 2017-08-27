#include "TestSerializable.h"

#include <string.h>



TestSerializable::TestSerializable() :
   m_integer(0)
{}



BinaryBlob TestSerializable::toBinaryBlob() const
{
   size_t size = sizeof(TestSerializable);
   BinaryBlob blob(size);
   // char** tmp = &(blob.getData());
   memcpy(blob.getData(), this, size);
   // return BinaryBlob(new TestSerializable(*this), sizeof(TestSerializable));
   return blob;
}



void TestSerializable::fromBinaryBlob(const BinaryBlob& blob)
{
   *this = TestSerializable(*reinterpret_cast<const TestSerializable*>(blob.getData()));
}



int TestSerializable::getData() const
{
   return m_integer;
}



void TestSerializable::setData(int value)
{
   m_integer = value;
}


