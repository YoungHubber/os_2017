#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int fpi,fpo;
    char buffer;

    fpi=open(argv[1],O_RDONLY);
    fpo=open(argv[2],O_WRONLY);

    while(1){
        read(fpi,&buffer,1);
        if(feof(fpi)){
            break;
        }
        write(fpo,&buffer,1);
    }

    close(fpi);
    close(fpo);

    return 0;
}

