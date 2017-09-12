#ifndef BINARYBLOB_H
#define BINARYBLOB_H

#include <string.h>

namespace NewBlob
{

class BinaryBlob
{
   public:
      BinaryBlob();
      virtual ~BinaryBlob();

      size_t getSize();

      BinaryBlob& operator<<(size_t x);
      BinaryBlob& operator>>(size_t& x);

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
