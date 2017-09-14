#include "SerializableRealVector.h"

#include "BinaryBlob.h"

#include <string.h>
#include <iostream>





SerializableRealVector::SerializableRealVector() :
   vec()
{}



SerializableRealVector::SerializableRealVector(BinaryBlob& blob) :
   vec()
{
   initFromBlob(blob);
}



SerializableRealVector::SerializableRealVector(const std::vector<double>& vector) :
   vec(vector)
{}



void SerializableRealVector::streamToBlob(BinaryBlob& blob) const
{
   blob << vec;
}


void SerializableRealVector::initFromBlob(BinaryBlob& blob)
{
   vec.clear();
   blob >> vec;
}

