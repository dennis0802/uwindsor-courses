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

/*
 * For these functions, assume a is the top number and b is the bottom number in the arithmetic.
 * 	100 (a)
 * +101 (b)
 * result
 */

// Performing signed-magnitude addition
void func_signed_mag_addition(int a[], int b[], int result[]){
	// Variable to help with adding.
	int carry = 0;

	// Forms of x + y and (-x) + (-y)
	if((a[0] == 0 && b[0] == 0) || (a[0] == 1 && b[0] == 1)){
		// Go from right to left to add.
		for(int i = MAX - 1; i > 0; i--){
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
			// Any additional digits.
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

		// Check the signed-bit
		// Both positive
		if(a[0] == 0 && b[0] == 0){
			result[0] = 0;
		}
		// Both negative
		else if(a[0] == 1 && b[0] == 1){
			result[0] = 1;
		}

		// Check for overflow - if there is a last carry during addition.
		if(carry > 0){
			result[0] = -1;
			puts("WARNING!: Overflow has occurred during the addition.");
			puts("An arbitrary -1 has been placed at the sign bit to represent this error.");
			puts("Keep this in mind if selecting to output in binary.");
			puts("The result is not reliable.");
		}
	}

	// The given numbers should be subtracted instead.
	// Form of (+x) + (-y) = (x - y)
	else if(a[0] == 0 && b[0] == 1){
		// Assume the 2nd sign bit is now positive to allow subtraction in the next function.
		b[0] = 0;
		func_signed_mag_subtraction(a, b, result);
	}
	// Form -x + (+y) = (y - x)
	else if(a[0] == 1 && b[0] == 0){
		// Assume the 1st sign bit is now positive to allow subtraction in the next function.
		a[0] = 0;
		func_signed_mag_subtraction(b, a, result);
	}
}

// Perform the signed-magnitude subtraction.
void func_signed_mag_subtraction(int a[], int b[], int result[]){
	// Variable to help subtracting
	int carry = 0;
	// Variable to flag a last borrow has occurred
	int lastCarryOccurred = 0;
	// Variable to help get the position the extra digit was found.
	int k;

	// Form of x - y or y - x
	if(a[0] == 0 && b[0] == 0){
		for(int i = MAX-1; i > 0; i--){
			// If the subtraction cannot be done.
			if(a[i] - b[i] < 0){
				// Look for a digit to the left of the current digit to borrow from
				for(int j = i - 1; j >= 0; j--){
					// Digit was found
					if(a[j] > 0){
						a[j] = a[j] - 1;
						carry = 2;
					}
					// No digit was found
					else if(j == 0){
						lastCarryOccurred = 1;
						carry = 2;
					}
					// Assign the current digit position to the helper variable
					k = j;
				}

				// Go back to the original digit i, applying the carrying digit to every position
				for(; k <= i; k++){
					// The original digit i was found
					if(k == i){
						a[k] = carry + a[k];
						carry = 0;
						break;
					}
					else{
						a[k] = carry - 1 + a[k];
					}
				}
			}
			else{
				result[i] = a[i] - b[i];
			}
			result[i] = a[i] - b[i];
		}

		// Check the signed-bit
		// Last carry has occurred
		if(lastCarryOccurred == 1){
			result[0] = 1;
			// Subtract the above result with the last carry to get the correct negative number.
			int lastCarry[MAX] = {1};
			for(int i = MAX - 1; i > 0; i--){
				// If the subtraction cannot be done.
				if(lastCarry[i] - result[i] < 0){
					// Look for a digit to the left of the current digit to borrow from
					for(int j = i; j > 0; j--){
						// Digit was found
						if(lastCarry[j-1] > 0){
							lastCarry[j-1] = lastCarry[j-1] - 1;
							carry = 2;
						}
						// Assign the current digit position to the helper variable
						k = j;
					}

					// Go back to the original digit i, applying the carrying digit to every position
					for(; k <= i; k++){
						// The original digit i was found
						if(k == i){
							lastCarry[k] = carry + lastCarry[k];
							carry = 0;
							break;
						}
						else{
							lastCarry[k] = carry - 1 + lastCarry[k];
						}
					}
				}
				else{
					result[i] = lastCarry[i] - result[i];
				}
			}
		}
		// No last carry occurred.
		else if(lastCarryOccurred == 0){
			result[0] = 0;
		}
	}

	// The given numbers should be subtracted in the opposite order.
	// Form of (-x) - (-y) = y - x
	else if(a[0] == 1 && b[0] == 1){
		// Assume both sign bits are positive to allow subtraction in the recalled function.
		b[0] = 0;
		a[0] = 0;
		func_signed_mag_subtraction(b, a, result);
	}
	// The given numbers should be added instead.
	// Form of (+x) - (-y) = (x + y)
	else if(a[0] == 0 && b[0] == 1){
		b[0] = 0;
		func_signed_mag_addition(a, b, result);
	}
	// Form of (-x) - (+y) = -(x + y)
	else if(a[0] == 1 && b[0] == 0){
		b[0] = 1;
		func_signed_mag_addition(a, b, result);
	}
}

