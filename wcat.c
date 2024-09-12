#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (512)

int main(int argc, char *argv[]) {
	//if file param is empty exit with code 1
	if(argc == 1) {
	   exit(1);
	}

	//loop handling
	for(int i = 1; i < argc; i++) {
	   FILE *fp = fopen(argv[i], "r");
	   if(fp == NULL) {
	     //if file does not exist exit with code 1
	     printf("wcat: cannot open file\n");
	     exit(1);
	}

	//print file contents
	char buffer[BUFFER_SIZE];
	while(fgets(buffer, BUFFER_SIZE, fp) != NULL) {
	   printf("%s", buffer);
	}

	//close file
	fclose(fp);

    	} //end loop

   //exit with code 0 if successful
   return 0;
}
