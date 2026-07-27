#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (fork() == 0) {
    char *argv[2];

    argv[0] = "cat";
    argv[1] = 0;
    close(0);
    open("input.txt", O_RDONLY);
    exec("cat", argv);
  }
}