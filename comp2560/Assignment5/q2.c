/**
 * Developer: Dennis Dao
 * Date: Mar 12, 2021
 * version 1.0
 */

// This program makes the child read and write to the out file, then the parent
// reports the child's status also to the out file.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
	// Variable definitions
	int in, out, pid, content;
	char buffer[400];

	// Usage
	if(argc != 3){
		printf("Usage: %s <source-file> <destination-file>\n", argv[0]);
		exit(1);
	}

	if((in = open(argv[1], O_RDONLY)) == -1){
		printf("%s does not exist\n", argv[1]);
		exit(1);
	}

	if((out = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1){
		printf("%s could not be opened.\n", argv[2]);
		exit(1);
	}

	// Make child process
	pid = fork();
	// Could not be made
	if(pid == -1){
		printf("The process could not be forked. Error.\n");
		exit(1);
	}
	// Child - reads and writes the content to the out file
	if(pid == 0){
		printf("Contents of %s being written to %s...\n", argv[1], argv[2]);
		while((content = read(in, buffer, 400)) > 0){
			if(write(out, buffer, content) != content){
				perror("Writing problem.");
				exit(3);
			}
		}

		if(content == -1){
			perror("Reading problem");
			exit(2);
		}

		// Begin termination process
		close(in);
		sleep(5);
		sprintf(buffer, "\nChild terminating.\n\n");
		write(out, buffer, strlen(buffer));
		sleep(5);
		exit(20);
	}
	// Parent - waits for the child, then prints status from child to the file
	else if(pid > 0){
		int status;
		int pid = wait(&status);
		int childStatus = status >> 8;
		sprintf(buffer, "My child has terminated.\n");
		write(out, buffer, strlen(buffer));
		sprintf(buffer, "My child %d has terminated and I have received the status %d\n", pid, status);
		write(out, buffer, strlen(buffer));
		sprintf(buffer, "Child status = %d\n", childStatus);
		write(out, buffer, strlen(buffer));
		close(out);
		puts("Program execution complete.");
	}
}
