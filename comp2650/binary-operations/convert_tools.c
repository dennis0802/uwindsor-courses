//============================================================================
// Name        : convert_tools.cpp
// Author      : Dennis Dao
// Version     : 1.0
// Lab Section : 55
// Description : Separate file for conversion functions.
//============================================================================

#include <math.h> // Include math functions to perform power operations (ex. 10^4=...).
#include <stdio.h>
#define MAX 8 // Byte = 8 bits

// Convert the binary number to decimal number.
void to_decimal(int a[]){
	// Variable to help convert to decimal
	int position = MAX - 1;

	// Multiply every position by its respective power of 2.
	for(int i = 0; i < MAX; i = i + 1){
		a[i] = a[i] * pow(2, position);
		position = position - 1;
	}
}

// Convert the binary number to octal number.
void to_octal(int a[]){
	// Variable to help convert to octal.
	int number = 0;

	// Get the decimal number
	to_decimal(a);
	for(int i = 0; i < MAX; i = i + 1){
		number = number + a[i];
	}
	// Divide by 8, taking note of the remainder
	for(int i = 0; number != 0; i = i + 1){
		a[i] = number % 8;
		number = number / 8;
	}

	// Given 8 positions in binary, the octal number will always have 3 positions.
	for(int i = 2; i >= 0; i = i - 1){
		printf("%d", a[i]);
	}
}

// Convert the binary number to hexadecimal number.
void to_hexadecimal(int a[]){
	// Variable to help convert to hexadecimal
	int number = 0;

	// Get the decimal number
	to_decimal(a);
	for(int i = 0; i < MAX; i = i + 1){
		number = number + a[i];
	}
	// Divide by 16, taking note of the remainder
	for(int i = 0; number != 0; i = i + 1){
		a[i] = number % 16;
		number = number / 16;
	}

	// Given 8 positions in binary, the hexadecimal number will always have 2 positions.
	for(int i = 1; i >= 0; i = i - 1){
		// Check if a letter should be printed.
		if(a[i] < 10){
			printf("%d", a[i]);
		}
		else if(a[i] == 10){
			printf("A");
		}
		else if(a[i] == 11){
			printf("B");
		}
		else if(a[i] == 12){
			printf("C");
		}
		else if(a[i] == 13){
			printf("D");
		}
		else if(a[i] == 14){
			printf("E");
		}
		else if(a[i] == 15){
			printf("F");
		}
	}
}
