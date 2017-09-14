#ifndef IBINARYSERIALIZER_H
#define IBINARYSERIALIZER_H

#include <stddef.h>

class BinaryBlob;

class IBinarySerializable
{
   public:
      virtual ~IBinarySerializable() {}

   public:
      virtual void streamToBlob(BinaryBlob& blob) const = 0;
      virtual void initFromBlob(BinaryBlob& blob) = 0;

   public:
      static bool derivesFromIBinarySerializable() { return true; }
};


#endif // IBINARYSERIALIZER_H
