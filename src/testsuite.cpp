#include <iostream>

#include "TestSerializable.h"
#include "SerializableRealVector.h"
#include "Request.h"
#include "Response.h"
#include "Parameter.h"
#include "DependencyListBase.h"
#include "DummyAlgorithm.h"
#include "CacheableBase.h"

#include <thread>
#include <chrono>



bool testSerializable()
{
   TestSerializable ts;
   ts.setData(150);
   BinaryBlob blob;

   ts.streamToBlob(blob);

   TestSerializable ts2;
   ts2.initFromBlob(blob);

   std::cout << ts2.getData() << std::endl;

   return true;
}



bool testSerializableRealVector(size_t n)
{
   std::vector<double>* vec = new std::vector<double>(n);
   for (size_t i=0; i < n; ++i)
   {
      (*vec)[i] = i*16;
   }

   SerializableRealVector* srv = new SerializableRealVector(*vec);
   delete vec;

   BinaryBlob blob;
   blob << *srv;
   // srv->streamToBlob(blob);

   delete srv;

   SerializableRealVector srv2(blob);

   std::cout << srv2.vec.back() << std::endl;
   return true;
}



bool testRequest()
{
   {
      auto request = Request::store("myKey", 128);
      std::cout << request << std::endl;
   }

   {
      auto request = Request::retrieve("ELEMENT");
      std::cout << request << std::endl;
   }

   {
      auto response = Response::responseAcknowledge();
      std::cout << response << std::endl;
   }
   {
      auto response = Response::responseNotOk();
      std::cout << response << std::endl;
   }
   {
      auto response = Response::announceMessage(128);
      std::cout << response << std::endl;
   }
   return true;
}



bool testParameter()
{
   Parameter<int> par1(42);
   Parameter<int> par2(42);

   std::cout << "par1 == par2: " << (par1 == par2) << std::endl;

   Parameter<int> par3(43);

   std::cout << "par1 == par3: " << (par1 == par3) << std::endl;


   Parameter<std::string> par4("hoi");
   BinaryBlob blob;
   blob << par4;
   Parameter<std::string> par5(blob);

   std::cout << "par4 == par5: " << (par4 == par5) << std::endl;


   return true;
}



bool testDependencyListBase()
{
   DummyAlgorithm alg("Dummy", DummyAlgorithm::DependencyList(42, 33));
   DependencyListBase depList1;
   depList1.addDependency(Parameter<int>(42));
   depList1.addDependency(Parameter<int>(33));

   DependencyListBase depList2;
   depList2.addDependency(Parameter<int>(42));
   depList2.addDependency(Parameter<int>(33));

   std::cout << "depList1 == depList2: " << (depList1 == depList2) << std::endl;

   DependencyListBase depList3;
   depList2.addDependency(Parameter<int>(2));
   depList2.addDependency(Parameter<int>(33));

   std::cout << "depList1 == depList3: " << (depList1 == depList3) << std::endl;

   return true;
}



bool testDummyAlg()
{
   DummyAlgorithm alg("dummy", DummyAlgorithm::DependencyList(42, 3));


   return true;
}


bool testCacheableBase()
{
   CacheableBase<SerializableRealVector> x;
   return true;
}


bool testBinaryBlob()
{
   BinaryBlob blob;

   const size_t len = 25;
   std::vector<size_t> vec(len);

   for (size_t i = 0; i < vec.size(); ++i)
   {
      vec[i] = i*i;
   }

   // blob << len;
   // for (size_t i = 0; i < vec.size(); ++i)
   // {
   //    blob << vec[i];
   // }
   blob << vec;


   blob << std::string("hoi");

   size_t len2;
   blob >> len2;
   std::vector<size_t> vec2(len2);
   for (size_t i = 0; i < vec2.size(); ++i)
   {
      blob >> vec2[i];
   }

   for (size_t i = 0; i < vec2.size(); ++i)
   {
      std::cout << vec2[i] << std::endl;
   }

   std::string str;
   blob >> str;

   std::cout << str << std::endl;





   return true;
}



int main()
{

   testSerializable();
   testSerializableRealVector(1e6);

   testRequest();
   testParameter();

   testDependencyListBase();
   testCacheableBase();
   testDummyAlg();

   testBinaryBlob();



   return 0;
}
