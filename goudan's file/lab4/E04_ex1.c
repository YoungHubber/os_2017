#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void p32();
int main () {
    pid_t pid;
    int n;
    printf ("p10\n");
    if ( (pid = fork())==-1 )
        printf("can't fork");
    if ( pid == 0 ){
        p32();
    }else {
        printf ("p11\n");
        while (wait((int *)0)!= pid);
    }
    printf ("p13\n");
    if ( (pid = fork())==-1 )
        printf("can't fork");
    if ( pid == 0 ){
        printf("Please input a number between -128 and 127:\n");
        scanf("%d",&n);
        printf ("p5\n");
        exit(0);
    }else {
        printf ("p4\n");
        while (wait((int *)0)!= pid);
    }
    printf ("p14\n");
    return(n);
}

void p32() {
    pid_t pid;
    if ( ( pid = fork() ) == -1 )
        printf("can't fork");
    if (pid > 0 ){
        printf ("p2\n");
        while (wait((int *)0)!=pid );
    } else {
        printf ("p3\n");
        exit (0);
    }
    exit (0);
}