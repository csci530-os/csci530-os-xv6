#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct stat sb;
  if (stat("input.txt", &sb) == -1) {
    fprintf(2, "Error trying to stat() file, does it exist?\n");
    exit(0);
  }

  printf("device   : %d\n", sb.dev);
  printf("inode no : %d\n", sb.ino);
  printf("type     : %d\n", sb.type);
  printf("nlink    : %d\n", sb.nlink);
  printf("size     : %lu\n", sb.size);
}