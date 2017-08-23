#include "TestSerializable.h"



TestSerializable::TestSerializable() :
   m_integer(42)
{}



IBinarySerializable::BinaryBlob TestSerializable::toBinaryBlob()
{
   return BinaryBlob(new TestSerializable(), sizeof(TestSerializable));
}



IBinarySerializable* TestSerializable::fromBinaryBlob(BinaryBlob blob)
{
   return new TestSerializable(*reinterpret_cast<TestSerializable*>(blob.getData()));
}

