#ifndef IBINARYSERIALIZER_H
#define IBINARYSERIALIZER_H

#include <stddef.h>

#include "BinaryBlob.h"



class IBinarySerializable
{
   public:
      virtual ~IBinarySerializable() {}

   public:
      virtual BinaryBlob toBinaryBlob() const = 0;
      virtual void fromBinaryBlob(const BinaryBlob& blob) = 0;

   public:
      static bool derivesFromIBinarySerializable() { return true; }
};

#endif // IBINARYSERIALIZER_H
