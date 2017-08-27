#include "Response.h"

#include <ostream>



Response::Response()
{}



Response::Response(const Response::Type& type, size_t numBytes) :
   m_type(type),
   m_numBytes(numBytes)
{}



Response Response::responseNotOk()
{
   return Response(NOT_OK, 0);
}



Response Response::responseAcknowledge()
{
   return Response(ACKNOWLEDGE, 0);
}



Response Response::announceMessage(size_t numBytes)
{
   return Response(ANNOUNCE, numBytes);
}



Response Response::keyNotFound()
{
   return Response(KEY_NOT_FOUND, 0);
}



Response::Type Response::getType() const
{
   return m_type;
}



size_t Response::getNumBytesMessage() const
{
   return m_numBytes;
}



std::ostream& operator<<(std::ostream& os, const Response& response)
{
   os << "Reponse ";
   if (response.getType() == Response::NOT_OK)
   {
      os << "NOT_OK";
   }
   else if (response.getType() == Response::ACKNOWLEDGE)
   {
      os << "ACKNOWLEDGE";
   }
   else if (response.getType() == Response::ANNOUNCE)
   {
      os << "ANNOUNCE:" << " announcement of message of " << response.getNumBytesMessage() << " bytes";
   }
   return os;
}
