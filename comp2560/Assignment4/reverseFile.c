/**
 * Reverse File
 * Developer: Dennis Dao
 * Date: Feb 27, 2021
 * version 1.0
 */

// This reverses the line order of a file using system calls

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	// Variable defintions
	int in, out, end, start, fileSize = 0;
	// For reading character by character
	char buffer;
	// For reading the whole line - assume a max of 1000 characters
	char line[1000];

	// Check correct usage
	if(argc != 3){
		printf("Usage: %s <source-file> <destination-file>\n", argv[0]);
		exit(1);
	}
	if((in = open(argv[1], O_RDONLY)) == -1){
		perror("File could not be opened");
		exit(1);
	}
	if((out = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1){
		perror("File could not be opened");
		exit(1);
	}

	// Get file size
	while((read(in, &buffer, 1)) > 0){
		fileSize++;
	}
	end = fileSize;

	// Print output
	for(int i = fileSize; i >= 0; i--){
		lseek(in, i-1, SEEK_SET);
		read(in, &buffer, 1);
		if(buffer == '\n'){
			start = i;
			// Subtract last known position of newline with recently found newline to get line n
			read(in, line, end - start);
			write(out, line, end - start);
			end = start;
		}
	}

	// Output the last line
	lseek(in, 0, SEEK_SET);
	read(in, line, end);
	write(out, line, end);

	// Success
	puts("Reverse line ordering successful");

	close(in);
	close(out);
	exit(0);
}
