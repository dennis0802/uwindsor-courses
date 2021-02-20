//============================================================================
// Name        : logicComplementOperators.c
// Author      : Dennis Dao
// Version     : 1.0
// Description : Program that runs the AND, NOT, OR, 1's complement, and
//				 2's complement operations with binary numbers from a user menu
//============================================================================

#include <stdio.h>
#define MAX 8 //Byte = 8 bits

// Function prototypes
void func_and(int a[], int b[], int result[]);
void func_or(int a[], int b[], int result[]);
void func_not(int a[], int result[]);
void func_1s_comp(int a[], int result[]);
void func_2s_comp(int a[], int result[]);
void func_2s_comp_star(int a[], int result[]);


int main(void){
	setbuf(stdout, NULL);

	// Variable definitions
	int exit = 0;
	int input;
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
			// Perform the AND operation
			func_and(x, y, z);
			puts("The first number AND the second binary yield:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("%d", z[i]);
			}
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
			puts("The first number OR the second binary yield:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("%d", z[i]);
			}
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
			puts("NOT the first binary number yields:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("%d", z[i]);
			}
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
			puts("The 1's complement of the binary number yields:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("%d", z[i]);
			}
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
			puts("The 2's complement of the binary number yields:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("%d", z[i]);
			}
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
			puts("The 2's complement of the binary number yields:");
			for(int i = 0; i < MAX; i = i + 1){
				printf("%d", z[i]);
			}

			printf("\n\n");
		}

		else{
			puts("Invalid input. Please input a valid response.");
		}

	}
	return 0;
}

// Function definitions
// Performing the AND operator
void func_and(int a[], int b[], int result[]){
	for(int i=0; i< MAX; i = i+1){
		result[i] = a[i] & b[i];
	}
}

// Performing the OR operator
void func_or(int a[], int b[], int result[]){
	for(int i=0; i< MAX; i = i+1){
		result[i] = a[i] | b[i];
	}
}

// Performing the NOT operator
void func_not(int a[], int result[]){
	for(int i=0; i< MAX; i = i+1){
		result[i] = !a[i];
	}
}

// Performing the 1's complement
void func_1s_comp(int a[], int result[]){
	func_not(a, result);
}

// Performing the 2's complement
void func_2s_comp(int a[], int result[]){
	// Variables to help with adding 1.
	int carry = 0;

	// NOT the numbers, then add 1.
	func_1s_comp(a, result);
	for(int i = MAX - 1; i >= 0; i = i - 1){
		// Initial digit to add (right side)
		if(i == MAX - 1){
			// If adding one to the ones column results in a 2, set the result to 0 and apply a carrying digit
			// Otherwise, add as normal.
			if(result[i] + 1 == 2){
				carry = 1;
				result[i] = 0;
			}
			else{
				result[i] = 1;
			}
		}
		// Any additional digits.
		else if(carry == 1){
			// If adding the carrying digit to the column results in a 2, set the result to 0 and apply a carrying digit.
			// Otherwise, add as normal.
			if(result[i] + carry == 2){
				carry = 1;
				result[i] = 0;
			}
			else{
				result[i] = result[i] + 1;
				carry = 0;
			}
		}
	}
}

// Performing the 2's complement alternate method
void func_2s_comp_star(int a[],int result[]){
	// Variables to help flag when a 1 is found.
	int found = 0;
	int position;

	// Go through the array backwards until the first occurrence of a 1 is found.
	for(int i = MAX - 1; i >= 0; i = i - 1){
		result[i] = a[i];
		if(a[i] == 1){
			position = i;
			found = 1;
			break;
		}
	}

	// NOT the remaining positions after finding the first occurrence of a 1.
	// NOT function not used due to requiring to go through the array backwards.
	if(found == 1){
		for(int i = position - 1; i >= 0; i = i - 1){
			result[i] = !a[i];
		}
	}

}

