/*
 *  mutex.c
 *
 *  Illustrates the use of mutex
 *  for mutual exclusion
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *ME_thread (void *arg)
{
    int status;

    pthread_detach (pthread_self ());

    for(;;) {
      pthread_mutex_lock (&mutex);
           
      printf("critical region of thread  %ld\n", pthread_self());

      pthread_mutex_unlock (&mutex);
      
      sleep(2);
//      sched_yield();    // volountarily releases CPU
    }
    return NULL;
}

int main (int argc, char *argv[])
{
    pthread_t thread;

    // setvbuf (stdout, NULL, _IONBF, 0);
    setbuf(stdout,0);           // no buffering for  stdout
 
    pthread_create (&thread, NULL, ME_thread, NULL);

    pthread_create (&thread, NULL, ME_thread, NULL);

    pthread_exit(NULL);
}
