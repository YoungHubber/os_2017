/*
 * Print  argv (all the arguments passed to an executable)
 * Useful to verify which is the executable name after an exec
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (int argc, char **argv,**envp){                 //need envp for environment
  int i;

  printf("argc = %d\n", argc);
  printf("envp[0]=%s\n",envp[0] );

  for (i=0; i<argc; i++) {
    fprintf (stdout,  "%s \n", argv[i]);
    sleep (1);
  }

  exit (0);
}
