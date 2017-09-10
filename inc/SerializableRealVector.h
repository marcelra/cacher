#ifndef SERIALIZABLEREALVECTOR_H
#define SERIALIZABLEREALVECTOR_H

#include "IBinarySerializable.h"

#include <vector>


class SerializableRealVector : public IBinarySerializable
{
   public:
      SerializableRealVector();
      SerializableRealVector(const BinaryBlob& blob);
      SerializableRealVector(const std::vector<double>& vector);

      BinaryBlob toBinaryBlob() const;
      void fromBinaryBlob(const BinaryBlob& blob);

   public:
      std::vector<double>   vec;

};

#endif // SERIALIZABLEREALVECTOR_H
