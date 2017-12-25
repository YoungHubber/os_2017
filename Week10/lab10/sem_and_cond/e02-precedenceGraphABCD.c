/*
 * Implements the following precedence graph
 *   A
 *  /  \
 * B    C
 *  \  /
 *   D
 * with threads and POSIX semaphores.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "pthread.h"

sem_t *sem1, *sem2;
  
int random_time (int max) {
  return (int)(rand() % max) + 1;
}	

static void *
B (void *arg){
  int *t = (int *) arg;
 
  sem_wait (sem1); 
  sleep (*t);
  printf ( "B after %d seconds\n", *t);
  sem_post (sem2);
  return  0;
}
	

static void *
C (void *arg){
  int *t = (int *) arg;

  sem_wait (sem1);  
  sleep(*t);
  printf ( "C after %d seconds\n", *t);
  sem_post (sem2);
  return  0;
}
	
static void *
D (void *arg){
  sem_wait (sem2); 
  sem_wait (sem2);   
  printf ( "D \n");
  return  0;
}
	

int
main (void){
  pthread_t th_b, th_c, th_d;
  int *rt;
   
  srand(getpid());
  rt = (int *) malloc(sizeof(int)*2);
  sem1 = (sem_t *) malloc(sizeof(sem_t));
  sem2 = (sem_t *) malloc(sizeof(sem_t));
  sem_init (sem1, 0, 0);
  sem_init (sem2, 0, 0);
 
  // sleep(random_time(10));
  rt[0] = random_time(5);
  pthread_create (&th_b, NULL, B, (void *) &rt[0]);
  rt[1] = random_time(5);
  pthread_create (&th_c, NULL, C, (void *) &rt[1]);
  pthread_create (&th_d, NULL, D, 0);

  printf("A\n");
  sem_post (sem1);
  sem_post (sem1);

  pthread_exit(0);
}
