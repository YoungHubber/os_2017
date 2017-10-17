/*
 * Illustrates the use of separate process address spaces
 * with common inital values
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int
main(){ 
  char c;
  char str[10];

  c = 'X';
  if (fork()) {		// recall 0 in C is FALSE
    // parent != 0
    c = 'P';
    strcpy (str, "parent");
    sleep (5);
  } else {
    // child
    strcpy (str, "child");
  }

  fprintf(stdout, "PID=%d; PPID=%d; c=%c; str=%s\n",
    getpid(), getppid(), c, str);

  exit(0);
}
