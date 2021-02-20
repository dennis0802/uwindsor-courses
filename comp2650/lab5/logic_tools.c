//============================================================================
// Name        : logic_tools.cpp
// Author      : Dennis Dao
// Version     : 1.0
// Lab Section : 55
// Description : Separate file for logic functions.
//============================================================================

#define MAX 8 // Byte = 8 bits

// Performing the AND operator
void func_and(int a[], int b[], int result[]){
	for(int i=0; i< MAX; i = i+1){
		result[i] = a[i] & b[i];
	}
}

// Performing the OR operator
void func_or(int a[], int b[], int result[]){
	for(int i=0; i< MAX; i = i+1){
		result[i] = a[i] | b[i];
	}
}

// Performing the NOT operator
void func_not(int a[], int result[]){
	for(int i=0; i< MAX; i = i+1){
		result[i] = !a[i];
	}
}





