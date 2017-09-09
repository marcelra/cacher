#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <ostream>



namespace Exception
{



class BaseException
{
   public:
      virtual const std::string getMessage() const = 0;
      virtual ~BaseException() {}
};



std::ostream& operator<<(std::ostream& os, BaseException& exc);



class KeyNotFound : public BaseException
{
   public:
      KeyNotFound(const std::string& key);

   public:
      const std::string getMessage() const;


   private:
      std::string m_key;
};



} /// namespace Exception


#endif // EXCEPTIONS_H
