#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
	uint32_t count; //to read binary data
	int ch; //to read characters

	//if no arguments are passed, print message and exit with code 1
	if(argc == 1) {
	  fprintf(stdout, "wunzip: file1 [file2 ...]\n");
	  exit(1);
	}

	//loop handling
	/* first check if the file can be opened, if not, print appropriate message
	   if the file can be opened, we then use fread() as long as it returns 1, 
	   indicating that there was a character read. once we reach the EOF, we exit
	   and print the characters.
	*/
	for(int i = 1; i < argc; i++) { 
	  FILE *fp = fopen(argv[i], "rb"); //read in binary
	  if(fp == NULL) {
	    fprintf(stdout, "wunzip: cannot open file\n");
	    exit(1);
	  }

	while(fread(&count, sizeof(uint32_t), 1, fp) == 1) {
	   ch = fgetc(fp);
	   if(ch == EOF) { //close file if we've reached the end of the file
	     fclose(fp);
	     exit(1);
	   }

	//print characters the correct amount of times
	for(uint32_t j = 0; j < count; j++) {
	   putchar(ch);
	}
     	}

    fclose(fp);
}

return 0; //if all successful, exit with code 0
}
