/**
 * Reverse Copy
 * Developer: Dennis Dao
 * Date: Feb 22, 2021
 * version 1.0
 */

// This reverses the contents of a file to another file

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	// Variables
	FILE *f1, *f2;
	int f1Length;
	char content;

	// Usage
	if(argc != 3){
		printf("Usage: %s a.txt b.txt\n", argv[0]);
		exit(1);
	}

	f1 = fopen(argv[1], "r");
	if(f1 == NULL){
		printf("%s does not exist.\n", argv[1]);
		exit(1);
	}

	f2 = fopen(argv[2], "w");
	if(f2 == NULL){
		printf("Problems opening %s", argv[2]);
		exit(1);
	}

	// Set file1 cursor (a.txt) at the end
	fseek(f1, 0, SEEK_END);
	// Length -1 to avoid printing the EOF character
	f1Length = ftell(f1) - 1;

	// Set the file cursor for f1 up to the offset to get the character
	// Decrement and repeat to read "backwards"
	for(int i = f1Length; i >= 0; i--){
		fseek(f1, i, SEEK_SET);
		content = fgetc(f1);
		fputc(content, f2);
	}
	fclose(f1);
	fclose(f2);
}
