//============================================================================
// Name        : decimalToGray.c
// Author      : Dennis Dao
// Version     : 1.0
// Description : Allows the user to get the gray code of a decimal number
//============================================================================

#include <stdio.h>

// Function prototypes
void to_Gray();
// Extra function to convert numbers to binary
void to_binary(int num, int binary[]);

int main() {
	// Variable definitions
	int exit = 1;
	int input;

	setbuf(stdout, NULL);
	// Menu for user to see gray code or exit.
	while(exit == 1){
		puts("Enter the command number: ");
		puts("0) Exit");
		puts("1) Gray Code");
		scanf("%d", &input);

		if(input == 0){
			exit = 0;
			puts("You have exited the program.");
			printf("\n");
		}
		else if(input == 1){
			to_Gray();
			printf("\n");
		}
		else{
			puts("Invalid input. Please enter a valid number.");
			printf("\n");
		}
	}
	return 0;
}

// Turn the decimal number into gray code
void to_Gray(){
	// Helper variables.
	int num = -1;
	// Assume both the binary and gray code have 7 bits
	int binary[7];
	int grayCode[7] = {0,0,0,0,0,0,0};

	// Keep asking the user for a valid number
	while(num < 0 || num > 127){
		printf("Enter a decimal number between 0-127: ");
		scanf("%d", &num);
		if(num < 0 || num > 127){
			puts("Invalid input. Please enter a decimal number between 0-127");
			printf("\n");
		}
	}
	// Convert the number to binary
	to_binary(num, binary);

	// Go through each bit in the binary number and perform XOR on the bit to the right of it.
	for(int i = 0; i < 6; i++){
		// Leftmost bit
		if(i == 0){
			grayCode[i] = binary[i];
			// If the bit to the right is the same, assign the gray code in that spot 0
			if(binary[i] == binary[i+1]){
				grayCode[i+1] = 0;
			}
			// If they are different, assign it 1.
			else{
				grayCode[i+1] = 1;
			}
		}

		// All remaining bits
		else{
			// If the bit to the right is the same, assign the gray code in that spot 0
			if(binary[i] == binary[i+1]){
				grayCode[i+1] = 0;
			}
			// If they are different, assign it 1.
			else{
				grayCode[i+1] = 1;
			}
		}
	}

	// Output the gray code.
	printf("Gray code for %d -> ", num);
	for(int i = 0; i < 7; i++){
		printf("%d", grayCode[i]);
	}
	printf("\n");

}

// Turn the decimal number into binary
void to_binary(int num, int binary[]){
	// Helper variables
	int rem;
	int position = 6;

	// Divide the number by 2 and place the remainder into the array until the number is 0
	while(num != 0 || position >= 0){
		rem = num % 2;
		num /= 2;
		binary[position] = rem;
		position--;
	}
}
