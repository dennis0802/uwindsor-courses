//============================================================================
// Name        : logicOperators.c
// Author      : Dennis Dao
// Version     : 1.0
// Description : Program that runs the AND operator, the OR operator, and the
//				 NOT operator from a user menu.
//============================================================================

#include <stdio.h>

int main(void) {
	// Variable definitions.
	int input;
	int exit = 0;
	int x;
	int y;

	// Run until the user wants to exit.
	while(exit != 1){
		puts("Enter the command number:");
		puts("1) AND");
		puts("2) OR");
		puts("3) NOT");
		puts("4) EXIT");
		fflush(stdout);
		scanf("%d", &input);

		// AND operator selected.
		if(input == 1){
			// Ask the user for boolean values.
			puts("Enter a boolean value (0 or 1).");
			fflush(stdout);
			scanf("%d", &x);

			puts("Enter another boolean value (0 or 1).");
			fflush(stdout);
			scanf("%d", &y);

			// Check validity of inputs.
			if((x == 0 || x == 1) && (y == 0 || y == 1)){
				printf("%d AND %d is %d\n\n", x,y, x&y);
			}
			else{
				puts("Invalid response.\n\n");
			}
		}

		// OR operator selected.
		else if(input == 2){
			// Ask the user for boolean values.
			puts("Enter a boolean value (0 or 1).");
			fflush(stdout);
			scanf("%d", &x);

			puts("Enter another boolean value (0 or 1).");
			fflush(stdout);
			scanf("%d", &y);

			// Check validity of inputs.
			if((x == 0 || x == 1) && (y == 0 || y == 1)){
				printf("%d OR %d is %d\n\n", x,y, x|y);
			}
			else{
				puts("Invalid response.\n\n");
			}
		}

		// NOT operator selected.
		else if(input == 3){
			// Ask the user for a boolean value.
			puts("Enter a boolean value (0 or 1).");
			fflush(stdout);
			scanf("%d", &x);

			// Check validity of inputs.
			if(x == 0 || x == 1){
				printf("NOT %d is %d\n\n", x, !x);
			}
			else{
				puts("Invalid response.\n\n");
			}
		}

		// User picked to exit program.
		else if(input == 4){
			exit = 1;
			printf("You have exited the program.\n\n");
		}

		// Invalid input was entered.
		else{
			printf("Invalid response.\n\n");
		}
	}
	return 0;
}
