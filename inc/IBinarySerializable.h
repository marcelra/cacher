#ifndef IBINARYSERIALIZER_H
#define IBINARYSERIALIZER_H

#include <stddef.h>



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



class IBinarySerializable
{
   public:
      virtual ~IBinarySerializable() {}

   public:
      virtual BinaryBlob toBinaryBlob() const = 0;
      virtual void fromBinaryBlob(const BinaryBlob& blob) = 0;

   public:
      static bool derivesFromIBinarySerializable() { return true; }
};

#endif // IBINARYSERIALIZER_H
