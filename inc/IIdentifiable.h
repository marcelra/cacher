#ifndef IIDENTIFIABLE_H
#define IIDENTIFIABLE_H

#include "IComparable.h"

#include <stdlib.h>



class IIdentifiable : public IComparable
{
   public:
      typedef size_t Id;

   public:
      virtual ~IIdentifiable() {}

   public:
      virtual Id getId() const = 0;

      bool operator==(const IComparable& other) const;

};



inline bool IIdentifiable::operator==(const IComparable& other) const
{
   const IIdentifiable& cmp = dynamic_cast<const IIdentifiable&>(other);
   if (!&cmp) {
      return false;
   }
   else {
      return getId() == cmp.getId();
   }
}

#endif // IIDENTIFIABLE_H
