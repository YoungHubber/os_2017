/*

ex303.c
os_lab3
Created by GAO Qiwei on 2017/10/30.

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>

int num =1;
int n;
void rescure(int deep, int* ptr)
{
  if(deep == 1)
  {
    printf("the tree pid:%u  %u  %u  %u\n", ptr[0], ptr[1], ptr[2], ptr[3]);
    exit(0);
  }else
  {
    num *=2;
    pid_t fpid = fork();
    if(fpid == 0)
    {
      ptr[n-deep+1] = num;
      rescure(deep-1, ptr);
    }else
    {
      num +=1;
      pid_t pid = fork();
      if(pid ==0)
      {
        ptr[n-deep+1] = num;
        rescure(deep-1, ptr);
      }else
      {
        sleep(100);
        exit(0);
      }
    }
  }
}


int main(int argc, char* argv[]) {
  if(argc != 2) {
       printf("the number of args is wrong!\n");
       return -1;
    }
  n = atoi(argv[1]);
  int deep= n;
  int *array = calloc(0,sizeof(int)*(n+1));
  array[n-deep] = 1;
  rescure(deep, array);
  return 0;
}