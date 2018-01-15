#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>


static void *readFile (void *);
sem_t sem;
double *a,*b,*ans;
int homeworks[10]={0},homeworks_done[10]={0};
int vec_index=0,hm_index=0;
void s_quit();


int main (int argc, char *argv[]) {
    if(argc<3){
        perror("The number of args is wrong!\n");
        exit(0);
    }
    int n,t,i,j,k;
    double dnum;
    n=atoi(argv[1]);
    t=atoi(argv[2]);
    signal(SIGQUIT, s_quit);

    pthread_t tids[t];

    a=(double*)malloc(sizeof(double)*n);
    b=(double*)malloc(sizeof(double)*n);
    ans=(double*)calloc(sizeof(double)*n,0);

    sem_init (&sem, 0, 1);

    for (i=0; i<t; i++) {
        pthread_create (&(tids[i]),NULL,readFile,NULL);
    }
    for (i=0; i<10; i++) {
        sem_wait (&sem);
        vec_index=0;
        for (j=0; i<n; j++) {
            dnum = rand()/(double)(RAND_MAX);
            a[j] = dnum;
            dnum = rand()/(double)(RAND_MAX);
            b[j] = dnum;
        }
        homeworks[i]=1;
        sem_post (&sem);
        printf("homework[%d]:\n",hm_index);
        while (!homeworks_done[i]);
        printf("homework[%d] dot product:%lf\n",hm_index-1,ans[hm_index-1]);
    }
    for (i=0; i<t; i++) {
        pthread_kill(tids[i],SIGQUIT);
    }

    return 0;
}

static void *readFile (void *arg){

    double ai,bi,abi;

    while (1) {
        while (!homeworks[hm_index]); //
        sem_wait (&sem);
        ai = a[vec_index];
        bi = b[vec_index];
        abi = ai*bi;
        printf("%lf ",abi);
        vec_index++;
        ans[hm_index]+=abi;
        if (vec_index == 10){
            homeworks_done[hm_index]=1;
            hm_index++;
        }
        sem_post (&sem);
        sleep (1);
    }
    return NULL;
}

void s_quit(){
    exit(EXIT_SUCCESS);
}
