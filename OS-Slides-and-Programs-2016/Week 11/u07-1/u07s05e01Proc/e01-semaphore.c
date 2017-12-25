/*
 * Illustrates the implementation of semaphores by means of
 * system call pipe
 * 2 Parameters on command line:
 * - # of process
 * - # of process in CS
 *
*/

#include <stdio.h>		
#include <stdlib.h>
#include <unistd.h>

// Mutual Exclusion semaphore
typedef int * semaphore;
semaphore me;

semaphore make_sem () {
  int *sem;

  sem = calloc (2,sizeof(int));
  pipe (sem);
  return sem;
}

void WAIT (semaphore s) {
  int junk;

  if (read(s[0], &junk, 1) <=0) {
    fprintf(stderr, "ERROR : wait\n");
    exit(1);
  }
}

void SIGNAL(semaphore s) {
  if (write(s[1], "x", 1) <=0) {
    fprintf(stderr, "ERROR : signal\n");
    exit(1);
  }
}

void process (int id) {
  int i;

  for(i=0; i<3; i++) {
    sleep(1);  
    WAIT(me); 
    printf("  Entering critical region of process %d\n", id);
    sleep(2);
    printf("    Exiting critical region of process %d\n", id);
    SIGNAL(me);
  }
  exit (0);
}

int main (int argc, char *argv[]) {
  int np, npSC, i;

  np = atoi (argv[1]);
  npCS = atoi (argv[2]);
  me = make_sem();

  //  initialize sem to npSC
  for(i=0; i<npCS; i++)  {
    SIGNAL(me);
  }

  fprintf (stdout, "\n");
  for (i=0; i<np; i++)  {
    if (fork() == 0) {
      // Child
      fprintf (stdout, " Process %d created.\n", i+1);
      process (i);
    }
  }

  exit(0);
}
