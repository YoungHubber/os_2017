/*

ex301.c
os_lab3
Created by GAO Qiwei on 2017/10/30.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void rescure(int);
void rescure(int deep) {
    if(deep == 0) {
        printf("the leaf pid:%u\n", getpid());
        exit(0);
    }else{
        pid_t fpid = fork();
        if(fpid == 0) {
            printf("the left child pid:%u\n",getpid());
            printf("%u's parent pid is:%u\n", getpid(),getppid());
            rescure(deep-1);
            sleep(100);
            return;
        }else{
            printf("the current pid:%u\n", getpid());
            pid_t pid = fork();
            if(pid ==0) {
                printf("the right child pid:%u\n", getpid());
                printf("%u's parent pid is:%u\n", getpid(),getppid());
                rescure(deep-1);
                sleep(100);
                return;
            }else{
                sleep(100);
                return;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("the number of args is wrong!");
        return -1;
    }
    int deep=atoi(argv[1]);
    rescure(deep);
    sleep(100);
    return 0;
}
