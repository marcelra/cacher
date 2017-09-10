#ifndef PARAMETER_H
#define PARAMETER_H

#include "IComparable.h"
#include "IBinarySerializable.h"

#include <iostream>
#include <string.h>
#include <cassert>

template<class T>
class Parameter : public IComparable, public IBinarySerializable
{
   public:
      Parameter(const T& value);
      Parameter(const BinaryBlob& blob);

      bool operator==(const IComparable& other) const;

   public:
      BinaryBlob toBinaryBlob() const;
      void fromBinaryBlob(const BinaryBlob& blob);

   private:
      T  m_value;
};


template<> BinaryBlob Parameter<std::string>::toBinaryBlob() const;
template<> void Parameter<std::string>::fromBinaryBlob(const BinaryBlob& blob);


template<class T>
Parameter<T>::Parameter(const T& value) :
   m_value(value)
{}



template<class T>
Parameter<T>::Parameter(const BinaryBlob& blob)
{
   fromBinaryBlob(blob);
}



template<class T>
bool Parameter<T>::operator==(const IComparable& other) const
{
   const Parameter<T>& cmp = dynamic_cast<const Parameter<T>&>(other);
   if (!&cmp) {
      return false;
   }
   else {
      return m_value == cmp.m_value;
   }
}



template<class T>
BinaryBlob Parameter<T>::toBinaryBlob() const
{
   BinaryBlob blob(reinterpret_cast<const char*>(&m_value), sizeof(T));
   return blob;
}


template<class T>
void Parameter<T>::fromBinaryBlob(const BinaryBlob& blob)
{
   assert(blob.getSize() == sizeof(T));
   m_value = *blob.getData();
}



#endif // PARAMETER_H
