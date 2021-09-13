/**
 * Developer: Dennis Dao
 * Date: Mar 17, 2021
 * version 1.0
 */

// This makes a game of dice using 4 child processes

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
int getRandomInteger(int n);
void action1();
void action2();
void child(char *);

int main(int argc, char *argv[]){
	pid_t pid1, pid2, pid3, pid4;

	printf("This is a 4-players game with a referee\n");
	if((pid1=fork()) == 0) child("TOTO");
	if((pid2=fork()) == 0) child("TITI");
	if((pid3=fork()) == 0) child("LOLO");
	if((pid4=fork()) == 0) child("LALA");

  	sleep(1);
  	signal(SIGUSR1, action1);
  	while(1){
    		printf("TOTO plays\n\n");
    		kill(pid1, SIGUSR1);
    		pause();
    		printf("TITI plays\n\n");
    		kill(pid2, SIGUSR1);
    		pause();
		printf("LOLO plays\n\n");
		kill(pid3, SIGUSR1);
		pause();
		printf("LALA plays\n\n");
		kill(pid4, SIGUSR1);
		pause();
  	}
}

// Function defintions
int getRandomInteger(int n){
	srand(time(NULL));
	return rand() % n;
}

void action1(){
	printf("\nReferee:");
}

void action2(){}

void child(char *s){
	int points=0;
	int dice, n=21;

	while(1){
		signal(SIGUSR1, action2);  // block myself
		pause();
		printf("%s: playing my dice\n", s);
		dice = getRandomInteger(n);
 		printf("%s: got %d points\n", s, dice);
    		points+=dice;
    		printf("%s: Total so far %d\n\n", s, points);
    		sleep(3);
    		if(points >= 100){
      			printf("%s: game over I won\n", s);
      			kill(0, SIGTERM);
    		}
    		kill(getppid(), SIGUSR1);
	}
}
