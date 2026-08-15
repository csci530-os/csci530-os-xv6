#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid = fork();

  if (pid > 0) {
    printf("parent: child=%d\n", pid);
    pid = wait((int *)0);
    printf("child %d is done\n", pid);
  } else if (pid == 0) {
    pause(10);
    printf("child: exec echo\n");
    char *argv[3];
    argv[0] = "echo";
    argv[1] = "hello";
    argv[2] = 0;
    exec("echo", argv); // does not return unless error
    printf("exec error\n");
  } else {
    printf("fork error\n");
  }
}