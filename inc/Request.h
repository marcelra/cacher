#ifndef REQUEST_H
#define REQUEST_H

#include <string>



const size_t MAX_KEY_LENGTH = 128;



class Request
{
   public:

      enum Type
      {
         STORE = 0,
         RETRIEVE
      };

   public:
      static Request store(const std::string& key, size_t numBytes);
      static Request retrieve(const std::string& key);

      bool isStoreRequest() const;
      size_t getNumBytes() const;

      bool isRetrieveRequest() const;
      std::string getKey() const;

      Request();

   private:
      Request(const std::string& key);
      Request(size_t numBytes);

   friend std::ostream& operator<<(std::ostream& os, const Request& request);

   private:
      char      m_key[MAX_KEY_LENGTH];
      Type      m_type;
      size_t    m_numBytes;
};



std::ostream& operator<<(std::ostream& os, const Request& request);

#endif // REQUEST_H
