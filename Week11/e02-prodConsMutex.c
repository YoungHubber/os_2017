/*
 *  se_with_mutex.c
 *
 *  Illustrates the use of a binary semaphore 
 *  to implement a general semaphore  // does not work on cygwin
 */
#include <pthread.h>
#include "errors.h"


#define BUFFER_SIZE 16
#define OVER (-1)

typedef struct 
{
  int count;	/* the counter */
  pthread_mutex_t lock;		/* mutex ensuring exclusive access to count */
  pthread_mutex_t s;
} Semaphore;

Semaphore *full, *empty;
int in, out;
int buffer[BUFFER_SIZE];

/* Initialize a semaphore */
static void
semaphore_init (Semaphore *s, int i)
{
  pthread_mutex_init (&s->lock, NULL);
  pthread_mutex_init (&s->s, NULL);
  pthread_mutex_lock(&s->s);
  s->count = i;
}

static void
semaphore_wait (Semaphore *s) {
  pthread_mutex_lock (&s->lock);
  s->count--;
  if (s->count < 0){
  	  pthread_mutex_unlock (&s->lock);
      pthread_mutex_lock (&s->s);
  }
  else
    pthread_mutex_unlock (&s->lock);
}

static void
semaphore_signal (Semaphore *s) {
  pthread_mutex_lock (&s->lock);
  s->count++;
  if (s->count <= 0)
    pthread_mutex_unlock (&s->s);
  pthread_mutex_unlock (&s->lock); 
}


/* Store an integer in the buffer */
static void
put (int data){
  semaphore_wait(empty);
  buffer[in] = data;
  in = (in + 1) % BUFFER_SIZE;
  semaphore_signal(full);
}

/* Read and remove an integer from the buffer */
static int
get (void){
  int data;
  
  semaphore_wait(full);
  data = buffer[out];
  out = (out + 1) % BUFFER_SIZE;
  semaphore_signal(empty);
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

  empty = (Semaphore *) malloc(sizeof(Semaphore));
  full = (Semaphore *) malloc(sizeof(Semaphore));
  semaphore_init (empty, BUFFER_SIZE);
  semaphore_init (full, 0);

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



 