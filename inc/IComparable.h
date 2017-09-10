#ifndef ICOMPARABLE_H
#define ICOMPARABLE_H


class IComparable
{
   public:
      virtual ~IComparable() {}

      virtual bool operator==(const IComparable& other) const = 0;
      bool operator!=(const IComparable& other) const;
};



inline bool IComparable::operator!=(const IComparable& other) const
{
   return !((*this) == other);
}


#endif // ICOMPARABLE_H
