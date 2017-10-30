c/*
 * - a grandchild process can synchronize with its grandparent process?
 * - or every parent process waits only for its chidren?
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int
main (
  )
{
  pid_t pid, retPid;

  setbuf(stdout,0);
  fprintf (stdout, "#Pa: PID=%d ... started\n", getpid());

  pid = fork();
  if (pid > 0) {
    // Parent
    fprintf (stdout, "#Fb: PID=%d ... going to wait\n", getpid());
    //sleep (1);
    retPid = wait ((int *) 0);
    fprintf (stdout, "#Fc: PID=%d ... end-wait, retPID=%d\n", getpid(), retPid);
    exit (0);

  }
  else { //Child
    pid = fork();
    if (pid > 0) { // Child
      fprintf (stdout, "  C1a: pid=%d ... going to sleep\n", getpid());
      // Force child to sleep, then is the parent to wait first
      sleep (10);
      fprintf (stdout, "  C1a: pid=%d ... sleep ended going to wait\n", getpid());
      retPid = wait ((int *) 0);
      fprintf (stdout, "  C1b: PID=%d ... end-wait, retPID=%d\n", getpid(), retPid);
      exit (0);

    }
    else {

      // Child of Child
      fprintf (stdout, "    C11a: PID=%d\n", getpid());
      sleep (1);
      fprintf (stdout, "    C11b: PID=%d ... going to exit\n", getpid());
      exit (0);

    }
  }

  fprintf (stdout, "Never Reached\n");
  return (0);
}
