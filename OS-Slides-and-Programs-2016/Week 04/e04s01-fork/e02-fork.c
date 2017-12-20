/*
 *  Illustrates system call fork
 *  The parent forks and terminates first
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(){
  // Who is the parent of the starting process? 
  fprintf (stdout, "#1: PID=%d; My parent PID=%d\n",
    getpid(), getppid());

  if (fork() == 0){ // Child Goes Here First
    sleep (5);
  }

  // Who is process number 1? 
  fprintf (stdout, "#2: PID=%d; My parent PID=%d\n",
     getpid(), getppid());


  return 0;
}
