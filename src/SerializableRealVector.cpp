#include "SerializableRealVector.h"

#include <string.h>
#include <iostream>



SerializableRealVector::SerializableRealVector() :
   vec()
{}



SerializableRealVector::SerializableRealVector(BinaryBlob& blob) :
   vec()
{
   fromBinaryBlob(blob);
}



SerializableRealVector::SerializableRealVector(const std::vector<double>& vector) :
   vec(vector)
{}



BinaryBlob SerializableRealVector::toBinaryBlob() const
{
   BinaryBlob blob;
   blob << vec;
   return blob;
}


void SerializableRealVector::fromBinaryBlob(BinaryBlob& blob)
{
   vec.clear();
   blob >> vec;
}

