#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <csignal>

#include <iostream>
#include <thread>
#include <chrono>



const char* to_server_fifo_name = "/tmp/to_server";
const char* from_server_fifo_name = "/tmp/from_server";



std::string to_upper(const std::string& str) {
   std::string result = str;

   for (size_t i = 0; i < str.size(); ++i) {
      result[i] = std::toupper(str[i]);
   }

   return result;
}



void startup() {
   std::cout << "Starting server..." << std::endl;
   mkfifo(to_server_fifo_name, 0666);
   mkfifo(from_server_fifo_name, 0666);
}



void shutdown() {
   std::cout << "Shutdown server..." << std::endl;
   unlink(to_server_fifo_name);
   unlink(from_server_fifo_name);
   exit(0);
}



void handleSignal(int) {
   shutdown();
}



int main()
/// Comments
{

   // commented out code
   signal(SIGINT, handleSignal);

   mkfifo(to_server_fifo_name, 0666);
   mkfifo(from_server_fifo_name, 0666);

   while (true)
   {
      std::cout << "Server running in lazy mode..." << std::endl;

      char buf[1024];

      int fd_read = open(to_server_fifo_name, O_RDONLY);
      read(fd_read, buf, 1024);
      close(fd_read);

      std::string command(buf);
      std::cout << "Received: " << buf << std::endl;
      std::string genResponse = to_upper(command);
      std::cout << "Sending: " << genResponse << std::endl;

      int fd_write = open(from_server_fifo_name, O_WRONLY);
      write(fd_write, genResponse.c_str(), 1024);
      close(fd_write);
   }

   return 0;
}
