#include "Utils.h"

#include <iostream>

void Utils::binaryDump(const char* data, size_t numBytes)
{
   for(int i=0; i<numBytes; ++i)
       std::cout << std::hex << (int) data[i];
   std::cout << std::endl;
}
