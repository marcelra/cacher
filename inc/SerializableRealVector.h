#ifndef SERIALIZABLEREALVECTOR_H
#define SERIALIZABLEREALVECTOR_H

#include "IBinarySerializable.h"

#include <vector>


class SerializableRealVector : public IBinarySerializable
{
   public:
      SerializableRealVector();
      SerializableRealVector(BinaryBlob& blob);
      SerializableRealVector(const std::vector<double>& vector);

      BinaryBlob toBinaryBlob() const;
      void fromBinaryBlob(BinaryBlob& blob);

   public:
      std::vector<double>   vec;

};

#endif // SERIALIZABLEREALVECTOR_H
