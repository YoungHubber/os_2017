
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void  create_file(char *filename, int k){
    FILE  *fp;
    char *txtname = strcat(filename, ".txt");
    if((fp=fopen(txtname,"w"))!=NULL){
        fprintf(fp,"%d", (rand()%(k-1))+1);
        fclose(fp);
    }
}


int main(int argc,char *argv[]){
    if(argc<3){
        perror("you haven't input the filename,please try again!\n");
        exit(EXIT_FAILURE);
    }
    int i,n=atoi(argv[1]),count=1,k=atoi(argv[2]);
    while(n>=10){
        count++;
        n=n/10;
    }
    char* str1 = malloc(sizeof(char)*(count)+3);
    char* str2 = malloc(sizeof(char)*(count)+1);
    if(access("data",0)==-1){
        if (mkdir("data",0777)){
            printf("Creat subdirectory failed!\n");
        }
    }
    if(chdir("data")==0)
        printf("Switch to subdirectory\n");
    for(i=0;i<=n;i++){
        sprintf(str1, "f0");
        sprintf(str2, "%d", i);
        strcat(str1, str2);
        create_file(str1,k);
    }
    
    exit(EXIT_SUCCESS);
}
