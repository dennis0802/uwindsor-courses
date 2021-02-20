//============================================================================
// Name        : shiftoperator.c
// Author      : Dennis Dao
// Version     : 1.0
// Description : Program to investigate the << shift operator
//============================================================================

#include <stdio.h>
#include <stdlib.h>

int main(void){
	// Variable definition
	int a;
	int pause;

	setbuf(stdout, NULL);

	// Get number from user
	printf("Enter the first operand: ");
	scanf("%d", &a);

	// Check the >> operator
	puts("Expected: ");
	printf("%d/2 =  %d \n", a, a/2);
	printf("%d/4 =  %d \n", a, a/4);
	printf("%d/8 =  %d \n", a, a/8);
	puts("Actual: >> divides by 2^i, where i is the number of the shifts right");
	printf("%d/2 = %d \n", a, a >> 1 );
	printf("%d/4 = %d \n", a, a >> 2 );
	printf("%d/8 = %d \n", a, a >> 3 );
	printf("\n");

	// Check the << operator
	puts("Expected: ");
	printf("%d * 2 =  %d \n", a, a * 2);
	printf("%d * 4 =  %d \n", a, a * 4);
	printf("%d * 8 =  %d \n", a, a * 8);
	puts("Actual: << multiplies by 2^i, where i is the number of shifts left");
	printf("%d * 2 = %d \n", a, a << 1 );
	printf("%d * 4 = %d \n", a, a << 2 );
	printf("%d * 8 = %d \n", a, a << 3 );

	// For release version - ask the user for any input so the executable file pauses and allows the user to see their results.
	printf("\n");
	puts("Enter any key to continue.");
	scanf("%d", &pause);

}
