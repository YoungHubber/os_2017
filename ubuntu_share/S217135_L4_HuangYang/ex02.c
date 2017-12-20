#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid,vPid[100];
    int n;
    int i,j,tmp;

    printf("Input the number of process n.:\n");
    scanf("%d",&n);
    printf("parent pid : %d\n",getpid());
    for(i=0; i<n; i++)
    {
        pid=fork();
        if(pid!=0)
        {
            vPid[i]=pid;
        }
        else
        {
            printf("child pid %d\n",getpid());
            sleep(n-i);
            exit(0);
        }
    }

    for(j=0; j<n; j++)
    {
        tmp=waitpid(vPid[j],(int*)0,0);
        printf("vPid ret %d\n",tmp);
    }



}
