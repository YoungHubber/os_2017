/*
 *  If argc > 1 
 *  wait for the end of all its offsprings
 *  else
 *  wait for the end of any offspring
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define deltaT 2

int main (
  int argc,
  char **argv
  )
{
  int i, ret, code;

  // Ignore the child termination 
  if (argc > 1)
    signal (SIGCHLD, SIG_IGN);

  for (i=1; i<6; i++)
    if (fork() == 0) {
      // child
      sleep (i*deltaT);
      printf ("Child #=%d PID=%d slept for %d seconds\n", i, getpid(), i*deltaT);
      // exit with code i
      exit (i);
  }

  // Allows some childs to terminate
  sleep (5);
  ret = wait (&code);
  printf ("Wait: ret = %d code = %x\n", ret, code);

  return (0);
}
