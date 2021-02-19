/*
 * Student Name: Dennis Dao
 * Student Number: 110010116
 */

#include <stdio.h>
// Linking the main file and xstring.h file
#include "xstring.h"

int main(){
	// Variable defintiions
	char test [150];
    	char c;
    	char x;

	// Prompt for a string
    	printf("Please enter a string of characters: ");
    	scanf("%150[^\n]s", test);

	// Prompt for characters
    	printf("Please enter a character to test the function Find First Occurrence: ");
    	scanf(" %c", &c);

    	printf("The first occurrence of %c in %s is at index = %d \n", c, test, FindFirstOccurrence(c, test));

    	printf("Please enter a character to test the function Find Last Occurrence: ");
    	scanf(" %c", &c);

    	printf("The last occurrence of %c in %s is at index = %d \n", c, test, FindLastOccurrence(c, test));

	// String weight function call
    	printf("The weight of the C String %s is = %d \n", test, GetStringWeight(test));

	// ToUpperCase and ToLowerCase function calls
    	ToUpperCase(test);
    	printf("The uppercase version is = %s \n", test);

    	ToLowerCase(test);
    	printf("The lowercase version is = %s \n", test);

	// ReverseString function call
    	ReverseString(test);
    	printf("The reversed version is = %s \n", test);

	// Prompt for characters to replace when calling ReplaceCharacter function
    	printf("Please enter the character you want to replace when testing the function Replace Character: ");
    	scanf(" %c", &x);

    	printf("Please enter the new character you want to insert when testing the function Replace Character: ");
    	scanf(" %c", &c);

    	ReplaceCharacter(x, c, test);
    	printf("The new C String after replacing with %c is %s \n", c, test);

	// Prompt for character to remove when calling RemoveCharacter function
    	printf("Please enter the character you want to remove when testing the function Remove Character: ");
    	scanf(" %c", &c);
    	RemoveCharacter(c, test);

    	printf("%s \n", test);

    	return 0;
}
