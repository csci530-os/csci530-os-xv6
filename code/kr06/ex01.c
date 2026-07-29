#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

struct stuff {
  char *ptr;     // 8 bytes
  int num1;      // 4 bytes
  short num2;    // 2 bytes
  char byte;     // 1 bytes
  char bytes[8]; // 8 bytes
};

int
main(int argc, char *argv[])
{
  struct stuff s;

  // a bunch of member access operations
  s.ptr = "hello";
  s.num1 = 0x11223344;
  s.num2 = 0x4142; // 2 bytes 0x41 = ascii A, 0x42 = ascii B
  s.byte = 'c';
  s.bytes[0] = 'h';

  // struct is allocated enough bytes to hold all members,
  // NOTE: the ptr and bytes are really pointers, so they are 8 bytes each
  // Question: why is size 24 here, is that what you expected?
  printf("sizeof(s): %ld\n\n", sizeof(s));

  printf("ptr: <%s>\n", s.ptr);
  printf("num1: <%d>\n", s.num1);
  printf("byte: <%c>\n", s.byte);
  printf("\n\n");

  // can have a pointer to a structure, just like any other type
  struct stuff *sp;
  sp = &s;

  // notice use of -> operator, to both dereference and access members
  printf("ptr: <%s>\n", sp->ptr);
  printf("num1: <%d>\n", sp->num1);
  printf("byte: <%c>\n", sp->byte);
  printf("\n\n");

  // we can treat the 23(+) bytes anyway we want, this is both
  // powerful and dangerous stuff

  // We want to treat sp as a pointer to 24 bytes
  // a character * will allow arithmetic by bytes into what it points at
  // NOTE: riscv is little endian, so the 2 byte short least significant
  // byte 0x42 is at lower address 12 offset, and 0x41 will be 13 offset
  char *cp = (char *)&s;
  printf("byte at cp+12: %c\n", *(cp + 12));
  printf("byte at cp+13: %c\n", *(cp + 13));

  // treat the 2 bytes as a short integer
  // NOTE: casting is tricky trying to get specific bytes to display
  // using printf, can be easier to create a temporary pointer of type
  // you need like we do here instead of casting in printf call
  short *num2p = (short *)(cp + 12);
  printf("short at cp+12: 0x%x\n\n", *num2p);

  // same example again, but using 4 byte num1 member
  printf("byte at cp+8 : 0x%x\n", *(cp + 8));
  printf("byte at cp+9 : 0x%x\n", *(cp + 9));
  printf("byte at cp+10: 0x%x\n", *(cp + 10));
  printf("byte at cp+11: 0x%x\n", *(cp + 11));

  int *num1p = (int *)(cp + 8);
  printf("int at cp+8: 0x%x\n\n", *num1p);
}
