#include "Parameter.h"


template<>
BinaryBlob Parameter<std::string>::toBinaryBlob() const
{
   const size_t len = m_value.length();

   BinaryBlob blob(sizeof(size_t) + len);

   memcpy(blob.getData(), &len, sizeof(size_t));
   memcpy(blob.getData() + sizeof(size_t), m_value.c_str(), len);

   return blob;
}


template<>
void Parameter<std::string>::fromBinaryBlob(const BinaryBlob& blob)
{
   const size_t nChars = *reinterpret_cast<const size_t*>(blob.getData());

   m_value = std::string(nChars, ' ');
   for (size_t iChar = 0; iChar < nChars; ++iChar)
   {
      m_value[iChar] = blob.getData()[iChar + sizeof(size_t)];
   }
}



