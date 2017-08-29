#ifndef IBINARYSERIALIZER_H
#define IBINARYSERIALIZER_H

#include <stddef.h>



class BinaryBlob
{
   public:
      BinaryBlob(size_t size);
      BinaryBlob(const BinaryBlob& other);
      BinaryBlob(char* data, size_t size);
      ~BinaryBlob();

      BinaryBlob& operator=(const BinaryBlob& other);

      size_t      getSize() const;
      const char* getData() const;
      char*       getData();
      void        clearData();

   private:
      char*    m_ptr;
      size_t   m_size;
};



class IBinarySerializable
{
   public:

      virtual BinaryBlob toBinaryBlob() const = 0;
      virtual void fromBinaryBlob(const BinaryBlob& blob) = 0;
};

#endif // IBINARYSERIALIZER_H
