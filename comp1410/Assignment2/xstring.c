/*
 * Student Name: Dennis Dao
 * Student Number: 110010116
 */

// Linking the xstring.h with the xstring.c file.
#include "xstring.h"

/*
 * Use this file to complete the implementation of the xstring library
 */

// Function finds the first occurence of a character
int FindFirstOccurrence(char c , char *pStr ){
	int index = 0;
	while(*pStr != '\0'){
		// Return index if match found.
		if(*pStr == c){
			return index;
		}
		// Increment index and move to next character
		index++;
		pStr++;
	}
	return -1;
}

// Function finds the last occurence of a character
int FindLastOccurrence(char c, char *pStr ){
	int index = 0;
	int lastFlag = -1;
	while(*pStr != '\0'){
		// If match found, lastFlag is now the index where the match was found.
		if(*pStr == c){
			lastFlag = index;
		}
		// Increment index and move to next character.
		index++;
		pStr++;
	}
	return lastFlag;
}

// Function gets the weight of a C string (summation of all characters)
int GetStringWeight (char *pStr ){
	int weight = 0;
	// Add elements of the string until delimiter character is found
    	while(*pStr != '\0'){
        	weight += *pStr;
        	pStr++;
    	}
	// Return the weight
    	return weight;
}

// Function replaces a character x for another character c in a string
void ReplaceCharacter(char x, char c , char *pStr ){
	while(*pStr != '\0'){
		// If the string pointer points to the character to be found, replace it with the character to replace it with.
        	if(*pStr == x){
                	*pStr = c;
            	}
            	pStr++;
        	}
}

// You could use (call) this function to help you implement the RemoveCharacter function
// Make sure that DeleteChartAt keeps the char array a valid C String ends with '\0'
void DeleteCharAt(int index, int size, char array[]){
	if(index < 0 || index >size -1){
        	return;
	}

    	for(int i=index; i < size-1; i++){
        	array[i] = array[i+1];
    	}
	array[size-1] = '\0';
}

// Function removes a charcter c in an char array str.
void RemoveCharacter(char c, char str[]){
	int i;
	int length = 0;
	// Get length of the char array.
	for(i = 0; str[i] != '\0'; i++){
		length++;
	}
	// Determine if a character matches with the character c.
	for(i = 0; str[i] != '\0'; i++){
		while(str[i] == c){
			// Call DeleteCharAt if match found.
			DeleteCharAt(i, length, str);
		}
	}
}

// Helper function to reverse string with its pointer by getting string length.
int pStringLength(char *pStr){
        int n;
        // Add up number of characters until delimiter character is found.
        for(n = 0; *pStr != '\0'; pStr++){
                n++;
        }
        return n;
}

// Helper function to reverse string.
void swapString(char *str1, char *str2){
        char temp;
        temp = *str1;
        *str1 = *str2;
        *str2 = temp;
}

// Function reverses a string
void ReverseString(char *pStr){
	// Variable definitions
	int length = pStringLength(pStr);
	char* start = pStr;
	char* end = pStr;
	int i;

	// Let the end pointer point to the end of the string (not the delimiter character)
	for(i = 0; i < length - 1; i++){
		end++;
	}
	// Swap the characters of the start and ends of the string.
	for(i = 0; i < length / 2; i++){
		swapString(end, start);
		// Point to the next character over
		start++;
		// Point to the previous character over.
		end--;
	}
}

// Function converts all characters of a string to upper case.
void ToUpperCase(char *pStr){
        while(*pStr != '\0'){
            if(*pStr >= 'a' && *pStr <= 'z'){
                    *pStr = *pStr + 'A' - 'a';
            }
            pStr++;
        }
}

// Function converts all characters of a string to lower case.
void ToLowerCase(char *pStr){
        while(*pStr != '\0'){
            if(*pStr >= 'A' && *pStr <= 'Z'){
                    *pStr = *pStr + 'a' - 'A';
            }
            pStr++;
        }
}
