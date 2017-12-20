/*
 * Implements the following precedence graph
 *    |<-----
 *    A     |
 *  /   \   |
 * B     C  |
 *  \   /   |
 *    D     |
 *    ------|
 * with threads and POSIX semaphores.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "pthread.h"
#include "semaphore.h"

sem_t *sem1, *sem2, *sem3, *sem4;
  
int random_time(int max){
  return (int)(rand() % max) + 1;
}	

static void *
B (void *arg){
  while (1){
    sem_wait (sem2);  
    printf ( "B \n");
    sem_post (sem4);
  }
  return  0;
}
	

static void *
C (void *arg){
  while (1){
    sem_wait (sem3);  
    printf ( "C \n");
    sem_post (sem4);
  }
  return  0;
}
	
static void *
D (void *arg){
  int t;

  while (1){
    sem_wait (sem4); 
    sem_wait (sem4);   
    printf ( "D \n");

    t = random_time(5);
    printf("sleep %d seconds\n", t);
    sleep(t);
    sem_post(sem1);
  }
  return  0;
}

int
main (void){
  pthread_t th_b, th_c, th_d;
   
  srand(getpid());
  sem1 = (sem_t *) malloc(sizeof(sem_t));
  sem2 = (sem_t *) malloc(sizeof(sem_t));
  sem3 = (sem_t *) malloc(sizeof(sem_t));
  sem4 = (sem_t *) malloc(sizeof(sem_t));
  sem_init (sem1, 0, 1);
  sem_init (sem2, 0, 0);
  sem_init (sem3, 0, 0);
  sem_init (sem4, 0, 0);

  // sleep(random_time(10));
  pthread_create (&th_b, NULL, B, (void *) 0);
  pthread_create (&th_c, NULL, C, (void *) 0);
  pthread_create (&th_d, NULL, D, (void *) 0);

  while (1){
    sem_wait (sem1);
    printf("A\n");
    sem_post (sem2);
    sem_post (sem3);
  }

  pthread_exit(0);
}
