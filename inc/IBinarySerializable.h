#ifndef IBINARYSERIALIZER_H
#define IBINARYSERIALIZER_H

#include <stddef.h>



class IBinarySerializable
{
   public:
      class BinaryBlob
      {
         public:
            BinaryBlob(void* ptr, size_t size);
            ~BinaryBlob();

            void* getData() const;

         private:
            void*    m_ptr;
            size_t   m_size;
      };

   public:

      virtual BinaryBlob toBinaryBlob() = 0;
      virtual IBinarySerializable* fromBinaryBlob(BinaryBlob) = 0;
};

#endif // IBINARYSERIALIZER_H
