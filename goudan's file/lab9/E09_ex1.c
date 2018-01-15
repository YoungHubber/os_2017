#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#include <dirent.h>

#define L 100

typedef struct threadData {
    pthread_t threadId;
    FILE *fp;
    int sum;
} threadData ;


static void *readFile (void *);
char **matrix_init(int);
sem_t sem;



 int main (int argc, char *argv[]) {
     if(argc<2){
         perror("The number of args is wrong!\n");
         exit(0);
     }
     
     DIR * dir;
     FILE *fp;
     struct dirent * ptr;
     int lines,i=0;
     char **array;
     char *filename,*command;
     int t,*retval;
     threadData *td;
     
     
     dir = opendir(argv[2]);
     
     fp=fopen("list.txt", "w+");
     
     while((ptr = readdir(dir)) != NULL){
         fprintf(fp,"%s\n", ptr->d_name);
     }
     closedir(dir);
     fclose(fp);
     fp = fopen("list.txt", "r");
     
     lines = system("wc -l list.txt");
     array = matrix_init(lines);
     filename = (char*)malloc(sizeof(char)*L);
     command = (char*)malloc(sizeof(char)*L);
     while(fscanf(fp, "%s",filename)!=EOF)
         array[i++]=strdup(filename);
     
     sem_init (&sem, 0, 1);
     t = atoi(argv[1]);
     td = (threadData *) malloc(t * sizeof (threadData));
     
     for (i=0; i<t; i++) {
         td[i].fp = fp;
         pthread_create (&(td[i].threadId),NULL,readFile,(void *) &td[i]);
     }
     
     for (i=0; i<t; i++) {
         pthread_join (td[i].threadId, (void**)&retval);
         printf("id:%ul,number:%d", (unsigned int)td[i].threadId,td[i].sum);
     }
     
     fseek(fp, 0, 0);
     while (fscanf (td->fp, "%s", filename)!=EOF) {
         sprintf(command,"cat %s >> all_sorted.txt",filename);
         system(command);
     }
     sprintf(command,"sort -m all_list.txt all_list.txt");
     system(command);
     
     fclose(fp);
     
 }

char **matrix_init(int n){
    char **m;
    int i,j;
    m = (char**)malloc(sizeof(char*)*n);
    for (i=0; i<n; i++) {
        m[i] = (char*)malloc(sizeof(char)*n);
    }
    
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            m[i][j]='\0';
        }
    }
    
    return m;
}

static void *readFile (void *arg){
    threadData *td=(threadData *)arg;
    char *filename,*cmd;
    int retVal;
    int number=0;
    
    filename = (char*)malloc(sizeof(char)*L);
    cmd = (char*)malloc(sizeof(char)*L);
    while (1) {
        sem_wait (&sem);
        retVal = fscanf (td->fp, "%s", filename);
        sem_post (&sem);
        if (retVal == EOF)
            break;
        sprintf(cmd,"wc -l %s",filename);
        system(cmd);
        number++;
        sleep (1);
    }
    td->sum=number;
    return NULL;
}
