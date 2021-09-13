/**
 * Developer: Dennis Dao
 * Date: Mar 12, 2021
 * version 1.0
 */

// This program makes the child read and write to the screen, then the parent
// reports the status of the child 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char* argv[]){
	// Variable definitions
	int in, pid, content;
	char buffer[400];

	// Usage
	if(argc != 2){
		printf("Usage: %s <source-file>\n", argv[0]);
		exit(1);
	}

	if((in = open(argv[1], O_RDONLY)) == -1){
		printf("%s does not exist\n", argv[1]);
		exit(1);
	}

	// Make child process
	pid = fork();
	// Could not be made
	if(pid == -1){
		printf("The process could not be forked. Error.\n");
		exit(1);
	}
	// Child - reads and writes the content to the screen (standard output)
	if(pid == 0){
		printf("Contents of %s:\n\n", argv[1]);
		while((content = read(in, buffer, 400)) > 0){
			if(write(STDOUT_FILENO, buffer, content) != content){
				perror("Writing problem.");
				exit(3);
			}
		}

		// Error while reading
		if(content == -1){
			perror("Reading problem");
			exit(2);
		}

		// Begin termination process
		close(in);
		sleep(5);
		printf("\nReading and writing complete.\n");
		printf("Child terminating.\n\n");
		sleep(5);
		exit(20);
	}
	// Parent - waits for the child, then prints status from child
	else if(pid > 0){
		int status;
		int pid = wait(&status);
		int childStatus = status >> 8;
		puts("My child has terminated.");
		printf("My child %d has terminated and I have received the status %d\n", pid, status);
		printf("Child status = %d\n", childStatus);
		exit(0);
	}
}
