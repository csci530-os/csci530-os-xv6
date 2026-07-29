#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// echo command line arguments
int
main(int argc, char *argv[])
{
  int i;

  for (i = 0; i < argc; i++)
    printf("argv[%d]: <%s>\n", i, argv[i]);
}
