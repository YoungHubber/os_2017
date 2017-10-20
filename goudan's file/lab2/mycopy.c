#include "stdio.h"
int main (int argc, char *argv[])
{
    FILE * file1,*file2;

    file1 = fopen(argv[1],"rb");
    file2 = fopen(argv[2],"wb");
    if(!file1)
    {
        printf("open error\n");
        return 0;
    }
    char c;
    int index = 0;
    fseek(file1,0,SEEK_END);
    int length = ftell(file1);
    //printf("%d\n",length);
    if(!length)
        return 0;
    while(!fseek(file1,index,SEEK_SET))
    {
        fread(&c,1,1,file1);
        fwrite(&c,1,1,file2);
        if(index == length - 1)
        {
            break;
        }
        index++;
    }
    fclose(file1);
    fclose(file2);

    return 0;
}