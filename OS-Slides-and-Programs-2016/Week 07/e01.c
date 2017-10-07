/*
 *  Illustrates foreground & background commmand in UNIX
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10

int
main (){
  int i;

  for (i=0; i<N; i++) {
    fprintf (stdout, "PID=%d; iteration=%d\n", getpid(), i+1);
    sleep (5);
  }

  return (1);
}

