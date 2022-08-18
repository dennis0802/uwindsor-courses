/*
 * Developer: Dennis Dao
 * June 7, 2022
 * v1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// Program to send a message to reverse character case to a child and return it to parent
int main(int argc, char* argv[]){
	// Variables
	int pid;
	int fd1[2], fd2[2]; // fd1: parent writes, child reads; fd2: parent reads, child writes

	pipe(fd1);
	pipe(fd2);

	if((pid = fork()) == -1){
		perror("fork");
		exit(-1);
	}

	// Child - read from fd1, write to fd2
	else if(pid == 0){
		char contents[100];
		close(fd1[1]);
		close(fd2[0]);

		// Read from the parent
		read(fd1[0], contents, 100);

		// Convert each character to opposite case
		// Difference between lower to upper is 32 from ASCII
		for(int i = 0; i < strlen(contents); i++){
			// Upper to lower
			if(contents[i] >= 65 && contents[i] <= 90){
				contents[i] += 32;
			}
			// Lower to upper
			else if(contents[i] >= 97 && contents[i] <= 122){
				contents[i] -= 32;
			}
		}

		// Write to the parent
		if(write(fd2[1], contents, strlen(contents)) != strlen(contents)){
			perror("Writing problem\n");
			exit(-1);
		}
		exit(0);
	}

	// Parent - write to fd1, read to fd2
	else{
		char buffer[100];
		close(fd1[0]);
		close(fd2[1]);

		// Assume user will input a string for the parent
        	printf("Enter a string for the parent process to send: ");
        	scanf("%[^\n]s", buffer);
        	printf("%s being written to the child process...\n\n", buffer);

		// Write message to the child
		if(write(fd1[1], buffer, strlen(buffer)) != strlen(buffer)){
			perror("Writing problem\n");
			exit(-1);
		}

		// Read message from child
		read(fd2[0], buffer, strlen(buffer));
		printf("%s received from the child.\n", buffer);
		puts("Terminating program...");

		exit(0);
	}
}
