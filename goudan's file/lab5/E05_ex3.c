#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_LINE 10000


int main(int argc,char *argv[])
{
    if(argc<3){
        perror("The number of args is wrong!\n");
        exit(0);
    }
    int pid = 0;
    int len = 0;
    char buf[MAX_LINE] = {0};
    int max = atoi(argv[1]);
    int * maxptr = malloc(sizeof(int) * max);
    int i=0;
    char *dirname = strcat(argv[2],"/");

    DIR * dir;
    FILE *fp;
    struct dirent * ptr;
    //    char file_list[100][40];
    //    int i=0;
    dir = opendir(argv[2]);

    fp=fopen("list.txt", "w+");

    while((ptr = readdir(dir)) != NULL)
    {
        fprintf(fp,"%s\n", ptr->d_name);
    }
    closedir(dir);
    fclose(fp);


    fp = fopen("list.txt", "r");
    while(fgets(buf, MAX_LINE, fp) != NULL)
    {
        len = (int)strlen(buf) - 1;
        if ('\n' == buf[len])
        {
            buf[len] = '\0';
        }

        if ((strcmp(buf, ".")!=0) && (strcmp(buf, "..")!=0)) {
            pid = fork();

            if (0 == pid)
            {
                // execlp("sort", "-n","-k", "1", "-u", "-o", strcat(dirname,buf),dirname, (char*)NULL);
                char *ars[] = {"sort", "-n -k 1 -u -o", strcat(dirname,buf),dirname, (char*)NULL};
                execv("sort",ars);
                printf("error2\n");
                return 1;
            }else{
                maxptr[i++]=pid;
            }
            if(i>=max){
                for(int j=0;j!=max; ++j) {
                    waitpid(maxptr[j], NULL, 0);
                }
            }
        }
    }
    fclose(fp);
    execlp("sort", "-n","-k", "1", "-u", "-o", "list.txt", "list.txt", (char*)NULL);
    return 0;
}

