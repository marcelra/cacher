#ifndef TESTSERIALIZABLE_H
#define TESTSERIALIZABLE_H

#include "IBinarySerializable.h"

class TestSerializable : public IBinarySerializable
{
   public:
      TestSerializable();

      BinaryBlob toBinaryBlob() const;
      void fromBinaryBlob(const BinaryBlob& blob);

      int getData() const;
      void setData(int value);

   private:
      int      m_integer;
};

#endif // TESTSERIALIZABLE_H
