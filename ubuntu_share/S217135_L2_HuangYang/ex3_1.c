#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    FILE *fpi,*fpo;
    char buffer;

    fpi=fopen(argv[1],"r");
    fpo=fopen(argv[2],"w");

    while(1){
        fread(&buffer,1,1,fpi);
        if(feof(fpi)){
            break;
        }
        fwrite(&buffer,1,1,fpo);
    }

    fclose(fpi);
    fclose(fpo);




    printf("Hello world!\n");
    return 0;
}
