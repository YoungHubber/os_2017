#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc,char *argv[])
{
    int i,j;
    int n=atoi(argv[1]);
    pid_t pidGeneration[100];
    int var=1;

    printf("Start pid: %d\n",getpid());

    for(i=0; i<n; i++)
    {
        pidGeneration[i]=var;
        var=var*2;
        if(fork())
        {
            var++;
            if(fork())
            {
                exit(EXIT_SUCCESS);
            }
        }

        if(i==(n-1))
        {
            //printf("child pid: %d.(ppid %d)\n",getpid(),getppid());
            printf("Process tree : ");
            for(j=0; j<n; j++)
            {
                printf("%d ",pidGeneration[j]);
            }
            printf("%d",var);
            printf("\n");
        }

    }

    return EXIT_SUCCESS;
}
