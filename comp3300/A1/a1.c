/*
 * Developer: Dennis Dao
 * Date: May 27, 2022
 * SID: 110010116
 */

// This program copies multiple files in sequential order to a destination file

#include <stdio.h>
#include <stdlib.h>

int main(void){
	// Variables
	int numFiles, read, ok = 0;
	char buffer[100], destName[255];
	FILE *source, *target;

	// Prompt for number of files
	printf("Enter the number of source files used: ");

	while(!ok){
		fgets(buffer, sizeof(buffer), stdin);
		numFiles = atoi(buffer);

		if(numFiles <= 0){
			puts("Invalid input. Try again.");
                        printf("Enter the number of source files used: ");
		}
		else{
			ok = 1;
		}
	}

	// Array of files used, each with a max length of 255 bytes/chars for file name 
	// Rows are the index of file r, where r is the row index.
	// Columns are the length of the file name, max of 255
	char names[numFiles][255];

	// Prompt for 'numFiles' files
	for(int i = 0; i < numFiles; i++){
		printf("Enter a source file: ");
		scanf("%s", names[i]);
		printf("Source file entered: %s\n\n", names[i]);

		// Test whether the file exists or not by attempting to open
		if((source = fopen(names[i], "r")) == NULL){
			printf("Error: %s does not exist or is not a valid file name.\n", names[i]);
			exit(-1);
		}
		fclose(source);
	}

	// Prompt for destination file
	printf("Enter a destination file: ");
	scanf("%s", destName);
	printf("Destination file entered: %s\n\n", destName);

	// Copy the file if it doesn't exist - ie. trying to open for reading should return NULL
	if((target = fopen(destName, "r")) == NULL){
		target = fopen(destName, "w");

		// Go through all numFiles files
		for(int i = 0; i < numFiles; i++){
			source = fopen(names[i], "r");
			// Copy until eof, and repeat until all inputs exhausted
			while(!feof(source)){
        			if((read = fread(buffer, sizeof(char), 100, source)) != 100){
					if(ferror(source)){
						puts("Error: Reading problem");
						exit(-1);
					}
				}
        			if(fwrite(buffer, sizeof(char), read, target) != read){
					puts("Error: Writing problem");
				}
			}
			fclose(source);
		}

        	// Normal termination
        	puts("Copying successful.");
        	fclose(target);
        	exit(0);
	}
	// Terminate if the output file exists
	else{
		printf("Error: The destination file %s already exists.\n", destName);
		exit(-1);
	}
}
