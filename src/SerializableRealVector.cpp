#include "SerializableRealVector.h"

#include <string.h>
#include <iostream>



SerializableRealVector::SerializableRealVector() :
   vec()
{}



SerializableRealVector::SerializableRealVector(const BinaryBlob& blob) :
   vec()
{
   fromBinaryBlob(blob);
}



SerializableRealVector::SerializableRealVector(const std::vector<double>& vector) :
   vec(vector)
{}



BinaryBlob SerializableRealVector::toBinaryBlob() const
{
   BinaryBlob blob(sizeof(size_t) + vec.size()*sizeof(double));

   char* ptr = blob.getData();
   size_t n = vec.size();
   memcpy(ptr, &n, sizeof(size_t));
   memcpy(ptr + sizeof(size_t), &vec[0], sizeof(double)*vec.size());

   return blob;
}


void SerializableRealVector::fromBinaryBlob(const BinaryBlob& blob)
{
   const char* data = blob.getData();

   size_t size = *reinterpret_cast<const size_t*>(data);
   vec = std::vector<double>(size);

   auto start = data + sizeof(size_t);
   memcpy(&vec[0], start, sizeof(double)*size);
}

