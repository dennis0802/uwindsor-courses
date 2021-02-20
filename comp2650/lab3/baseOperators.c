//============================================================================
// Name        : baseOperators.c
// Author      : Dennis Dao
// Version     : 1.0
// Description : Program that runs the AND, NOT, OR, 1's complement, and
//				 2's complement operations with binary numbers from a user menu.
//				 The user also has the option of deciding what base to have the
//				 output as.
//============================================================================

#include <stdio.h>
#include "logic_tools.h"
#include "comp_tools.h"
#include "convert_tools.h"
#define MAX 8 // Byte = 8 bits

int main(void){
	setbuf(stdout, NULL);

	// Variable definitions
	int exit = 0;
	int conversionInput = 0;
	int input;
	int number = 0;
	int x[MAX];
	int y[MAX];
	int z[MAX];

	// Loop until the user wants to exit.
	while(exit == 0){
		// Let user input a command number.
		puts("Enter the command number:");
		puts("0) EXIT");
		puts("1) AND");
		puts("2) OR");
		puts("3) NOT");
		puts("4) 1's complement");
		puts("5) 2's complement");
		puts("6) 2's complement*");
		fflush(stdout);
		scanf("%d", &input);

		// User exited program
		if(input == 0){
			exit = 1;
			printf("You have exited the program.\n\n");
		}

		// Perform the AND operator
		else if(input == 1){
			// Allow user to enter binary numbers.
			puts("Enter the first binary number:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("x%d = ", i);
				scanf("%d", &x[i]);
				if(x[i] < 0 || x[i] > 1){
					puts("Invalid entry. Please re-enter the first binary number.");
					i = -1;
				}
			}
			puts("Enter the second binary number:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("y%d = ", i);
				scanf("%d", &y[i]);
				if(y[i] < 0 || y[i] > 1){
					puts("Invalid entry. Please re-enter the second binary number.");
					i = -1;
				}
			}
			printf("\n");
			// Perform the AND operation
			func_and(x, y, z);
			// Ask the user for base of the output
			while(conversionInput == 0){
				puts("Enter the output base:");
				puts("1) Binary");
				puts("2) Octal");
				puts("3) Decimal");
				puts("4) Hexadecimal");
				scanf("%d", &conversionInput);

				// Convert to binary
				if(conversionInput == 1){
					puts("The first binary AND the second binary in binary yield:");
					for(int i = 0; i < MAX; i = i + 1){
						printf("%d", z[i]);
					}
				}

				// Convert to octal
				else if(conversionInput == 2){
					puts("The first binary AND the second binary in octal yield:");
					to_octal(z);
				}

				// Convert to decimal
				else if(conversionInput == 3){
					puts("The first binary AND the second binary in decimal yield:");
					to_decimal(z);
					// Sum up the powers of 2.
					for(int i = 0; i < MAX; i = i + 1){
						number = number + z[i];
					}
					printf("%d", number);
				}

				// Convert to hexadecimal
				else if(conversionInput == 4){
					puts("The first binary AND the second binary in hexadecimal yield:");
					to_hexadecimal(z);
				}

				// Invalid input entered.
				else{
					puts("Invalid input. Please enter a valid input.");
					printf("\n");
					conversionInput = 0;
				}
			}
			conversionInput = 0;
			printf("\n\n");
		}

		// Perform the OR operator
		else if(input == 2){
			// Allow user to enter binary numbers.
			puts("Enter the first binary number:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("x%d = ", i);
				scanf("%d", &x[i]);
				if(x[i] < 0 || x[i] > 1){
					puts("Invalid entry. Please re-enter the first binary number.");
					i = -1;
				}
			}
			puts("Enter the second binary number:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("y%d = ", i);
				scanf("%d", &y[i]);
				if(y[i] < 0 || y[i] > 1){
					puts("Invalid entry. Please re-enter the second binary number.");
					i = -1;
				}
			}
			// Perform the OR operation
			func_or(x, y, z);
			// Ask the user for base of the output
			while(conversionInput == 0){
				puts("Enter the output base:");
				puts("1) Binary");
				puts("2) Octal");
				puts("3) Decimal");
				puts("4) Hexadecimal");
				scanf("%d", &conversionInput);

				// Convert to binary
				if(conversionInput == 1){
					puts("The first binary OR the second binary in binary yield:");
					for(int i = 0; i < MAX; i = i + 1){
						printf("%d", z[i]);
					}
				}

				// Convert to octal
				else if(conversionInput == 2){
					puts("The first binary OR the second binary in octal yield:");
					to_octal(z);
				}

				// Convert to decimal
				else if(conversionInput == 3){
					puts("The first binary OR the second binary in decimal yield:");
					to_decimal(z);
					// Sum up the powers of 2.
					for(int i = 0; i < MAX; i = i + 1){
						number = number + z[i];
					}
					printf("%d", number);
				}

				// Convert to hexadecimal
				else if(conversionInput == 4){
					puts("The first binary OR the second binary in hexadecimal yield:");
					to_hexadecimal(z);
				}

				// Invalid input entered.
				else{
					puts("Invalid input. Please enter a valid input.");
					printf("\n");
					conversionInput = 0;
				}
			}
			conversionInput = 0;
			printf("\n\n");
		}

		// Perform the NOT operator
		else if(input == 3){
			// Allow user to enter binary number.
			puts("Enter the first binary number:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("x%d = ", i);
				scanf("%d", &x[i]);
				if(x[i] < 0 || x[i] > 1){
					puts("Invalid entry. Please re-enter the first binary number.");
					i = -1;
				}
			}
			// Perform the NOT operation
			func_not(x, z);
			// Ask the user for base of the output
			while(conversionInput == 0){
				puts("Enter the output base:");
				puts("1) Binary");
				puts("2) Octal");
				puts("3) Decimal");
				puts("4) Hexadecimal");
				scanf("%d", &conversionInput);

				// Convert to binary
				if(conversionInput == 1){
					puts("NOT the first binary in binary yield:");
					for(int i = 0; i < MAX; i = i + 1){
						printf("%d", z[i]);
					}
				}

				// Convert to octal
				else if(conversionInput == 2){
					puts("NOT the first binary in octal yield:");
					to_octal(z);
				}

				// Convert to decimal
				else if(conversionInput == 3){
					puts("NOT the first binary in decimal yield:");
					to_decimal(z);
					// Sum up the powers of 2.
					for(int i = 0; i < MAX; i = i + 1){
						number = number + z[i];
					}
					printf("%d", number);
				}

				// Convert to hexadecimal
				else if(conversionInput == 4){
					puts("NOT the first binary in hexadecimal yield:");
					to_hexadecimal(z);
				}

				// Invalid input entered.
				else{
					puts("Invalid input. Please enter a valid input.");
					printf("\n");
					conversionInput = 0;
				}
			}
			conversionInput = 0;
			printf("\n\n");
		}

		// Perform 1's complement
		else if(input == 4){
			// Allow user to enter binary number.
			puts("Enter the first binary number:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("x%d = ", i);
				scanf("%d", &x[i]);
				if(x[i] < 0 || x[i] > 1){
					puts("Invalid entry. Please re-enter the first binary number.");
					i = -1;
				}
			}
			// Perform the 1's complement.
			func_1s_comp(x, z);
			// Ask the user for base of the output
			while(conversionInput == 0){
				puts("Enter the output base:");
				puts("1) Binary");
				puts("2) Octal");
				puts("3) Decimal");
				puts("4) Hexadecimal");
				scanf("%d", &conversionInput);

				// Convert to binary
				if(conversionInput == 1){
					puts("The 1's complement of the number in binary yield:");
					for(int i = 0; i < MAX; i = i + 1){
						printf("%d", z[i]);
					}
				}

				// Convert to octal
				else if(conversionInput == 2){
					puts("The 1's complement of the number in octal yield:");
					to_octal(z);
				}

				// Convert to decimal
				else if(conversionInput == 3){
					puts("The 1's complement of the number in decimal yield:");
					to_decimal(z);
					// Sum up the powers of 2.
					for(int i = 0; i < MAX; i = i + 1){
						number = number + z[i];
					}
					printf("%d", number);
				}

				// Convert to hexadecimal
				else if(conversionInput == 4){
					puts("The 1's complement of the number in hexadecimal yield:");
					to_hexadecimal(z);
				}

				// Invalid input entered.
				else{
					puts("Invalid input. Please enter a valid input.");
					printf("\n");
					conversionInput = 0;
				}
			}
			conversionInput = 0;
			printf("\n\n");
		}

		// Perform 2's complement
		else if(input == 5){
			// Allow user to enter binary number.
			puts("Enter the first binary number:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("x%d = ", i);
				scanf("%d", &x[i]);
				if(x[i] < 0 || x[i] > 1){
					puts("Invalid entry. Please re-enter the first binary number.");
					i = -1;
				}
			}
			// Perform the 2's complement.
			func_2s_comp(x, z);
			// Ask the user for base of the output
			while(conversionInput == 0){
				puts("Enter the output base:");
				puts("1) Binary");
				puts("2) Octal");
				puts("3) Decimal");
				puts("4) Hexadecimal");
				scanf("%d", &conversionInput);

				// Convert to binary
				if(conversionInput == 1){
					puts("The 2's complement of the number in binary yield:");
					for(int i = 0; i < MAX; i = i + 1){
						printf("%d", z[i]);
					}
				}

				// Convert to octal
				else if(conversionInput == 2){
					puts("The 2's complement of the number in octal yield:");
					to_octal(z);
				}

				// Convert to decimal
				else if(conversionInput == 3){
					puts("The 2's complement of the number in decimal yield:");
					to_decimal(z);
					// Sum up the powers of 2.
					for(int i = 0; i < MAX; i = i + 1){
						number = number + z[i];
					}
					printf("%d", number);
				}

				// Convert to hexadecimal
				else if(conversionInput == 4){
					puts("The 2's complement of the number in hexadecimal yield:");
					to_hexadecimal(z);
				}

				// Invalid input entered.
				else{
					puts("Invalid input. Please enter a valid input.");
					printf("\n");
					conversionInput = 0;
				}
			}
			conversionInput = 0;
			printf("\n\n");
		}

		// Perform the 2's complement*/alternate method.
		else if(input == 6){
			// Allow user to enter binary number.
			puts("Enter the first binary number:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("x%d = ", i);
				scanf("%d", &x[i]);
				if(x[i] < 0 || x[i] > 1){
					puts("Invalid entry. Please re-enter the first binary number.");
					i = -1;
				}
			}
			// Perform the 2's complement
			func_2s_comp_star(x, z);
			// Ask the user for base of the output
			while(conversionInput == 0){
				puts("Enter the output base:");
				puts("1) Binary");
				puts("2) Octal");
				puts("3) Decimal");
				puts("4) Hexadecimal");
				scanf("%d", &conversionInput);

				// Convert to binary
				if(conversionInput == 1){
					puts("The 2's complement of the number in binary yield:");
					for(int i = 0; i < MAX; i = i + 1){
						printf("%d", z[i]);
					}
				}

				// Convert to octal
				else if(conversionInput == 2){
					puts("The 2's complement of the number in octal yield:");
					to_octal(z);
				}

				// Convert to decimal
				else if(conversionInput == 3){
					puts("The 2's complement of the number in decimal yield:");
					to_decimal(z);
					// Sum up the powers of 2.
					for(int i = 0; i < MAX; i = i + 1){
						number = number + z[i];
					}
					printf("%d", number);
				}

				// Convert to hexadecimal
				else if(conversionInput == 4){
					puts("The 2's complement of the number in hexadecimal yield:");
					to_hexadecimal(z);
				}

				// Invalid input entered.
				else{
					puts("Invalid input. Please enter a valid input.");
					printf("\n");
					conversionInput = 0;
				}
			}
			conversionInput = 0;
			printf("\n\n");
		}

		else{
			puts("Invalid input. Please input a valid response.");
		}
		// Reset the decimal number for the next loop.
		number = 0;
	}
	return 0;
}
