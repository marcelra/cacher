#ifndef REQUEST_H
#define REQUEST_H

#include <string>



class Request
{
   public:

      enum Type
      {
         STORE = 0,
         RETRIEVE
      };

   public:
      static Request store(size_t numBytes);
      static Request retrieve(const std::string& key);

      bool isStoreRequest() const;
      size_t getNumBytes() const;

      bool isRetrieveRequest() const;
      std::string getKey() const;

   private:
      Request(const std::string& key);
      Request(size_t numBytes);

   friend std::ostream& operator<<(std::ostream& os, const Request& request);

   private:
      Type      m_type;
      size_t    m_numBytes;
      char      m_key[128];
};



std::ostream& operator<<(std::ostream& os, const Request& request);

#endif // REQUEST_H
