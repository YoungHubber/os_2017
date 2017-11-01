/*

ex302.c
os_lab3
Created by GAO Qiwei on 2017/10/30.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

void rescure(int deep, int* ptr, int n)
{
    if(deep == 0)
    {
        ptr[n-deep] = getpid();
        printf("the tree pid:%u  %u  %u  %u\n", ptr[0], ptr[1], ptr[2], ptr[3]);
        exit(0);
    }else
    {
        ptr[n-deep] = getpid();
        pid_t fpid = fork();
        if(fpid == 0)
        {
            rescure(deep-1, ptr, n);
            sleep(100);
            return;
        }else
        {
            pid_t pid = fork();
            if(pid ==0)
            {
                rescure(deep-1, ptr, n);
                sleep(100);
                return;
            }else
            {
                sleep(100);
                return;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
       printf("the number of args is wrong!\n");
       return -1;
    }
    int n = atoi(argv[1]);
    int deep= atoi(argv[1]);
    int *array = malloc(sizeof(int)*(pow(2,deep)));
    rescure(deep, array, n);
    sleep(100);
    return 0;
}
