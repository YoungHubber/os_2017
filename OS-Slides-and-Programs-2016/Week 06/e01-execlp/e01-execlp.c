/*
 *
 * Illustrates the use of system calls system and exec
 * l in exec is for list: the arguments are passed in a list
 * p in exec is for PATH: the executable file is searched in
 * the directories listed in PATH
 * The second argument of exec is the name of the process during
 * its running phase, it corresponds to argv[0].
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (
  int argc,
  char ** argv
)
{
  if (execlp ("./e04-argv", "myls", "-l", "-R", "/home", (char *) 0) < 0)
    printf ("error exec\n");

  // NEVER REACHED
  printf ("listing complete !!!\n");

  exit (0);
}
