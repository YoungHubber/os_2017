/*
 *  Precedence graph with signal, kill & pause
 *  and race conditions !!!
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

static void sigUsr (int);
void S1 (pid_t);
void S2 ();

static void
sigUsr (
  int signo
) {
  if (signo == SIGUSR1)
    fprintf (stdout, "Received SIGUSR1\n");
  else if (signo == SIGUSR2)
    fprintf (stdout, "Received SIGUSR2\n");
  else
    fprintf (stderr, "Received signal %d\n", signo);

  return;
}

int
main (
  void
) {
  pid_t pid;

  if (signal(SIGUSR1, sigUsr) == SIG_ERR) {
    fprintf (stdout, "Signal Handler Error.\n");
    return (1);
  }
  if (signal(SIGUSR2, sigUsr) == SIG_ERR) {
    fprintf (stdout, "Signal Handler Error.\n");
    return (1);
  }

  fprintf (stdout, "P20\n");

  pid = fork ();
  if (pid == (pid_t) -1) {
    // Error
    fprintf (stdout, "Fork failed\n");
    exit (1);
  }
  if (pid > (pid_t) 0) {
    // Father
    S1 (pid);
    //while (wait ((int *) 0 != pid);
    wait ((int *) 0);
  } else {
    // Child
    S2 ();
    exit (0);
  }

  fprintf (stdout, "P25\n");

  return (0);
}

void S1 (
  pid_t cpid
) {
  fprintf (stdout, "P11\n");
  sleep (1);
  kill (cpid, SIGUSR1);
  fprintf (stdout, "P12\n");
  pause ();
  fprintf (stdout, "P13\n");

  return;
}

void S2 (
  )
{
  pid_t pid;

  pid = fork ();
  if (pid == (pid_t) -1) {
    // Error
    fprintf (stdout, "Fork failed\n");
    exit (1);
  }
  if (pid > (pid_t) 0) {
    // Parent
    fprintf (stdout, "P21\n");
    // Sleeping here means sleeping forever
    // sleep (2);
    pause ();
    kill (getppid (), SIGUSR2);
    fprintf (stdout, "P23\n");
    wait ((int *) 0);
  } else {
    // Child
    fprintf (stdout, "P22\n");
    exit (0);
  }

  fprintf (stdout, "P24\n");
  return;
}
