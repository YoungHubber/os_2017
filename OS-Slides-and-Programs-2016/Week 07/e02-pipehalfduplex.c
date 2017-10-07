/*
 * Can we write on both ends of a pipe  (half-duplex)?
 *  yes, but alternatively ...
 *  If you give on the command line:
 *  - P:  the parent writes a sequence of P characters that are read by the child 
 *  - C:  the child  writes a sequence of C characters that are read by the parent 
 *  - PC: parent and child alternate their role of reader and writer
 *  Inserting the sleep calls avoid that sequence of R/W operations are performed by the same process
 *  Eliminating the while(1) loop -> parent waits the child exit.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main (
  int argc,
  char ** argv
  )
{
  int fd[2];
  char c;

  // no buffering
  setbuf (stdout, 0);

  // Create pipe
  pipe (fd);

  if (fork()!=0) {
    while (1) {
      if (strcmp (argv[1], "F")==0 || strcmp (argv[1], "FC")==0) {
        c = 'F';
        fprintf (stdout, "Father Write %c\n", c);
        write (fd[1], &c, 1);
      }
      sleep (2);
      if (strcmp (argv[1], "C")==0 || strcmp (argv[1], "FC")==0) {
        read (fd[0], &c, 1);
        fprintf (stdout, "Father Read %c\n", c);
      }
      sleep (2);
    }
    wait ((int *) 0);
  } else {
    while (1) {
      if (strcmp (argv[1], "F")==0 || strcmp (argv[1], "FC")==0) {
        read (fd[0], &c, 1);
        fprintf (stdout, "Child Read %c\n", c);
      }
      sleep (2);
      if (strcmp (argv[1], "C")==0 || strcmp (argv[1], "FC")==0) {
        c = 'C';
        fprintf (stdout, "Child Write %c\n", c);
        write (fd[1], &c, 1);
      }
      sleep (2);
    }
    exit (0);
  }

   return (0);
}
