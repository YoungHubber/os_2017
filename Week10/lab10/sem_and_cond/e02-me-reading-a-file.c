/* Reads the lines of a file of integers in parallel
 * prints for each thread: 
 * - the sum of the read numbers
 * - the number of lines read 
 * - the sum of all numbers in the file
 *
 * uses nanosleep
 *
 * > /e02-me-reading-a-file 4 file_of_int.txt
 * Thread: 1 Sum=306 #Lines=7
 * Thread: 2 Sum=151 #Lines=4
 * Thread: 3 Sum=388 #Lines=7
 * Thread: 0 Sum=110 #Lines=2
 * Total: Sum=955 #Lines=20
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

#define L 100
typedef struct threadData {
  pthread_t threadId;
  int id;
  FILE *fp;
  int lines;
  int sum;
} threadData ;
static void *readFile (void *);
sem_t sem;

int main (int argc, char *argv[]) {
  int i, nT, total, lines;
  threadData *td;
  void *retval;
  FILE *fp;

  if (argc < 3) {
    fprintf(stderr, "Syntax: %s num_of_threads filename\n", argv[0]);
    exit(1);
  }

  nT = atoi (argv[1]);
  td = (threadData *) malloc(nT * sizeof (threadData));
  if ((fp = fopen (argv[2], "r")) == NULL){
    fprintf (stderr, "Error Opening File %s\n", argv[2]);
    exit (1);
  }
  sem_init (&sem, 0, 1);

  for (i=0; i<nT; i++) {
    td[i].id = i;
    td[i].fp = fp; // Same fp for all threads
    td[i].lines = td[i].sum = 0;
    pthread_create (&(td[i].threadId), NULL, readFile, (void *) &td[i]);
  }
  total = lines = 0;
  for (i=0; i<nT; i++) {
    pthread_join (td[i].threadId, &retval);
    total += td[i].sum;
    lines += td[i].lines;
  }
  fprintf (stdout, "Total: Sum=%d #Lines=%d\n",
    total, lines);
  sem_destroy (&sem);
  fclose (fp);
  return (0);
}

static void *readFile (void *arg){
  int n, retVal;
  threadData *td;
  struct timespec ts;
    
  td = (threadData *) arg;
  
  srand(pthread_self());  
  ts.tv_sec = 0;
  while (1) {
    sem_wait (&sem);
    retVal = fscanf (td->fp, "%d", &n);
    sem_post (&sem);
    if (retVal == EOF) 
      break;
    td->lines++;
    td->sum += n;
    ts.tv_nsec = 10000 * rand() % 10;
    nanosleep (&ts, NULL);  // Delay Threads
  }
  fprintf (stdout, "Thread: %d Sum=%d #Lines=%d\n",
    td->id, td->sum, td->lines);
  pthread_exit ((void *) 1);
}
