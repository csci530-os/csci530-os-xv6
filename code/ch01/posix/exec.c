#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main()
{
  int pid = fork();

  if (pid > 0) {
    printf("parent: child=%d\n", pid);
    pid = wait((int *)0);
    printf("child %d is done\n", pid);
  } else if (pid == 0) {
    printf("child: exec echo\n");
    char *argv[3];
    argv[0] = "echo";
    argv[1] = "hello";
    argv[2] = 0;
    execv("/usr/bin/echo", argv); // does not return unless error
    printf("exec error\n");
  } else {
    printf("fork error\n");
  }
}