//============================================================================
// Name        : arithmetic_tools.cpp
// Author      : Dennis Dao
// Version     : 1.0
// Lab Section : 55
// Description : Separate file for arithmetic functions
//============================================================================

#define MAX 8 // Byte = 8 bits
#include <stdio.h>
#include "arithmetic_tools.h" // The functions may have to call each other, depending on arithmetic form.
#include "comp_tools.h" // Required to take the 2's complement

/*
 * NOTE 1: For these functions, assume a is the top number and b is the bottom number in the arithmetic.
 * 			100 (a)
 * 		   +101 (b)
 * 			result
 */

/*
 * NOTE 2: Signed-2's complement numbers are similar to signed-magnitude numbers!
 * 		 x <= 0111...111 = positive, x > 0111...1111 = negative
 * 		 01110 < 01111 = positive, 11110 > 01111 = negative
 * 		 In these cases, the first bit (from left to right) will be checked for overflow.
 */

// Performing signed-2's complement addition
void func_signed_2s_addition(int a[], int b[], int result[]){
	// Variable to help with adding.
	int carry = 0;
	// Go from right to left to add, disregarding the last carrying digit if it exists.
	for(int i = MAX - 1; i >= 0; i--){
		// Initial digit to add (right side)
		if(i == MAX - 1){
			// If the addition of the digits results in a 2
			if(a[i] + b[i] == 2){
				carry = 1;
				result[i] = 0;
			}
			else{
				result[i] = a[i]+b[i];
			}
		}
		// Any additional digits, now including 0.
		else if(i != MAX - 1){
			// If the addition of the digits results in a 2
			if(a[i] + b[i] + carry == 2){
				carry = 1;
				result[i] = 0;
			}
			// If the addition of the digits results in a 3
			else if(a[i] + b[i] + carry == 3){
				carry = 1;
				result[i] = 1;
			}
			else{
				result[i] = a[i] + b[i] + carry;
				carry = 0;
			}
		}
	}

	// Check if overflow occurred.
	// If positives output a negative.
	if(a[0] == 0 && b[0] == 0 && result[0] == 1){
		puts("WARNING!: Overflow has occurred during the addition.");
		puts("The result is not reliable.");
	}
	// If negatives output a positive
	else if(a[0] == 1 && b[0] == 1 && result[0] == 0){
		puts("WARNING!: Overflow has occurred during the addition.");
		puts("The result is not reliable.");
	}
}

// Perform the signed-2's complement subtraction. (x + 2's complement(y))
void func_signed_2s_subtraction(int a[], int b[], int result[]){
	// Helper variable to keep track of the original "sign bit"
	int b_original = b[0];
	// Get the 2's complement version of b.
	func_2s_comp(b, b);

	// Add the results together.
	func_signed_2s_addition(a, b, result);

	// Check if overflow occurred.
	// If positives output a negative.
	if(a[0] == 0 && b_original == 0 && result[0] == 1){
		puts("WARNING!: Overflow has occurred during the addition.");
		puts("The result is not reliable.");
	}
	// If negatives output a positive
	else if(a[0] == 1 && b_original == 1 && result[0] == 0){
		puts("WARNING!: Overflow has occurred during the addition.");
		puts("The result is not reliable.");
	}

}

