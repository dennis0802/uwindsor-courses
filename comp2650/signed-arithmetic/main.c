//============================================================================
// Name        : COMP2650_Lab04_dao114.cpp
// Author      : Dennis Dao
// Version     : 1.0
// Lab Section : 55
// Description : Program that runs signed magnitude addition and signed magnitude
//				 subtraction of two binary numbers inputed by the user. The user
//				 can also decide the base to output the result in.
//============================================================================

#include <stdio.h>
#include "convert_tools.h" // Conversion tools for switching bases
#include "arithmetic_tools.h" // Arithmetic tools for performing signed magnitude arithmetic
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
		puts("1) Addition in signed-magnitude");
		puts("2) Subtraction in signed-magnitude");
		fflush(stdout);
		scanf("%d", &input);

		// User exited program
		if(input == 0){
			exit = 1;
			printf("You have exited the program.\n\n");
		}

		// Perform signed-magnitude addition
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

			// Perform the signed-magnitude addition
			func_signed_mag_addition(x, y, z);

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
					puts("The first binary added with the second binary in binary yield:");
					for(int i = 0; i < MAX; i = i + 1){
						printf("%d", z[i]);
					}
					printf("\n");
				}

				// Convert to octal
				else if(conversionInput == 2){
					puts("The first binary added with the second binary in octal yield:");
					to_octal(z);
					printf("\n");
				}

				// Convert to decimal
				else if(conversionInput == 3){
					puts("The first binary added with the second binary in decimal yield:");
					to_decimal(z);
					// Sum up the powers of 2.
					for(int i = 1; i < MAX; i = i + 1){
						number = number + z[i];
					}
					// Check the signed bit.
					if(z[0] == 1){
						number = number * -1;
					}
					printf("%d", number);
					printf("\n");
				}

				// Convert to hexadecimal
				else if(conversionInput == 4){
					puts("The first binary added with the second binary in hexadecimal yield:");
					to_hexadecimal(z);
					printf("\n");
				}

				// Invalid input entered.
				else{
					puts("Invalid input. Please enter a valid input.");
					printf("\n");
					conversionInput = 0;
				}
			}
			conversionInput = 0;
			printf("\n");
		}

		// Perform signed-magnitude subtraction
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

			// Perform the signed-magnitude subtraction
			func_signed_mag_subtraction(x, y, z);
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
					puts("The first binary subtracted with the second binary in binary yield:");
					for(int i = 0; i < MAX; i = i + 1){
						printf("%d", z[i]);
					}
					printf("\n");
				}

				// Convert to octal
				else if(conversionInput == 2){
					puts("The first binary subtracted with the second binary in octal yield:");
					to_octal(z);
					printf("\n");
				}

				// Convert to decimal
				else if(conversionInput == 3){
					puts("The first binary subtracted with the second binary in decimal yield:");
					to_decimal(z);
					// Sum up the powers of 2.
					for(int i = 1; i < MAX; i = i + 1){
						number = number + z[i];
					}
					// Check the signed bit.
					if(z[0] == 1){
						number = number * -1;
					}
					printf("%d", number);
					printf("\n");
				}

				// Convert to hexadecimal
				else if(conversionInput == 4){
					puts("The first binary subtracted with the second binary in hexadecimal yield:");
					to_hexadecimal(z);
					printf("\n");
				}

				// Invalid input entered.
				else{
					puts("Invalid input. Please enter a valid input.");
					printf("\n");
					conversionInput = 0;
				}
			}
			conversionInput = 0;
			printf("\n");
		}

		else{
			puts("Invalid input. Please input a valid response.");
		}
		// Reset the decimal number for the next loop.
		number = 0;
	}
	return 0;
}
