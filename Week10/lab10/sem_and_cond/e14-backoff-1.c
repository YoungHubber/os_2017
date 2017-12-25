/*
 * backoff.c
 *
 * Demonstrates deadlock avoidance using "mutex backoff".
 * 
 * uses usleep   (microsleep)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		// for usleep
#include <pthread.h>
#include <errno.h> 		// for EBUSY

#define ITERATIONS 10

/*
 * Initialize a static array of 3 mutexes.
 */
pthread_mutex_t mutex[3] = {
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER
    };
    

/*
 * This is a thread start routine that locks all mutexes 
 * in order. This ensures a conflict with lock_backward, 
 * which does the opposite.
 */
void *
lock_forward (void *arg)
{
    int i, iterate, backoffs;
    int status;

    for (iterate = 0; iterate < ITERATIONS; iterate++) {
        backoffs = 0;
        status = pthread_mutex_lock (&mutex[0]);
        for (i = 1; i < 3; i++) {  
          status = pthread_mutex_trylock (&mutex[i]);
          if (status == EBUSY) {
            backoffs++;
            printf("forward locker backing off at %d\n",i);
            for (; i >= 0; i--) 
              pthread_mutex_unlock (&mutex[i]);
          }
          else
            printf(" forward locker got %d\n", i);
          usleep (rand() % 10);
        }

        printf ("lock forward got all locks, %d backoffs\n", backoffs);
        pthread_mutex_unlock (&mutex[2]);
        pthread_mutex_unlock (&mutex[1]);
        pthread_mutex_unlock (&mutex[0]);
        sleep (1);
  }
  return NULL;
}

/*
 * This is a thread start routine that locks all mutexes in
 * reverse order. This ensures a conflict with lock_forward, 
 * which does the opposite.
 */
void *
lock_backward (void *arg)
{
    int i, iterate, backoffs;
    int status;

    for (iterate = 0; iterate < ITERATIONS; iterate++) {
        backoffs = 0;
        status = pthread_mutex_lock (&mutex[2]);
        for (i = 2; i >= 0; i--) {  
          status = pthread_mutex_trylock (&mutex[i]);
          if (status == EBUSY) {
            backoffs++;
            printf("backward locker backing off at %d\n",i);
            for (; i <3; i++) 
              status = pthread_mutex_unlock (&mutex[i]);
          }
          else
            printf(" backward locker got %d\n", i);
          usleep (rand() % 10);            
        }
        /*
         * Report that we got them, and unlock to try again.
         */
        printf (
            "lock forward got all locks, %d backoffs\n", backoffs);
        pthread_mutex_unlock (&mutex[2]);
        pthread_mutex_unlock (&mutex[1]);
        pthread_mutex_unlock (&mutex[0]);
        sleep (1);
  }
    return NULL;
}

int main (int argc, char *argv[]){
    pthread_t forward, backward;

    pthread_create (&forward, NULL, lock_forward, NULL);
    pthread_create (&backward, NULL, lock_backward, NULL); 
    pthread_exit (NULL);
}
