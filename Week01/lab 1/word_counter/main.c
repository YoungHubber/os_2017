#include<stdio.h>
#include<ctype.h>

int main(int argc,char *argv[] ){
	char character;
	int word = 0;
	int space = -1;

	// Temporary variable introduced to understand when a word starts

	int tmp = 0;

	FILE *fp;
	if(argc!=2){
        printf("error number of argument\n");
	}

	fp=fopen(argv[1],"r");
    if(fp==NULL){
        printf("err open the file!\n");
    }

	while( character !=EOF){
		character = fgetc(fp);

	// Check if character is a space
	if( isspace(character)){
		space++;   // if it then increments the spacing variable
		if(tmp > 0){
			word++;   // if the end of a word then also increases the variable word
			tmp=0;    // reset flag checking whether a word has been started
		}
	}

	// Check if the character is alphanumeric
    if ( isalpha (character) ){
			tmp++; // also increases the word flag
		}
	}

	printf("there are %d words",word);

	fclose(fp);


    return 0;
}
