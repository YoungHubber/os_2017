#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>

#define MAX_LINE 10000
#define BUFSIZE 1024


typedef struct csort {
    char* name;
    int sum_line;
    int sum_file;
    int pid;
}chsort;

int get_lines(char *);
int get_sum_line(chsort *, int);
int get_sum_file(chsort *, int);

int main(int argc,char *argv[])
{
    if(argc<3){
        perror("The number of args is wrong!\n");
        exit(0);
    }
    int pid = 0;
    int len = 0;
    char subfile[MAX_LINE] = {0};
    int c = atoi(argv[1]);
    int i=0;
    
    DIR * dir;
    FILE *fp;
    struct dirent * ptr;
    int *totptr;
    
    int request_pipe[2],data_pipe[2],answer_pipe[2];
    char buffer1[BUFSIZE + 1], buffer2[BUFSIZE + 1], buffer3[BUFSIZE + 1];
    const char * short_data = "OK"; //for child request
    int c_use=0,tmp=0;
    chsort *totsort;
    
    memset(buffer1, '\0', sizeof(buffer1));
    memset(buffer2, '\0', sizeof(buffer2));
    memset(buffer3, '\0', sizeof(buffer3));
    totsort = malloc(sizeof(totsort)*c);
    totptr = malloc(sizeof(int)*c);
    for (int j=0; j<c; j++) {
        totsort[j].name = malloc(sizeof(char)*BUFSIZE);
        totsort[j].sum_line = 0;
        totsort[j].sum_file = 0;
    }
    
    signal(SIGPIPE, SIG_IGN);
    dir = opendir(argv[2]);
    
    fp=fopen("list.txt", "w+");
    
    while((ptr = readdir(dir)) != NULL)
    {
        if((strcmp(ptr->d_name, ".")!=0) && (strcmp(ptr->d_name,"..")!=0))
            fprintf(fp,"%s\n", ptr->d_name);
    }
    closedir(dir);
    fclose(fp);
    
    fp = fopen("list.txt", "r");
    
    if ((pipe(request_pipe)||pipe(data_pipe)||pipe(answer_pipe)) == 0) {
        for (i=0; i<c; i++) {
            if((pid=fork())!=0){
                totptr[i]=pid;
                continue;
            }else{
                break;
            };
        }
        if (0 == pid){
            if(close(request_pipe[0])<0)
                perror( "req close error\n" );
            if(close(data_pipe[1])<0)
                perror( "data close error\n" );
            if(close(answer_pipe[0])<0)
                perror( "ans close error\n" );
            
            signal(SIGPIPE, SIG_IGN);
            while(1) {
                if(write(request_pipe[1], short_data, strlen(short_data))<=0){
                    perror("son process write request_pipe error");
                    if(errno == EPIPE) {
                        printf("request_pipe write EPIPE\n");
                        break;
                    }
                }else{
                    if(read(data_pipe[0], buffer2, 5)<=0){
                        printf("%s\n",strerror(errno));
                        if(errno == EPIPE) {
                            printf("data_pipe read EPIPE\n");
                            break;
                        }
                    }else{
                        char cmd[256] = {0};
                        char dirname[BUFSIZE] = {0};
                        sprintf(dirname,"%s/%s", argv[2], buffer2);
                        printf("son process sort file:%s\n", buffer2);
                        sprintf(cmd,"sort -n -o %s %s",dirname,dirname);
                        printf("file name：%s\n",dirname);
                        printf("cmd:%s\n", cmd);
                        system(cmd);
                        char answer[BUFSIZE] = {0};
                        char answer_tmp[BUFSIZE] = {0};
                        sprintf(answer, "%d", getpid());
                        strcat(answer, ",");
                        sprintf(answer_tmp, "%d", get_lines(buffer2));
                        strcat(answer, answer_tmp);
                        if(write(answer_pipe[1], answer, strlen(answer))<=0){
                            printf("%s\n",strerror(errno));
                            if(errno == EPIPE) {
                                printf("answer_pipe write EPIPE\n");
                                break;
                            }
                        }else{
                            printf("answer_pipe read successed\n");
                        }
                    }
                }
            }
            close(answer_pipe[1]);
            close(data_pipe[0]);
            close(request_pipe[1]);
            
        }else{
            if(close(request_pipe[1])<0)
                perror( "req close error\n" );
            if(close(data_pipe[0])<0)
                perror( "data close error\n" );
            if(close(answer_pipe[1])<0)
                perror( "ans close error\n" );
            int cnt = 0;
            while(fgets(subfile, MAX_LINE, fp) != NULL){
                printf("%s\n",subfile);
                len = (int)strlen(subfile) - 1;
                if ('\n' == subfile[len]){
                    subfile[len] = '\0';
                }
                if ((strcmp(subfile, ".")!=0) && (strcmp(subfile, "..")!=0)) {
                    if(read(request_pipe[0], buffer1, BUFSIZE)<=0){
                        printf("request_pipe read failed\n");
                        printf("%s\n",strerror(errno));
                    }else{
                        printf("request_pipe read successed\n");
                        printf("short request：%s\n",buffer1);
                        if(write(data_pipe[1], subfile, strlen(subfile))<=0){
                            printf("data_pipe write failed\n");
                            printf("%s\n",strerror(errno));
                        }else{
                            ++cnt;
                            printf("data_pipe write successed\n");
                            printf("data_pipe write filename:%s\n", subfile);
                        }
                    }
                }
                
            }
            close(request_pipe[0]);
            close(data_pipe[1]);
            if(read(answer_pipe[0], buffer3, BUFSIZE)<=0){
                printf("answer_pipe read failed\n");
                printf("%s\n",strerror(errno));
                if(errno == EPIPE) {
                    close(answer_pipe[0]);
                }
            }else{
                printf("answer_pipe read successed:%s\n",buffer3);
                sscanf(buffer3, "%s,%d",totsort[++c_use].name,&tmp);
                totsort[c_use].sum_line += tmp;
                totsort[c_use].sum_file += 1;
                totsort[c_use].pid = pid;
            }
            
            for (int j=0; j<c_use; j++) {
                printf("process name:%s,sort number:%d \n",totsort[j].name,totsort[j].sum_line);
            }
            printf("total sorted file number:%d\ntotal sorted line number:%d\n",get_sum_file(totsort, c_use),get_sum_line(totsort, c_use));
            
        }
    }
    fclose(fp);
    if (pid!=0){
        char cmd[256] = {0};
        sprintf(cmd,"sort -m list.txt all_list.txt");
        system(cmd);
    }
    return 0;
}

int get_lines(char *fn){
    FILE* fp = fopen(fn, "r");
    char buff[BUFSIZE];
    int lines=0;
    while (fgets(buff, BUFSIZE, fp)!=NULL) {
        lines++;
    }
    return lines;
}

int get_sum_line(chsort *cs,int len){
    int i,sum=0;
    for (i=0; i<len; i++) {
        sum+=cs[i].sum_line;
    }
    return sum;
}

int get_sum_file(chsort *cs,int len){
    int i,sum=0;
    for (i=0; i<len; i++) {
        sum+=cs[i].sum_file;
    }
    return sum;
}
