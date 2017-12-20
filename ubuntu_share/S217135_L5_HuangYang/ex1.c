#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int n,k;
    int i;
    char str[20];
    time_t t;

    printf("Input n & k for number of files and range of random numbers.\n");
    scanf("%d %d",&n,&k);

    system("mkdir data");
    system("chmod 777 data");

    srand((unsigned) time(&t) );

    for(i=0; i<n; i++)
    {
        FILE *fp;
        sprintf(str,"data/f%d",i);
        fp=fopen(str,"w");
        fprintf(fp,"%d",rand()%k+1);
        fclose(fp);

    }

    return 0;
}
