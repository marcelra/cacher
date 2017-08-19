#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <chrono>
#include <thread>



const char* to_server_fifo_name   = "/tmp/to_server";
const char* from_server_fifo_name = "/tmp/from_server";



int main()
{
   std::cout << "Started" << std::endl;

   while (true)
   {
      std::string buf;
      std::getline(std::cin, buf);

      int fd_write = open(to_server_fifo_name, O_WRONLY);
      write(fd_write, buf.c_str(), 1024);
      close(fd_write);

      char read_buf[1024];
      int fd_read = open(from_server_fifo_name, O_RDONLY);
      read(fd_read, read_buf, 1024);
      close(fd_read);

      std::cout << "Server responded: " << std::endl;
      std::cout << read_buf << std::endl;
   }
}
