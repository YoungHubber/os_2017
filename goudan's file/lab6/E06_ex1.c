#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_SIZE 1024

void sUser1();
void sAlrm();
void pchild();

int n=0;

int main( int argc, char ** argv ){
    int pid;
    char buff[MAX_SIZE+1];
    sigset( SIGUSR1, sUser1);
    sigset( SIGALRM, sAlrm);
    FILE *fp = fopen(argv[1], "r");
    
    pid = fork();
    if (pid==0) {
        pchild();
    }else{
        while (fgets(buff, MAX_SIZE, fp)!=NULL) {
            sleep(1);
            if ((n%2)==0) {
                printf("parent n=%d\n",n );
                printf("%s\n",buff);
            }
        }
    }
    return 0;
}

void pchild(){
    int r;
    r = rand()%(10-1)+1;
    alarm(60);
    while (1) {
        if(getppid()==1)
            exit(EXIT_SUCCESS);
        else{
            sleep(r);
            kill(getppid(), SIGUSR1);
        }
    }
    return;
}

void sUser1(){
    n+=1;
    printf("child changed n=%d\n",n );
    return;
}

void sAlrm(){
    int i = 0;
    char cmd[256];
    sprintf(cmd,"kill -9 %d",getpid());
    i = system(cmd);
    return;
}
