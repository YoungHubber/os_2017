/*
 * cond.c
 *
 * Demonstrate a simple condition variable wait.
 * Remark:
 *   pthread_cond_wait performs 
 *   mutex unlock and then blocks the thread
 *   when the control returns to thread the mutex is locked 
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct my_struct_tag {
    pthread_mutex_t     mutex;  /* Protects access to value */
    pthread_cond_t      cond;   /* Signals change to value */
    int                 value;  /* Access protected by mutex */
} my_struct_t;

my_struct_t data = {
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 0};

int hibernation = 1;            /* Default to 1 second */

/*
 * Thread start routine. It will set the main thread's predicate
 * and signal the condition variable.
 */
void *
wait_thread (void *arg){
    int status;

    sleep (hibernation);
    status = pthread_mutex_lock (&data.mutex);
    data.value = 1;             /* Set predicate */
    status = pthread_cond_signal (&data.cond);
    status = pthread_mutex_unlock (&data.mutex);

    return NULL;
}

int main (int argc, char *argv[]){
    int status;
    pthread_t wait_thread_id;
    struct timespec timeout;

    /*
     * If an argument is specified, interpret it as the number
     * of seconds for wait_thread to sleep before signaling the
     * condition variable.  You can play with this to see the
     * condition wait below time out or wake normally.
     */
    if (argc > 1)
        hibernation = atoi (argv[1]);

    pthread_create (&wait_thread_id, NULL, wait_thread, NULL);

    /*
     * Wait on the condition variable for 2 seconds, or until
     * signaled by the wait_thread. Normally, wait_thread
     * should signal. If you raise "hibernation" above 2
     * seconds, it will time out.
     */
    timeout.tv_sec = time (NULL) + 2;
    timeout.tv_nsec = 0;
    status = pthread_mutex_lock (&data.mutex);

    while (data.value == 0) {
        status = pthread_cond_timedwait (
            &data.cond, &data.mutex, &timeout);
        if (status == ETIMEDOUT) {
            printf ("Condition wait timed out.\n");
            break;
        }
        else if (status != 0){
        		fprintf(stderr, "%d , Wait on condition", status);
            return 1;
        }
    }

    if (data.value != 0)
        printf ("Condition was signaled.\n");
    status = pthread_mutex_unlock (&data.mutex);

    return 0;
}
