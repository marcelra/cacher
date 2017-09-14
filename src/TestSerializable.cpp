#include "TestSerializable.h"

#include "BinaryBlob.h"

#include <string.h>



TestSerializable::TestSerializable() :
   m_integer(0)
{}



void TestSerializable::streamToBlob(BinaryBlob& blob) const
{
   blob << m_integer;
}



void TestSerializable::initFromBlob(BinaryBlob& blob)
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


