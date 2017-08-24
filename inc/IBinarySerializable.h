#ifndef IBINARYSERIALIZER_H
#define IBINARYSERIALIZER_H

#include <stddef.h>



class BinaryBlob
{
   public:
      BinaryBlob(size_t size);
      BinaryBlob(const BinaryBlob& other);
      ~BinaryBlob();

      BinaryBlob& operator=(const BinaryBlob& other);

      char*    getData();
      void     trash();

   private:
      char*    m_ptr;
      size_t   m_size;
};



class IBinarySerializable
{
   public:

      virtual BinaryBlob toBinaryBlob() = 0;
      virtual void fromBinaryBlob(BinaryBlob) = 0;
};

#endif // IBINARYSERIALIZER_H
