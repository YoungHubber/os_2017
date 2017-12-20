/*
 *  Illustrates system call fork
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main (){
  fprintf (stdout, "#1: PID=%d; My parent PID=%d\n",
    getpid(), getppid());

  fork();

  // If processes sleep they can be seen with command ps ...
  //sleep (5);

  fprintf (stdout, "#2: PID=%d; My parent PID=%d\n",
    getpid(), getppid());

  return (1);
}

