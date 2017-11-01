/*
 * Illustrates the use of the system calls
 * signal, alarm, and pause 
 */ 

#include <stdio.h>		
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void catcher1 ();
void catcher2 ();

int i = 0;

void
catcher1 (){
  printf("catcher 1: "); fflush (stdout);
  system("date");
  if (i == 1)
    signal (SIGALRM, catcher1);
  else
    signal (SIGALRM, catcher2);
  i = 1-i;
  return;
}

void
catcher2 (){
  printf("catcher 2: "); fflush (stdout);
  system("date");
  if (i == 1)
    signal (SIGALRM, catcher1);
  else
    signal (SIGALRM, catcher2);
  i = 1-i;
  return;
}

int
main (){
  /*
   * declaration for the kernel. It means:
   * I don't want to die (default action)
   * when I receive a SIGALRM signal, instead
   * I will execute function "catcher"
   */
  signal (SIGALRM, catcher1);

  /* alarm interrupt the pause() after 5 sec. The two catchers alternate */
  while(1) {
    alarm(5);
    printf("waiting begins\n"); fflush (stdout);
    pause();
    printf("end wait\n"); fflush (stdout);
  }

  exit(0);
}
