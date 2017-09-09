#include "Exceptions.h"


#include <sstream>

namespace Exception
{



std::ostream& operator<<(std::ostream& os, BaseException& exc)
{
   os << exc.getMessage();
   return os;
}



KeyNotFound::KeyNotFound(const std::string& key) :
   m_key(key)
{}



const std::string KeyNotFound::getMessage() const
{
   std::stringstream ss;
   ss << "key '" << m_key << "' not found";
   return ss.str();
}



} /// namespace Exception
