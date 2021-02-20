//============================================================================
// Name        : truth_table.c
// Author      : Dennis Dao
// Version     : 1.0
// Description : Program that allows the user to make a truth table and set
//               the output values of the boolean function F.
//============================================================================

#include <stdio.h>
#include <math.h>
#include "arithmetic_tools.h" // Arithmetic tools for performing signed-2's complement arithmetic

#define INPUT_VARIABLE_COUNT 3
#define OUTPUT_VARIABLE_COUNT 1

// Function prototypes
void build_left_side(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]);
void build_right_side(int truth_table[][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT]);

int main(void){
	setbuf(stdout, NULL);

	// Variable definitions
	int TRUTH_TABLE_ROW_COUNT = (int)pow(2, INPUT_VARIABLE_COUNT);
	int truth_table[TRUTH_TABLE_ROW_COUNT][INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT] = {0};
	const char variables [INPUT_VARIABLE_COUNT + OUTPUT_VARIABLE_COUNT] = {'Z', 'Y', 'X', 'F'};
	// Variable to help pause the executable/release version of the program and see the truth table
	int pause;

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
	puts("Enter any key to continue");
	scanf("%d", &pause);
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
