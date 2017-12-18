#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem1;
sem_t sem2;
sem_t sem3;
sem_t sem4;
sem_t sem5;
sem_t sem6;

static void *readFile (void *);

int main (){
    
    int ret=0,i=0;
    pthread_t tids[6];
    
    if(sem_init (&sem1, 0, 1)!=0){
        printf("Semaphore  initialize failed");
        exit(EXIT_FAILURE);
    }
    if(sem_init (&sem2, 0, 0)!=0){
        printf("Semaphore  initialize failed");
        exit(EXIT_FAILURE);
    }
    if(sem_init (&sem3, 0, 0)!=0){
        printf("Semaphore  initialize failed");
        exit(EXIT_FAILURE);
    }
    if(sem_init (&sem4, 0, 0)!=0){
        printf("Semaphore  initialize failed");
        exit(EXIT_FAILURE);
    }
    if(sem_init (&sem5, 0, 0)!=0){
        printf("Semaphore  initialize failed");
        exit(EXIT_FAILURE);
    }
    if(sem_init (&sem6, 0, 0)!=0){
        printf("Semaphore  initialize failed");
        exit(EXIT_FAILURE);
    }
    
    ret = pthread_create(&tids[0], NULL, readFile,(void*)&"A");
    if (ret)
        printf("Thread creation failed!!\n");exit(EXIT_FAILURE);
    
    ret = pthread_create(&tids[1], NULL, readFile,(void*)&"B");
    if (ret)
        printf("Thread creation failed!!\n");exit(EXIT_FAILURE);
    
    ret = pthread_create(&tids[2], NULL, readFile,(void*)&"C");
    if (ret)
        printf("Thread creation failed!!\n");exit(EXIT_FAILURE);
    
    ret = pthread_create(&tids[3], NULL, readFile,(void*)&"D");
    if (ret)
        printf("Thread creation failed!!\n");exit(EXIT_FAILURE);
    
    ret = pthread_create(&tids[4], NULL, readFile,(void*)&"E");
    if (ret)
        printf("Thread creation failed!!\n");exit(EXIT_FAILURE);
    
    ret = pthread_create(&tids[5], NULL, readFile,(void*)&"F");
    if (ret)
        printf("Thread creation failed!!\n");exit(EXIT_FAILURE);
    
    for (i=0; i<6; i++) {
        pthread_join (tids[i], (void**)&ret);
    }
    
    return 0;
}

static void *readFile (void *arg){
    char* t = (char*)arg;
    int i=0;
    for (i=0; i<10; i++) {
        if (strcmp(t, "A")==0) {
            sem_wait (&sem1);
            printf("A");
            printf("\n");
            sem_post (&sem2);
            sem_post (&sem3);
        }else if (strcmp(t, "B")==0){
            sem_wait (&sem2);
            printf("B");
            printf("\n");
            sem_post (&sem4);
        }else if (strcmp(t, "C")==0){
            sem_wait (&sem3);
            printf("C");
            printf("\n");
            sem_post (&sem4);
        }else if (strcmp(t, "D")==0){
            sem_wait (&sem4);
            sem_wait (&sem4);
            printf("D");
            printf("\n");
            sem_post (&sem1);
        }else{
            pthread_exit ((void *) 1);
            return NULL;
        }
    }
    pthread_exit ((void *) 1);
    return NULL;
}
