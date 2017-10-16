#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    char c;
    FILE *fp;

    fp=fopen(argv[1],"r");

    if(fp==NULL){
        fprintf(stderr,"error opening file.\n");
        exit(1);
    }
    while(fscanf(fp,"%c",&c)!=EOF){
        printf("%c",c);
    }

    fclose(fp);

    return 0;
}
