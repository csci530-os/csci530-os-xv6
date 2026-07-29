#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// mystrlen: return length of string s
int
mystrlen(char *s)
{
  int n;

  for (n = 0; *s != '\0'; s++)
    n++;

  return n;
}

int
main(int argc, char *argv[])
{
  char array[100] = {'h', 'e', 'l', 'l', 'o', ',', ' ',
                     'w', 'o', 'r', 'l', 'd', '\0'};
  char *ptr = "hello, world";

  printf("length string constant: %d\n", mystrlen("hello, world"));
  printf("length character array: %d\n", mystrlen(array));
  printf("length pointer to char block: %d\n", mystrlen(ptr));
  printf("\n\n");

  printf("length string constant: %d\n", strlen("hello, world"));
  printf("length character array: %d\n", strlen(array));
  printf("length pointer to char block: %d\n", strlen(ptr));
}
