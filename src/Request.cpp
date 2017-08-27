#include "Request.h"

#include <stdlib.h>

#include <cassert>
#include <ostream>
#include <string.h>



std::string emptyKey(MAX_KEY_LENGTH, '_');



Request::Request()
{}



Request::Request(size_t numBytes) :
   m_type(Request::STORE),
   m_numBytes(numBytes)
{
   memcpy(m_key, emptyKey.c_str(), MAX_KEY_LENGTH);
}



Request::Request(const std::string& key) :
   m_type(Request::RETRIEVE),
   m_numBytes(0)
{
   memcpy(m_key, emptyKey.c_str(), MAX_KEY_LENGTH);
   assert(key.length() < MAX_KEY_LENGTH);
   memcpy(m_key, key.c_str(), MAX_KEY_LENGTH);
}



Request Request::store(const std::string& key, size_t numBytes)
{
   Request req(key);
   req.m_numBytes = numBytes;
   req.m_type = Request::STORE;
   return req;
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
