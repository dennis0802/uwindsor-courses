//============================================================================
// Name        : truth_table.c
// Author      : Dennis Dao
// Version     : 1.0
// Description : Program that allows the user to make a truth table and set
//               the output values of the boolean function F. The user can
//				 output the minterms and the maxterms of the function.
//============================================================================

#include <stdio.h>
#include <math.h>
#include "arithmetic_tools.h" // Arithmetic tools for performing signed-2's complement arithmetic

#define INPUT_VARIABLE_COUNT 3
#define OUTPUT_VARIABLE_COUNT 1

// Function prototypes
void build_left_side(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]);
void build_right_side(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]);
void to_minterm(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]);
void to_MAXTERM(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]);

int main(void){
	setbuf(stdout, NULL);

	// Variable definitions
	int TRUTH_TABLE_ROW_COUNT = (int)pow(2, INPUT_VARIABLE_COUNT);
	int truth_table[TRUTH_TABLE_ROW_COUNT][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT] = {0};
	int exit = 1;
	int input;
	const char variables [INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT] = {'Z', 'Y', 'X', 'F'};

	// Build the truth table
	build_left_side(truth_table);
	build_right_side(truth_table);

	// Print the truth table input header
	for(int i = 0; i < INPUT_VARIABLE_COUNT; i++){
		printf("%c, ", variables[i]);
	}
	printf(" : ");

	// Print the truth table output header
	for(int i = INPUT_VARIABLE_COUNT; i < INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT; i++){
		printf("%c, ", variables[i]);
	}
	printf("\n");

	// Print the content of each row
	for(int i = 0; i < TRUTH_TABLE_ROW_COUNT; i++){
		// Rows containing input variables
		for(int j = 0; j < INPUT_VARIABLE_COUNT; j++){
			printf("%d, ", truth_table[i][j]);
		}
		printf(" : ");

		// Rows containing the output variable
		for(int j = INPUT_VARIABLE_COUNT; j < INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT; j++){
			printf("%d, ", truth_table[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// Menu for user to see canonical SoP or exit.
	while(exit == 1){
		puts("Enter the command number: ");
		puts("0) Exit");
		puts("1) Canonical SoP (Sum of Products)");
		puts("2) Canonical Pos (Product of Sums)");
		scanf("%d", &input);

		if(input == 0){
			exit = 0;
			puts("You have exited the program.");
			printf("\n");
		}
		else if(input == 1){
			to_minterm(truth_table);
			printf("\n\n");
		}
		else if(input == 2){
			to_MAXTERM(truth_table);
			printf("\n\n");
		}
		else{
			puts("Invalid input. Please enter a valid number.");
			printf("\n");
		}
	}

	return 0;
}

// Function definitions
// Building the left side of the truth table
void build_left_side(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]){
	int TRUTH_TABLE_ROW_COUNT = (int)pow(2, INPUT_VARIABLE_COUNT);

	for(int i = 0; i < TRUTH_TABLE_ROW_COUNT - 1; i++){

		int row[INPUT_VARIABLE_COUNT] = {0};
		int result[INPUT_VARIABLE_COUNT] = {0};

		// Access the elements of row i to be used.
		for(int k = 0; k < INPUT_VARIABLE_COUNT; k++){
			row[k] = truth_table[i][k];
		}

		// Increment
		func_increment(row, result);

		// Put the results into the next row (i+1)
		for(int j = 0; j < INPUT_VARIABLE_COUNT; j++){
			truth_table[i+1][j] = result[j];
		}
	}
}

// Building the right side of the truth table
void build_right_side(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]){
	int input;
	int TRUTH_TABLE_ROW_COUNT = (int)pow(2, INPUT_VARIABLE_COUNT);

	for(int i = 0; i < TRUTH_TABLE_ROW_COUNT; i++){

		// For each output variable F
		for(int j = 0; j < OUTPUT_VARIABLE_COUNT; j++){
			printf("Output value for row #%d of F output variable: ", i);
			scanf("%d", &input);
			// Check validity of input and set to output column
			if(input == 0 || input == 1){
				truth_table[i][INPUT_VARIABLE_COUNT] = input;
			}
			else{
				puts("Invalid input. Please enter a 0 or 1.");
				j--;
			}
		}
	}
	printf("\n");
}

// Printing the minterm output variable of the boolean function
void to_minterm(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]){
	int TRUTH_TABLE_ROW_COUNT = (int)pow(2, INPUT_VARIABLE_COUNT);

	// For every output variable...
	for(int j = 0; j < OUTPUT_VARIABLE_COUNT; j++){
		printf("Output variable F%d = 'sigma' m(", j+1);
		for(int m = 0; m < TRUTH_TABLE_ROW_COUNT; m++){
			if(truth_table[m][INPUT_VARIABLE_COUNT] == 1){
				printf("%d,", m);
			}
		}
		printf(") = ");
		// For each row...
		for(int i = 0; i < TRUTH_TABLE_ROW_COUNT; i++){
			for(int k = 0; k < OUTPUT_VARIABLE_COUNT; k++){
				// Check the contents of each row that has a 1 for output
				// Print a NOT variable if it is 0, normal otherwise)
				// Form the sum of minterms.
				if(truth_table[i][INPUT_VARIABLE_COUNT] == 1){
					if(truth_table[i][0] == 0){
						printf("Z\'");
					}
					else{
						printf("Z");
					}
					if(truth_table[i][1] == 0){
						printf("Y\'");
					}
					else{
						printf("Y");
					}
					if(truth_table[i][2] == 0){
						printf("X\'");
					}
					else{
						printf("X");
					}
					printf("+");
				}
			}
		}
	}
}

// Printing the maxterm output variable of the boolean function
void to_MAXTERM(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]){
	int TRUTH_TABLE_ROW_COUNT = (int)pow(2, INPUT_VARIABLE_COUNT);

	// For every output variable...
	for(int j = 0; j < OUTPUT_VARIABLE_COUNT; j++){
		printf("Output variable F%d = 'PI' M(", j+1);
		for(int m = 0; m < TRUTH_TABLE_ROW_COUNT; m++){
			if(truth_table[m][INPUT_VARIABLE_COUNT] == 0){
				printf("%d,", m);
			}
		}
		printf(") = ");
		// For each row...
		for(int i = 0; i < TRUTH_TABLE_ROW_COUNT; i++){
			for(int k = 0; k < OUTPUT_VARIABLE_COUNT; k++){
				// Check the contents of each row that has a 0 for output
				// Print a NOT variable if it is 1, normal otherwise)
				// Form the product of sums
				if(truth_table[i][INPUT_VARIABLE_COUNT] == 0){
					if(truth_table[i][0] == 1){
						printf("(Z\'+");
					}
					else{
						printf("(Z+");
					}
					if(truth_table[i][1] == 1){
						printf("Y\'+");
					}
					else{
						printf("Y+");
					}
					if(truth_table[i][2] == 1){
						printf("X\')");
					}
					else{
						printf("X)");
					}
				}
			}
		}
	}
}
