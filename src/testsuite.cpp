#include <iostream>

#include "TestSerializable.h"



bool testSerializable()
{
   TestSerializable ts;
   ts.setData(150);
   BinaryBlob&& blob = ts.toBinaryBlob();

   TestSerializable ts2;
   ts2.fromBinaryBlob(blob);

   // std::cout << ts2.getData() << std::endl;
   // std::cout << sizeof(char) << std::endl;

   blob.trash();
}

int main()
{

   for (size_t i=0; i < 10e6; ++i)
   {
      testSerializable();
   }


   return 0;
}
