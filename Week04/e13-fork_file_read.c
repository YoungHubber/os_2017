#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define NAME "e12in.bin"

int
main () {
  int pid, n;
  int fdi;

#if INDEP

  /*
   * Fork and then open file
   * fp are independent
   */
   
  printf("Two independent file pointers\n");

  pid = fork();

  if (pid==0) {
    /* Child */
    fdi = open (NAME, O_RDONLY);
    while (read(fdi, &n, sizeof(int))) {
      printf ("Child reading %d\n", n);
      sleep (1);
    }
    close (fdi);
  } 
  else {
    /* Parent */
    fdi = open (NAME, O_RDONLY);

    while (read(fdi, &n, sizeof(int))) {
      printf ("Parent reading %d\n", n);
      //sleep (1);
    }
    close (fdi);
  }

#else

  /*
   * Open file and then fork *fp is shared
   */
  printf("Shared file pointer\n");
  
  fdi = open (NAME, O_RDONLY);
  pid = fork();

  if (pid==0) {    // Child
    printf ("Child running ...\n");
    while (read(fdi, &n, sizeof(int))) {
      printf ("Child reading %d\n", n);
      sleep (1);
    }
  } else {   // Parent 
    printf ("Parent running ...\n");
    while (read(fdi, &n, sizeof(int))) {
      printf ("Parent reading %d\n", n);
      sleep (1);
    }
  }

  close (fdi);

#endif

  return (0);
}
