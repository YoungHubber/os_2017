/*
 *  Install a signal handler and receive a signal from shell.
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

static void sig_usr(int);

int
main (int argc , char ** argv) {
  if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
    fprintf (stderr, "Signal Handler Error.\n");
    return (1);
  }
  if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
    fprintf (stderr, "Signal Handler Error.\n");
    return (1);
  }

  if (argc > 1)
    signal (SIGUSR1, SIG_IGN);


  while (1) {
    if (argc > 1){
      fprintf (stdout, "Before sleep.\n");
      sleep (100);
      fprintf (stdout, "After sleep.\n");
    }
    else {
      fprintf (stdout, "Before pause.\n");
      pause ();
      fprintf (stdout, "After pause.\n");
    }
  }

  return (0);
}

static void sig_usr (int signo) {
  if (signo == SIGUSR1)
    printf("received SIGUSR1\n");
  else if (signo == SIGUSR2)
    printf("received SIGUSR2\n");
  else
    fprintf (stderr, "Received signal %d\n", signo);

  return;
}
