#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid,pidP2,pidP3,pidP4,pidP5,p,q,r;
    int num;
    int status;

    printf("P10 PID:%d\n",getpid());
    printf("P11 PID:%d\n",getpid());
    pidP2=fork();  //p10
    if(pidP2==0)    //p2
    {
        pid=getpid();
        printf("P2 PID:%d\n",pid);
        //sleep(1);
        exit(0);
    }
    else     //p10
    {
	pidP3=fork();
        if(pidP3==0)    //p3
        {
            pid=getpid();
            printf("P3 PID:%d\n",pid);
            //sleep(2);
            exit(0);
        }


    }
    p=waitpid(pidP2,(int*)0,0);
    printf("rec is %d\n",p);
    q=waitpid(pidP3,(int*)0,0);
    printf("rec is %d\n",q);

    printf("P13 PID:%d\n",getpid());

    pidP4=fork();
    if(pidP4==0)   //p4
    {
        pid=getpid();
        printf("P4 PID:%d\n",pid);
        //sleep(2);
        exit(0);
    }
    else
    {
	pidP5=fork();
        if(pidP5==0)
        {
            pid=getpid();
            printf("P5 PID:%d\n",pid);
            printf("Input a 8-bit number:\n");
            scanf("%d",&num);
            exit(num);
        }

        r=waitpid(pidP5,&status,0);
        printf("check for p5 rec is %d\n",r);
        printf("The termination code of p5 is %x\n",status);
        printf("P14 PID:%d",getpid());
    }

    return 0;
}
