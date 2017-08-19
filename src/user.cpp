#include <iostream>
#include <assert.h>
#include <sstream>

int main(int argc, char* argv[]) {

   assert(argc == 2);

   const char* ptr_str = argv[1];

   void* ptr;

   std::stringstream ss;
   ss << std::hex << ptr_str;
   ss >> ptr;

   char* msg = reinterpret_cast<char*>(0x558930412c20); //   reinterpret_cast<char*>(ptr);

   std::cout << std::hex << msg << std::endl;

   return 0;
}
