/*
 * Parent and child have two separate heaps?
 *
 * Each page that is allocated for the process (be it
 * a virtual memory page that has the stack on it or the heap)
 * is copied for the forked process to be able to access it.
 * Actually, it is not copied right at the start, it is set to
 * Copy-on-Write, meaning once one of the processes (parent or
 * child) try to modify a page it is copied so that they will
 * not harm one-another, and still have all the data from the
 * point of fork() accessible to them.
 * For example, the code pages, those the actual executable
 * was mapped to in memory, are usually read-only and thus are
 * reused among all the forked processes - they will not be copied
 * again, since no one writes there, only read, and so copy-on-write
 * will never be needed.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>

#define MAXBUF 1024
#define NUMCHILD 2

int main(int argc, char *argv[]){
  pid_t pid;
  char *common;
  
  /*Try to see if common can be shared */
  common = (char *) malloc (sizeof (char));
  *common = 'M';
  
  fprintf(stdout, "Caller  : mypid=%d\t *(common):%c\t common:%ld\n",
    getpid(), *common, (long int) common);
  fflush (stdout);

  pid=fork();
  if (pid == 0) {
    fprintf(stdout, "Child 1 : mypid=%d\t *(common):%c\t common:%ld\n",   //piont to diff cell addresss is same but in own domain
      getpid(), *common, (long int) common);
    *common = 'C';
    fprintf(stdout, "Child 2 : mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    fflush (stdout);
    exit (0);
  } else {
    
    sleep(2); // C on *(common) ?? NO
    fprintf(stdout, "Parent 1: mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    fflush (stdout);
    *common = 'P';
    fprintf(stdout, "Parent 2: mypid=%d\t *(common):%c\t common:%ld\n",
      getpid(), *common, (long int) common);
    fflush (stdout);
  }

  return 0;
}
