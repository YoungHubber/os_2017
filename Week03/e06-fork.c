/*
 *  Generation of K children process
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define K 3

int
main (){
  int i;

  fprintf (stdout, "Starting PID=%d\n",  getpid());
  for(i=0; i<K; i++) {
    if (fork() == 0) {
      fprintf (stdout, "Body: Process %d (PID=%d)\n",  i, getpid());
      break;
    }
  }
  fprintf (stdout, "Ending PID=%d (PPID=%d)\n",
     getpid(), getppid());

  exit(0);
}
