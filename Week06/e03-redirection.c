// Verify standard and error output redirection 
// Use: 
// redirection > standard_out.txt
// redirection 2> error_out.txt
// redirection &> both_out.txt

#include <stdio.h>
#include <stdlib.h>


int
main (int argc, char ** argv){
	
	printf("This goes to standard output\n");
	fprintf(stderr, "This goes to error output\n");
 
  return (0);
}
