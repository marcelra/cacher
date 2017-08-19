#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

int main() {

   void* shared_mem = new char[1000];

   std::cout << "Handle to shared memory = " << shared_mem << std::endl;

   const char* test = "Hello world!";
   // memcpy(shptr, test, 12);

   while (true) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   }

   delete[] shared_mem;

   return 0;
}
