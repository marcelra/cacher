#ifndef TESTSERIALIZABLE_H
#define TESTSERIALIZABLE_H

#include "IBinarySerializable.h"

class TestSerializable : public IBinarySerializable
{
   public:
      TestSerializable();

      IBinarySerializable::BinaryBlob toBinaryBlob();
      IBinarySerializable* fromBinaryBlob(BinaryBlob);

   private:
      int      m_integer;
};

#endif // TESTSERIALIZABLE_H
