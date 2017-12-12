#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#define THREAD_NUM 1

void * thread_handler(void *arg);

int main(int argc,char *argv[]){

    if(argc<2){
        perror("The number of args is wrong!\n");
        exit(0);
    }

    int i,slp;
    int *exc;

    slp = atoi(argv[1]);

    pthread_t tid[THREAD_NUM];

    for(i = 0; i < THREAD_NUM; i++){

        pthread_create(&tid[i], NULL, thread_handler, (void *)&slp);

    }

    for(i = 0; i < THREAD_NUM; i++){

        pthread_join(tid[i],(void**)&exc);
        printf("thread id:%lu,exit code:%d\n", (unsigned long)tid[i], *exc);

    }
    return 0;
}

void *thread_handler(void *arg){
    int s = *((int*)arg);
    static int excode;
    printf("process id: %d\tthread id: %lu\n", getpid(),(unsigned long)pthread_self());
    sleep(s);
    scanf("%d",&excode);
    return (void *)(&excode);
}
