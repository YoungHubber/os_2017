#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int i;
    int n=atoi(argv[1]);

    printf("Start pid: %d\n",getpid());

    for(i=0; i<n; i++)
    {
        if(fork())
        {
            if(fork()){
                break;
            }
        }
        if(i==(n-1)){
            printf("child pid: %d.(ppid %d)\n",getpid(),getppid());
        }

    }

    return EXIT_SUCCESS;
}
