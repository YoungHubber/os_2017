/* SCHEDULER with SEMPHORES */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define NPROC 2

typedef int *semaforo;
semaforo clock, psem[2];
int deadline[NPROC];
int interval[NPROC];
int t = 0;
int sem_array[20];
int p_sem_array = 0;

semaforo
make_sem (){
  int *sem;

  sem = &sem_array[p_sem_array];
  p_sem_array++;
  p_sem_array++;
  pipe (sem);
  return sem;
}

void
WAIT (semaforo s){
  int junk;

  if (read (s[0], &junk, 1) <= 0)    {
      fprintf (stderr, "ERROR : WAIT\n");
      exit (1);
    }
}

void
SIGNAL (semaforo s){
  if (write (s[1], "s", 1) <= 0)
    {
      fprintf (stderr, "ERROR : signal\n");
      exit (1);
    }
}

void
proc0 (){
  int i;

  while (1)
    {
      WAIT (psem[0]);
      i = getpid ();
      printf ("Process %d", i);
      system ("date");
    }
}

void
proc1 (){
  int i;

  while (1)
    {
      WAIT (psem[1]);
      i = getpid ();
      printf ("Process %d", i);
      system ("date");
    }
}

void 
catcher (){
  printf ("tick\n");
  SIGNAL (clock);
  signal (SIGALRM, catcher);
}

void
alarm_clock (){
  signal (SIGALRM, catcher);
  while (1)
    {
      alarm (1);
      pause ();
    }
}


int
main (){
  int i;

  clock = make_sem ();
  psem[0] = make_sem ();
  psem[1] = make_sem ();

/*  Scheduler initialization   */
  interval[0] = 5;
  interval[1] = 7;
  deadline[0] = 5;
  deadline[1] = 7;

  if ((i = fork ()) == 0)
    proc0 ();
  if (fork () == 0)
    proc1 ();
  if (fork () == 0)
    alarm_clock ();

  /*       control and  scheduling  */

  while (1)    {
      WAIT (clock);
      t++;
      for (i = 0; i < NPROC; i++)	{
	    if (deadline[i] <= t) 	    {
	      deadline[i] = t + interval[i];
	      printf ("Awake process %d at time %d\n", i, t);
	      SIGNAL (psem[i]);
	    }
	  }
    }
}
