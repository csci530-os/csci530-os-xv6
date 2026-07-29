#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// strcpy (version 1): copy t to s; array subscript version
void
strcpy_v1(char *s, char *t)
{
  int i;

  i = 0;
  while ((s[i] = t[i]) != '\0')
    i++;
}

// strcpy (version 2): copy t to s; pointer version
void
strcpy_v2(char *s, char *t)
{
  while ((*s = *t) != '\0') {
    s++;
    t++;
  }
}

// strcpy (version 3): copy t to s; pointer version 2
void
strcpy_v3(char *s, char *t)
{
  while ((*s++ = *t++) != '\0')
    ; // do nothing
}

// strcpy (version 4): copy t to s; pointer version 3
void
strcpy_v4(char *s, char *t)
{
  while ((*s++ = *t++))
    ; // do nothing
}

int
main(int argc, char *argv[])
{
  char s[50];
  char *t = "This is a string we will copy to buffer s";

  strcpy_v1(s, t);
  printf("V1 The string in s is: <%s>, size: %d\n", s, strlen(s));

  // how does one reset a string?  well we could just set initial character
  // to EOS flag
  s[0] = '\0';
  printf("After reseting, s is: <%s>, size: %d\n", s, strlen(s));
  printf("\n\n");

  strcpy_v2(s, t);
  printf("V2 The string in s is: <%s>, size: %d\n", s, strlen(s));
  s[0] = '\0';
  printf("\n\n");

  strcpy_v3(s, t);
  printf("V3 The string in s is: <%s>, size: %d\n", s, strlen(s));
  s[0] = '\0';
  printf("\n\n");

  strcpy_v4(s, t);
  printf("V4 The string in s is: <%s>, size: %d\n", s, strlen(s));
  s[0] = '\0';
  printf("\n\n");
}
