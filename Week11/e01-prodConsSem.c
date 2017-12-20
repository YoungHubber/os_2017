#include <stdio.h>
#include "pthread.h"
#include "semaphore.h"

#define BUFFER_SIZE 16
#define OVER (-1)

sem_t *empty, *full;
int in, out;
int buffer[BUFFER_SIZE];



/* Store an integer in the buffer */
static void
put (int data){
  sem_wait(empty);
  buffer[in] = data;
  in = (in + 1) % BUFFER_SIZE;
  sem_post(full);
}

/* Read and remove an integer from the buffer */
static int
get (void){
  int data;
  
  sem_wait(full);
  data = buffer[out];
  out = (out + 1) % BUFFER_SIZE;
  sem_post(empty);
  return data;
}

/* A test program: one thread inserts integers from 0 to 9999,
   the other reads them and prints them. */

static void *
producer (void *data){
  int n;
  for (n = 0; n < 10000; n++) {
      printf ("%d --->\n", n);
      put (n);
    }
  put (OVER);
  return NULL;
}

static void *
consumer (void *data){
  int d;
  while (1){
      d = get();
      if (d == OVER)
	      break;
      printf ("<--- %d\n", d);
    }
  return NULL;
}

int
main (void){
  pthread_t th_a, th_b;
  void *retval;

  empty = (sem_t *) malloc(sizeof(sem_t));
  full = (sem_t *) malloc(sizeof(sem_t));
  sem_init (empty, 0, BUFFER_SIZE);
  sem_init (full, 0, 0);
  in = 0;
  out = 0;
  /* Create the threads */
  pthread_create (&th_a, NULL, producer, 0);
  pthread_create (&th_b, NULL, consumer, 0);
  /* Wait until producer and consumer finish. */
  pthread_join (th_a, &retval);
  pthread_join (th_b, &retval);
  return 0;
}

