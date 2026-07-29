#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char amessage[] = "now is the time"; // an array, allocated on stack
  char *pmessage =
    "now is the time"; // a pointer string constant in constants section

  amessage[4] = '*';
  printf("<%s>\n", amessage);

  *(pmessage + 4) = '*'; // what happens here?
  printf("<%s>\n", pmessage);
}
