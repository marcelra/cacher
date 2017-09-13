#include "TestSerializable.h"

#include <string.h>



TestSerializable::TestSerializable() :
   m_integer(0)
{}



BinaryBlob TestSerializable::toBinaryBlob() const
{
   BinaryBlob blob;
   blob << m_integer;
   return blob;
}



void TestSerializable::fromBinaryBlob(BinaryBlob& blob)
{
   blob >> m_integer;
}



int TestSerializable::getData() const
{
   return m_integer;
}



void TestSerializable::setData(int value)
{
   m_integer = value;
}


