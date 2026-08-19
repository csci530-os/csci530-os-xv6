#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  char *pargv[2];

  pargv[0] = "wc";
  pargv[1] = 0;

  pipe(p);

  if (fork() == 0) {
    close(0);
    dup(p[0]);
    close(p[0]);
    close(p[1]);
    exec("wc", pargv);
  } else {
    close(p[0]);
    write(p[1], "hello world\n", 12);
    close(p[1]);
  }
}