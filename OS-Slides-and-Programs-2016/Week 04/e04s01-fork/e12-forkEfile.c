#include <stdio.h>
#include <unistd.h>

#define NAME "e12in.txt"

int
main () {
  int pid, n;
  FILE *fp;

#if INDEP

  /*
   * Fork and then open file
   * fp are independent
   */
   
  printf("Two independent file pointers\n");
  setbuf (stdout, 0);

  pid = fork();

  if (pid==0) {
    /* Child */
    fp = fopen (NAME, "r");
    setbuf (fp, 0);
    while (fscanf (fp, "%d", &n) != EOF) {
      printf ("Child reading %d\n", n);
      sleep (1);
    }
    fclose (fp);
  } else {
    /* Parent */
    fp = fopen (NAME, "r");
    setbuf (fp, 0);
    while (fscanf (fp, "%d", &n) != EOF) {
      printf ("Parent reading %d\n", n);
      //sleep (1);
    }
    fclose (fp);
  }

#else

  /*
   * Open file and then fork *fp is shared
   */
  printf("Shared file pointer\n");
  setbuf (stdout, 0);
  fp = fopen (NAME, "r");
  setbuf (fp, 0);

  pid = fork();

  if (pid==0) {    // Child
    printf ("Child running ...\n");
    while (fscanf (fp, "%d", &n) != EOF) {
      printf ("Child reading %d\n", n);
      sleep (1);
    }
  } else {   // Parent 
    printf ("Parent running ...\n");
    while (fscanf (fp, "%d", &n) != EOF) {
      printf ("Parent reading %d\n", n);
      sleep (1);
    }
  }

  fclose (fp);

#endif

  return (0);
}
