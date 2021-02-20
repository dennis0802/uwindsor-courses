//============================================================================
// Name        : comp_tools.cpp
// Author      : Dennis Dao
// Version     : 1.0
// Lab Section : 55
// Description : Separate file for complement functions.
//============================================================================

#include "logic_tools.h" // Required as we use func_not for doing 1's comp!
#define MAX 8 // Byte = 8 bits

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



