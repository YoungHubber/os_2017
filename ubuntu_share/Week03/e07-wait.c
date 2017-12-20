/*
 *  Illustrates fork, wait and exit return information
 *  Once run: Use 
 *  echo $?
 *  to make the shell display the parent return value (15)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (
  )
{
  pid_t pid, cpid;
  int status;

  fprintf (stdout, "Starting Process: PID=%d\n",  getpid());

  pid = fork();

  if (pid != 0) {
    // parent
    fprintf (stdout, "Parent: PID=%d; ParentPID=%d; ReturnPID=%d\n",
      getpid(), getppid(), pid);
    status = 0;
    sleep (05);
    cpid = wait (&status);
    fprintf (stdout, "Parent Wait: ChildPID=%d Status=%x ", 
      cpid, status);
    fprintf (stdout, "WIFEXITED=%d WEXITSTATUS=%d\n",
      WIFEXITED(status), WEXITSTATUS (status));
    printf("Parent completed\n");
    exit (25);
  } else {
    // Child
    fprintf (stdout, "Child : PID=%d; ParentPPID=%d; ReturnPID=%d\n",
      getpid(), getppid(), pid);
    sleep (10);
    fprintf (stdout, "Child completed\n");
    status = 123;
    exit (6);
  }
}
