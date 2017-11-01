/*
 * execve.c
 * Illustrates the use of system calls system and exec
 * v in exec is for variables: the arguments are passed as a
 * sequence of variables 
 * e in exec is for env: the executable file
 * inherits the shell environment variables
 *
 * Use of system calls system and exec
 * use: execve command arg environment
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (
  int argc,
  char **argv,
  char ** envp
  )
{
  char *arguments[10] = {"name", "-l", "-R", "/", "\0"};

  // Notice complete path
  if (execve ("./u03s04e10-argv", arguments , envp) < 0) {
    printf ("error exec\n");
    exit(1);
  }

  // NEVER REACHED
  printf ("listing complete !!!\n");
  exit (0);
}
