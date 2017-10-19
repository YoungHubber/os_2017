#include <sys/stat.h> 
#include <sys/types.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 

int main (int argc, char *argv[])
{
    int file1,file2;

    file1 = open(argv[1],O_RDONLY);
    file2 = open(argv[2],O_WRONLY);
    if(!file1)
    {
        printf("open error\n");
        return 0;
    }
    char c;
    int index = 0;
    lseek(file1,0,SEEK_END);
    int length = lseek(file1, 0, SEEK_CUR);

    if(!length)
        return 0;
    while(!lseek(file1,index,SEEK_SET))
    {
        read(file1,&c,1);
        write(file2,&c,1);
        if(index == length - 1)
        {
            break;
        }
        index++;
    }
    close(file1);
    close(file2);

    return 0;
}