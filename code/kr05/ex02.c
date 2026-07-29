#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// interchange *px and *py
void
swap(int *px, int *py)
{
  int temp;

  temp = *px;
  *px = *py;
  *py = temp;
}

int
main(int argc, char *argv[])
{
  int a = 5;
  int b = 42;

  // pass by reference
  swap(&a, &b);
  printf("a=%d b=%d\n", a, b);
}
