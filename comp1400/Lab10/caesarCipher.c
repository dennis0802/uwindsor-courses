/*
 * Lab 10 - Exercise 1
 * Developer: Dennis Dao
 * Date: Nov 22, 2019
 * version 1.0
 */

// This program was made to perform the Caesar cipher.

// C Standard Library for input/output functions.
#include <stdio.h>
// C Standard Library for strings.
#include <string.h>

// Function prototype of cipherToPlain
char * cipherToPlain(char cipher[30], int key);

// text is the text inputted from the user, a character array capable of holding at most 29 characters.
char text[30];
// cipherKey is the key for each letter.
int cipherKey;

// Main function executes the program
int main(void){
	// Prompt user for text
	puts("Please enter your text: ");
	scanf("%[^\n]", text);
	// Prompt user for the cipher key.
	puts("Please enter the Cipher Key: ");
	scanf("%d", &cipherKey);

	// Loop through each letter and peform the cipher.
	for(int i = 0; i < strlen(text); i++){
		// If the position is a space, do nothing.
		if(text[i] == ' '){
		}
		// Else, check whether the character is uppercase or lowercase
		else {
			// If the text is less than 97 (ASCII a) and the sum of the text and key is greater than 90 (ASCII Z), subtract 26 from the text to set it to 'A'.
			if(text[i] < 96 && text[i] + cipherKey > 90){
				text[i] -= 26;
			}
			// Else, if the sum of the text and key is less than 122 (ASCII z), subtract 26 from the text to set it to 'a'.
			else if(text[i] + cipherKey > 122 ){
				text[i] -= 26;
			}
			// Add the cipher key to the current character
			text[i] += cipherKey;
		}

	}

	// Print out the ciphered text.
	printf("Your cipher text is: %s\n", text);
	printf("Your plain text was: %s\n", cipherToPlain(text, cipherKey));

}
// End of main function.

// cipherToPlain performs the Caesar cipher from ciphertext to plain text.
char * cipherToPlain(char cipher[30], int key){
	// Loop through each letter and peform the cipher.
	for(int i = 0; i < strlen(cipher); i++){
		// If the position is a space, do nothing.
		if(cipher[i] == ' '){
		}
		// Else, check whether the character is uppercase or lowercase
		else {
			// If the difference of the text and key is less than 65 (ASCII A), add 26 to the text.
			if(cipher[i] - cipherKey < 65){
				cipher[i] += 26;
			}
			// Else, if the text is greater than 90 (ASCII Z) and the difference of the text and key is less than 97 (ASCII a), add 26 to the text.
			else if(cipher[i] > 90 && cipher[i] - cipherKey < 97){
				text[i] += 26;
			}
			// Subtract the cipher key to the current character
			cipher[i] -= cipherKey;
		}

	}
	// Return the plain text
	return cipher;

}
