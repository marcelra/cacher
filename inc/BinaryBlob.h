#ifndef BINARYBLOB_H
#define BINARYBLOB_H

#include <string.h>
#include <string>
#include <vector>
#include <cassert>

namespace NewBlob
{

class BinaryBlob
{
   public:

      BinaryBlob();
      virtual ~BinaryBlob();

   private:
      BinaryBlob(const BinaryBlob& other);
      BinaryBlob& operator=(const BinaryBlob& other);

   public:
      size_t getSize();
      void resetReadCursor();

      template <class T> BinaryBlob& operator<<(const T& x);
      template <class T> BinaryBlob& operator>>(T& x);

      template <class T> BinaryBlob& operator<<(const std::vector<T>& x);
      template <class T> BinaryBlob& operator>>(std::vector<T>& x);

   private:
      void grow();
      void growIfNeeded(size_t numBytesToBeAdded);

   private:
      char*       m_ptr;
      size_t      m_bytesAlloc;
      char*       m_writePtr;
      char*       m_readPtr;

      static const size_t s_initSize;
};



template <class T>
BinaryBlob& BinaryBlob::operator<<(const T& x)
{
   growIfNeeded(sizeof(T));

   memcpy(m_writePtr, &x, sizeof(T));
   m_writePtr += sizeof(T);
   return *this;
}



template <class T>
BinaryBlob& BinaryBlob::operator>>(T& x)
{
   assert( (m_readPtr + sizeof(T)) <= m_writePtr );

   memcpy(&x, m_readPtr, sizeof(T));
   m_readPtr += sizeof(T);
   return *this;
}



template <class T>
BinaryBlob& BinaryBlob::operator<<(const std::vector<T>& x)
{
   *this << static_cast<size_t>(x.size());

   growIfNeeded(sizeof(T) * x.size());

   memcpy(m_writePtr, &x[0], sizeof(T)*x.size());

   m_writePtr += sizeof(T) * x.size();

   return *this;
}



template <class T>
BinaryBlob& BinaryBlob::operator>>(std::vector<T>& x)
{
   size_t len;
   *this >> len;

   assert( (m_readPtr + len) <= m_writePtr);
   x.insert(x.end(), m_readPtr, m_readPtr + len);
   m_readPtr += len;

   return *this;
}

} /// namespace NewBlob


class BinaryBlob
{
   public:
      BinaryBlob(size_t size = 0);
      BinaryBlob(const BinaryBlob& other);
      BinaryBlob(const char* data, size_t size);
      ~BinaryBlob();

      BinaryBlob& operator=(const BinaryBlob& other);

      size_t      getSize() const;
      const char* getData() const;
      char*       getData();
      void        clearData();

      void append(const char* data, size_t numBytes);
      void append(const BinaryBlob& other);

   private:
      char*    m_ptr;
      size_t   m_size;
};



#endif // BINARYBLOB_H