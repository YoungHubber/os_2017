
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("the number of args is wrong!");
        return -1;
    }
    int n = atoi(argv[1]);

    int * ptr = malloc(sizeof(int) * n);
    pid_t pid;
    for(int i=0; i != n; ++i) {
        pid = fork();
        if(pid ==0) {
            free(ptr);
            sleep(n-i-1);
            exit(0);
        }
        while (wait((int *)0)!= pid);
    }
    return 0;
}
