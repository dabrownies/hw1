#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	//if argc equals 1, meaning the user did not pass any arguments
	//we print a guide statement and exit with code 1
	if(argc == 1) {
	  printf("wgrep: searchterm [file ...]\n");
	  exit(1);
	}

	FILE *fp;
	char *searchTerm = argv[1]; //set searchTerm to the second argument
	char *buffer = NULL;
	size_t bufsize = 0;

	//if only two arguments are passed (the program and searchTerm)
	//we read from stdin
	if(argc == 2) {
	  while(getline(&buffer, &bufsize, stdin) != -1) { //call getline until stdin stream aborts
	    if(strstr(buffer, searchTerm) != NULL) { //search for substring within each buffer line
		printf("%s", buffer);
	    }
	  }
	} else { //argc == 3, meaning all arguments are passed
	    for(int i = 2; i < argc; i++) { //start at index two to read files in turn
		fp = fopen(argv[i], "r");
		if(fp == NULL) { //if file does not exist exit with code 1
		   printf("wgrep: cannot open file\n");
		   exit(1);
		}

	    //if the file can be open, we begin reading lines from the file
	    while(getline(&buffer, &bufsize, fp) != -1) { //call getline until we reach EOF
		if(strstr(buffer, searchTerm) != NULL) {
		   printf("%s", buffer);
		}
	    }
		
	    fclose(fp); //close file

	    }
	  }

	free(buffer); //free buffer
	
	return 0; //if all successful, exit with code 0
     } 
