#include "stdio.h"

int main (int argc, char *argv[])
{
    FILE *fp,*fp2;
    int c;
    
    fp = fopen( argv[1], "r");
    fp2 = fopen( argv[2], "w+");
    
    while ( (c = fgetc(fp)) != EOF){
        fputc(c,fp2);
    }
    
    fclose(fp);
    fclose(fp2);
    
    return 0;
}
