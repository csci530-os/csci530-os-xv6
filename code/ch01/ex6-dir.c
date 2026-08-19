#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int fd;
  mkdir("/a");
  chdir("/a");
  mkdir("b");
  chdir("b");
  fd = open("c", O_CREATE | O_WRONLY);
  write(fd, "hello world\n", 12);
  close(fd);
}