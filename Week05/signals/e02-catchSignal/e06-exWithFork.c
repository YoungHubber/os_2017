/*
 * alarm_fork.c
 *
 * This version of alarm.c uses fork to create a new process to
 * wait for each alarm to expire.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

int
main (int argc, char *argv[])
{
  char line[128];
  int seconds;
  pid_t pid;
  char message[64];

  //  signal(SIGCHLD,SIG_IGN);  // avoids zombie children
  while (1) {
    printf ("Alarm> ");
    if (fgets (line, sizeof (line), stdin) == NULL)
      exit (1);
    if (strlen (line) <= 1)
      continue;
    system ("date");
    /*
     * Parse input line into seconds (%d) and a message
     * (%64[^\n]), consisting of up to 64 characters
     * separated from the seconds by whitespace.
     */
    if (sscanf (line, "%d %64[^\n]", &seconds, message) < 2) {
      fprintf (stderr, "Bad command\n");
    }  else {
      pid = fork ();
      if (pid == (pid_t) -1) {
        fprintf (stderr, "Fork failed\n");
        exit (1);
      }
      if (pid == (pid_t) 0) {
	//		If we are in the child, wait and then print a message
	      sleep (seconds);
	      system ("date");
	      printf ("(%d) %s\n", seconds, message);
	      exit (0);
      }
    }
  }
}
