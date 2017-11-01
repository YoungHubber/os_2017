/*
 *
 * Illustrates the use of system calls system
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main (
  )
{
  char str[10];

  fprintf (stdout, "DATE:\n");
  system ("date");                     //fork a child and exec given argu ,and parent wait the exec sync procedure 

  fprintf (stdout, "LS:\n");	
  system ("ls");

  fprintf (stdout, "LS -LAR:\n");	
  strcpy (str, "ls -laR .");
  system (str);

  exit (0);
}
