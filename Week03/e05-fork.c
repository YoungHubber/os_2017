/*
 *  Generation of K children process
 *  Erroneous use of fork
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define K 3

int
main (){
  int i;

  for (i=0; i<K; i++) {
    fork();
    fprintf (stdout, "Body of process %d and i = %d\n",  getpid(), i);
  }

  exit(0);
}
