#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// swap: interchange v[i] and v[j]
void
swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int
main(int argc, char *argv[])
{
  int i;
  char *wordlist[] = {"charlie", "bravo", "delta", "alfa"};

  // array of 4 (char *) pointers
  printf("sizeof(wordlist): %ld\n", sizeof(wordlist));

  // can access "string" indexed into wordlist
  for (i = 0; i < 4; i++) {
    printf("wordlist[%d] = <%s>\n", i, wordlist[i]);
  }
  printf("\n\n");

  // each item in array is an pointer address to a constant string
  for (i = 0; i < 4; i++) {
    printf("address of wordlist[%d] = 0x%lx\n", i,
           (long unsigned int)(wordlist[i]));
  }
  printf("\n\n");

  // we can perform a selection sort by hand, e.g. item "alfa" needs to be
  // swapped to index 0, then "charlie" to index 2
  swap(wordlist, 0,
       3); // swap charlie and alpha -> [alfa, bravo, delta, charlie]
  swap(wordlist, 2,
       3); // swap delta and charlie -> [alfa, bravo, charlie, delta]
  for (i = 0; i < 4; i++) {
    printf("wordlist[%d] = <%s>\n", i, wordlist[i]);
  }
  printf("\n\n");

  for (i = 0; i < 4; i++) {
    printf("address of wordlist[%d] = 0x%lx\n", i,
           (long unsigned int)(wordlist[i]));
  }
  printf("\n\n");
}
