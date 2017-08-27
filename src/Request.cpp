#include "Request.h"

#include <cassert>
#include <ostream>



std::string emptyKey(128, '_');



Request::Request(size_t numBytes) :
   m_type(Request::STORE),
   m_numBytes(numBytes)
{
   std::copy(emptyKey.begin(), emptyKey.end(), m_key);
}



Request::Request(const std::string& key) :
   m_type(Request::RETRIEVE),
   m_numBytes(0)
{
   std::copy(emptyKey.begin(), emptyKey.end(), m_key);
   assert(key.length() < 128);
   std::copy(key.begin(), key.end(), m_key);
}



Request Request::store(size_t numBytes)
{
   return Request(numBytes);
}



Request Request::retrieve(const std::string& key)
{
   return Request(key);
}



bool Request::isStoreRequest() const
{
   return m_type == Request::STORE;
}



size_t Request::getNumBytes() const
{
   return m_numBytes;
}



bool Request::isRetrieveRequest() const
{
   return m_type == Request::RETRIEVE;
}



std::string Request::getKey() const
{
   return m_key;
}



std::ostream& operator<<(std::ostream& os, const Request& request)
{
   if (request.isStoreRequest())
   {
      os << "Request to store " << request.getNumBytes() << " bytes";
   }
   else if (request.isRetrieveRequest())
   {
      os << "Request to retrieve item by key '" << request.getKey() << "'";
   }
   return os;
}
