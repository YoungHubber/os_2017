#include <stdio.h>
int i, j, *pk; // global variables initialized to 0
int main(){
scanf("%d", &i);
j=2;
j = j / i; // possible division by 0 exception
printf("%d\n", j);
// Correct program
pk = &i; // pk set to the address of variable i
scanf("%d", pk);
printf("i contains: %d %d\n", i, *pk);
// Program generates here a memory violation exception
pk = 0;
scanf("%d", pk);// tries to write where pk points to,
// a memory location out of user domain
printf("i contains: %d %d\n", i, *pk);
return 0;
}
