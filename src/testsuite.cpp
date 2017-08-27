#include <iostream>

#include "TestSerializable.h"
#include "SerializableRealVector.h"

#include <thread>
#include <chrono>



bool testSerializable()
{
   TestSerializable ts;
   ts.setData(150);
   BinaryBlob&& blob = ts.toBinaryBlob();

   TestSerializable ts2;
   ts2.fromBinaryBlob(blob);

   std::cout << ts2.getData() << std::endl;

   blob.clearData();
   return true;
}



bool testSerializableRealVector(size_t n)
{
   std::vector<double>* vec = new std::vector<double>(n);
   for (size_t i=0; i < n; ++i)
   {
      (*vec)[i] = i*16;
   }
   std::cout << "After creating vector" << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(5));

   SerializableRealVector* srv = new SerializableRealVector(*vec);
   std::cout << "After creating serializable vector" << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(5));

   delete vec;
   std::cout << "After removing vector" << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(5));

   BinaryBlob&& blob = srv->toBinaryBlob();
   std::cout << "After creating blob" << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(5));

   delete srv;
   std::cout << "After deleting original vector" << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(5));

   SerializableRealVector srv2(blob);
   std::cout << "After creating 2nd vector" << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(5));

   std::cout << srv2.vec.back() << std::endl;

   // for (size_t i=0; i<srv2.vec.size(); ++i)
   // {
   //     std::cout << srv2.vec[i] << ", ";
   // }
   // std::cout << std::endl;
   blob.clearData();
   std::cout << "After clearing data" << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(5));
}



int main()
{

   // for (size_t i=0; i < 10e6; ++i)
   // {
   testSerializable();
   // }

   testSerializableRealVector(20000000000/16);



   return 0;
}