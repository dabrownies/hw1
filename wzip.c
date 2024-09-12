#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
	//helper variables to keep track of repeated characters
	int curr;
	int prev = EOF; //ensure the very first character read per file is never matched
	uint32_t count = 0; //ensure each char count is represented in 4 bytes

	//if no arguments are passed, print message and exit with code 1
	if(argc == 1) {
	  fprintf(stdout, "wzip: file1 [file2 ...]\n");
	  exit(1);
	}

	/* loop handling
	   we first check if the file can be opened. if a file fails to open at any
	   point during the iteration, we exit with code 1. essentially, wzip will run and output compressed files
	   until completion or until a file was unable to be read.
	*/
	for(int i = 1; i < argc; i++) {
	  FILE *fp = fopen(argv[i], "r");
	  if(fp == NULL) {
	    fprintf(stdout, "wzip: cannot open file\n");
	    exit(1);
	  }

		//read in file input by each character
		while( (curr = fgetc(fp)) != EOF) { //set curr to the current character in the file
		   if(curr == prev) { //indicates there is a repeated sequence
		     count++;
		   } else { //indicates end of a char sequence
			if(count > 0) { //only write to output if there is something to print
			  fwrite(&count, sizeof(uint32_t), 1, stdout);
			  fputc(prev, stdout);
			}
	
			//this will either keep track of a character sequence or,
			//signify the beginning of sequence (will reset counter when reading a new file)
			prev = curr;
			count = 1;
		   }
		}
	  fprintf(stdout, "\n");
	  fclose(fp);
	}

   return 0;
}
