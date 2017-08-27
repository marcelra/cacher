#ifndef RESPONSE_H
#define RESPONSE_H

#include <ostream>

class Response
{
   public:
      enum Type
      {
         NOT_OK = 0,
         ACKNOWLEDGE,
         ANNOUNCE
      };

   public:

      static Response responseNotOk();
      static Response responseAcknowledge();
      static Response announceMessage(size_t numBytes);

   public:

      Response(const Type& type, size_t numBytes);

      Type getType() const;
      size_t getNumBytesMessage() const;

   private:
      Type     m_type;
      size_t   m_numBytes;
};



std::ostream& operator<<(std::ostream& os, const Response& response);



#endif // RESPONSE_H
