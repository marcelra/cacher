#ifndef CACHEABLEBASE_H
#define CACHEABLEBASE_H

#include "IIdentifiable.h"

#include <cassert>

template<class T>
class CacheableBase : public IIdentifiable, public T
{

   public:
      CacheableBase();

   public:
      Id getId() const;

};



template<class T>
CacheableBase<T>::CacheableBase() :
   T()
{
   assert(T::derivesFromIBinarySerializable());
}



template<class T>
IIdentifiable::Id CacheableBase<T>::getId() const
{
   return 0;
}


#endif // CACHEABLEBASE_H
