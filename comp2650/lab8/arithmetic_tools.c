//============================================================================
// Name        : arithmetic_tools.cpp
// Author      : Dennis Dao
// Version     : 1.0
// Lab Section : 55
// Description : Separate file for arithmetic functions
//============================================================================

#define INPUT_VARIABLE_COUNT 3
#define OUTPUT_VARIABLE_COUNT 1
#include <stdio.h>

// Performing signed-2's complement addition to increment the truth table
void func_increment(int a[], int result[]){
	// Helper variable to store the carrying digit.
	int carry;

	// Add from right to left
	for(int i = INPUT_VARIABLE_COUNT - 1; i >= 0; i = i-1){
		// First digit
		if(i == INPUT_VARIABLE_COUNT - 1){
			// If adding one to the ones column results in a 2, set the result to 0 and apply a carrying digit
			// Otherwise, add as normal.
			if(a[i] + 1 == 2){
				carry = 1;
				a[i] = 0;
			}
			else{
				a[i] = 1;
			}
		}

		// Remaining digits
		else if(carry == 1){
			// If adding the carrying digit to the column results in a 2, set the result to 0 and apply a carrying digit.
			// Otherwise, add as normal.
			if(a[i] + carry == 2){
				carry = 1;
				a[i] = 0;
			}
			else{
				carry = 0;
				a[i] = a[i] + 1;
			}
		}
	}

	// Copy the values to the result array.
	for(int j = 0; j < INPUT_VARIABLE_COUNT; j++){
		result[j] = a[j];
	}
}

