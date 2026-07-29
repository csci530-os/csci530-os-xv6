#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int x = 1, y = 2, z[10];
  int *ip; // ip is a pointer to int

  z[0] = 0;
  printf("x=%d y=%d z[0]=%d\n\n", x, y, z[0]);

  // first, what are the basic sizes of types in xv6 riscv
  printf("sizeof(char)     : %ld\n", sizeof(char));
  printf("sizeof(short)    : %ld\n", sizeof(short));
  printf("sizeof(int)      : %ld\n", sizeof(int));
  printf("sizeof(long int) : %ld\n", sizeof(long int));
  printf("sizeof(float)    : %ld\n", sizeof(float));
  printf("sizeof(double)   : %ld\n", sizeof(double));
  printf("sizeof(void *)   : %ld\n", sizeof(void *));
  printf("\n\n");

  // basic examples of pointers and addresses
  ip = &x; // ip now points to x
  printf("address of x: %lx\n", (long unsigned int)(&x));
  printf("address in ip: %lx\n", (long unsigned int)(ip));
  printf("sizeof(ip): %ld\n", sizeof(ip));
  printf("\n\n");

  y = *ip; // y is now 1
  printf("x=%d\n\n", x);

  *ip = 0; // x is now 0
  printf("y=%d\n\n", y);

  ip = &z[0]; // ip now points to z[0]
  printf("address of z[0]   : %ld\n", (long unsigned int)(&z[0]));
  printf("address in ip     : %ld\n", (long unsigned int)(ip));
  printf("base address of z : %ld\n", (long unsigned int)(z));
  printf("\n\n");

  // more examples, a dereferenced pointer can be used anywhere the
  // variable it points to could be
  ip = &x;        // reassign back to x
  y = *ip + 1;    // y = x + 1
  *ip = *ip + 10; // x = x + 10
  *ip += 1;       // x += 1
  ++*ip;          // pre increment x again
  (*ip)++;        // careful, the parens are necessary here

  // can you guess what x is at this point?
  printf("x=%d\n\n", x);

  // test display of 64 bits hex value
  long int bighex = 0xdeadbeef5ee7c0de;
  printf("bighex: %lx\n", bighex);
}
