#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int
main()
{
  struct stat sb;
  if (stat("input.txt", &sb) == -1) {
    fprintf(stderr, "Error trying to stat() file, does it exist?\n");
    exit(0);
  }

  printf("device     : %d\n", sb.st_dev);
  printf("inode no   : %d\n", sb.st_ino);
  printf("type (mode): %o\n", (sb.st_mode & S_IFMT));
  printf("nlink      : %d\n", sb.st_nlink);
  printf("size       : %d\n", sb.st_size);
}