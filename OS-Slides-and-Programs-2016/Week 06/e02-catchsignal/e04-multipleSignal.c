/*
 *  Install a signal handler and receive signal from shell.
 *  Run from shell in background and then:
 *  kill -USR1/-USR2/-KILL/-SIGUSR1/-SIGUSR2/-SIGKILL pid
 *
 *  Show:
 *  - managing different signal
 *  - ignore signal
 *  - use sleep and pause
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sigUsr1 (int);
static void sigUsr2 (int);

static void
sigUsr1 (int signo) {
  if (signo == SIGUSR1)
    printf("Received SIGUSR1\n");
  else
    printf("Received wrong SIGNAL\n");

  fprintf (stdout, "sigUsr1 sleeping ...\n");
  sleep (5);
  fprintf (stdout, "... sigUsr1 end sleeping.\n");

  return;
}

static void
sigUsr2 (
  int signo
) {
  if (signo == SIGUSR2)
    printf("Received SIGUSR2\n");
  else
    printf("Received wrong SIGNAL\n");

  fprintf (stdout, "sigUsr2 sleeping ...\n");
  sleep (5);
  fprintf (stdout, "... sigUsr2 end sleeping.\n");

  return;
}

int
main () {
  if (signal(SIGUSR1, sigUsr1) == SIG_ERR) {
    fprintf (stderr, "Signal Handler Error.\n");
    return (1);
  }
  if (signal(SIGUSR2, sigUsr2) == SIG_ERR) {
    fprintf (stderr, "Signal Handler Error.\n");
    return (1);
  }

  while (1) {
    fprintf (stdout, "Before pause.\n");
    pause ();
    fprintf (stdout, "After pause.\n");
  }

  return (0);
}
