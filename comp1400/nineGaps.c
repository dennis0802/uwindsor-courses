/*
 * NineGaps (Function Version)
 * Developer: Dennis Dao
 * Student Number: 110010116
 * Date: Novemeber 24, 2019
 * version 1.0
 */

// This program was made to play the NineGaps game with functions in the code.

// C Standard Library for input/output functions
#include<stdio.h>
// C Standard Library for utility functions such as rand()
#include <stdlib.h>
// C Standard Library for time and date functions
#include <time.h>

// -------------------- Function Prototypes -------------------------
// Generate a random main board by shuffling the main_board
void shuffle_board(int board[]);

// Generate random operators ( + , - , x )
void random_operators(char operators_array[]);

// Based on the selected level, 3 or 5 or 7 board values will be hidden.
void set_board(int game_board[], int missing_array[], int level);

// Display the game board after each update
void display_board(char operators_array[], int game_board[], int temp_board[], int column_results[], int row_results[]);

// Display the missing values and update missing_count
int display_missing_values(int missing_array[]);

// Check the results
int check_results(int temp_board[], int main_board[]);

// Calculate the results in columns and rows
void calculate_results(int row_results[], int column_results[], int main_board[], char operators_array[]);

// -------------------- Global Variables ------------------------------------
// rand_num will be used to store the result of random number generations, temp1 will be used as a temporary variable
int rand_num1, rand_num2, temp1;
// i and j are used for loop indexes
int i, j;
// missing_count keeps track of the number of missing values in the game board.
int missing_count;
// Flag variable to determine if the user solves the game correctly.
char check_game;

// Main function executes the program
int main(){
	setbuf(stdout, NULL);

    int main_board[9]={1,2,3,4,5,6,7,8,9}; // define the main board to store all the values from 1-9
    int missing_array[9]; // define an array of size 9 to keep track of missing values
    int game_board[9]; // define an array to form the actual game board with random numbers and hidden values
    int temp_board[9]; // define an array which is a copy of the game_board and will be displayed to the user and will be updated in each iteration
    int row_results[3]; // this is an array that stores the results of calculation of each row
    int column_results[3]; // this is an array that stores the results of calculation of each column
    char operators_array[12]; // this is an array that stores random operations
    int level; // this variable stores the level of difficulty
    int play_again; // this is flag variable to determine if the user wants to play again or not
    int missing_count; // this is a variable that keep track of the number of missing values in the game board.
    srand(time(NULL));

    fflush(stdout);
    do{
	// check_game is initialized at 1 and level is initialized at 0.
        check_game=1;
        level=0;
        printf("Welcome to Nine-Gaps game!...\n");
	    printf("*****************************\n");
	    printf("      *****************      \n");
	    printf("            *****            \n");
	    printf("              *              \n");

        // Get the level of difficulty from the user
        do{
		    puts("Choose the level of difficulty (1-Beginner, 2-Intermediate, 3-Advanced, 4-Expert):");

		    scanf("%d",&level);
		    // If the level is less than 1 or greater than 4, print an error message.
		    if ((level < 1) || (level > 4))
			    puts("The entered value is not valid");
		    // Else, check each case the player may have inputted.
		    else{
		        switch (level){
			    // If 1 was inputted, the user is in the beginner level.
		            case 1:
		                puts("You have chosen the Beginner level");
		                break;
			    // If 2 was inputted, the user is in the intermediate level
		            case 2:
		                puts("You have chosen the Intermediate level");
		                break;
			    // If 3 was inputted, the user is in the advanced level
		            case 3:
		                puts("You have chosen the Advanced level");
		                break;
			    // If 4 was inputted, the user is in the expert level.
		            case 4:
		                puts("You have chosen the Expert level");
		                break;
		        }
			// Break out the loop.
		        break;
		    }
	    } while (1);
        //////////////////////////////////////////////////

        // 1 - Generate a random main board by shuffling the main_board
        shuffle_board(main_board);

        // 2 - Generate random operators ( + , - , x )
        random_operators(operators_array);

        // 3 - Calculate the results in columns and rows
        calculate_results(row_results, column_results, main_board, operators_array);

        /// Initializing missing array to 0
        for(i = 0 ; i < 9 ; i++)
            missing_array[i]=0;

        ////////////////////////////////////////////////////////

        /// Copy the main board into game_board
        for(i = 0; i < 9; i++)
            game_board[i] = main_board[i];

        /////////////////////////////////////////////////////////

        //4- Based on the selected level, 3 or 5 or 7 board values will be hidden.
        set_board(game_board, missing_array, level);

        /// Copy the game board into a temporary board
        for(i = 0; i < 9; i++)
            temp_board[i] = game_board[i];

        ///////////////////////////////////////////////////////

        // The inner loop to get values from the user
        do{
                // 5 - Display the game board after each update
        	display_board(operators_array, game_board, temp_board, column_results, row_results);

        	// 6 - Display the missing values and update missing_count
        	missing_count = display_missing_values(missing_array);

		// Break if the missing values are empty.
                if (missing_count==0){
                	break;
		}

        	// Get user's guess (location and value) and check inputs' validity
	        printf("Enter a row number (1-3), column(1-3), value(One of the missing values):\n");
		int r, c, v;
	        scanf("%d %d %d", &r, &c, &v);

		// If 0 is inputted at any point, break out the loop.
	        if (r==0 || c==0 || v==0)
	            break;

		// If the row or column is greater than 3 or less than 1, print an error message.
	        if (r < 1 || r > 3 || c < 1 || c > 3){
	            puts("Invalid row and/or column numbers. Try again.");
	            continue;
	        }

		// If the value inputted is less than 1 or greater than 9, print an error message.
	        if (v < 1 || v > 9) {
	            puts("Invalid cell value. Try again.");
	            continue;
	        }

		// If the value inputted is already in the spot, print an error message.
	        if (missing_array[v-1]<1) {
	            puts("This value is already there. Try again.");
	            continue;
	        }

		// If the spot does not have a missing value, print an error message
                if (game_board[3*(r-1) + (c-1)]!='?') {
                	puts("This cell could not be changed. Try again.");
	            	continue;
	        }
		// Else, run the code.
	        else{
		    // If the spot is valid, the spot in the temp board is now that value.
	            if (game_board[3*(r-1) + (c-1)] == temp_board[3*(r-1) + (c-1)]){
	                temp_board[3*(r-1) + (c-1)] = v;
	                missing_array[v-1]=0;
	            }
		    // Else, the spot is a guessed value and the two values are swapped.
	            else{
                        // Return value to missing values and update the temp_board
			temp1 = temp_board[3*(r-1)+(c-1)];
			temp_board[3*(r-1) + (c-1)] = v;
	                missing_array[temp1 - 1] = temp1;
	                missing_array[v-1]= 0;
	            }
	        continue;
	        }

        } while (1); // End of the inner loop

        // 7 - Check the results
	// If check_game is still 1 after calling the function, the user has won.
        if (check_results(temp_board, main_board))
            printf ("**** Congratulations!!!****\n ***You Won!!!!*** \n");
	// Else, check_game was changed the user has lost.
        else
            printf (":( Sorry it is not correct :( \n");

	// Prompt user if they want to play again.
        printf("#######################################\n");
        printf ("   Do you want to play again? (Yes:1, No:0)\n");
        printf("#######################################\n");
        scanf ("%d", &play_again);

	// If they don't want to play again, display a goodbye message.
        if (!play_again){
            printf("Bye!\n");
            break;
        }
    } while (1); // End of the outer loop
}

// ------------------ Functions --------------------------------
// 1 - Generate a random main board by shuffling the manin_board
void shuffle_board(int board[]) {
	// Shuffle the numbers around 50 times.
	for(i = 0; i < 50; i++){
		// rand_num1 and rand_num2 are random numbers from 0-8
		rand_num1 = rand() % 9;
		rand_num2 = rand() % 9;
		// temp1 is the first random number's element of the main board.
		temp1 = board[rand_num1];
		// That element of the main board is now the second random number's element of the main board
		board[rand_num1] = board[rand_num2];
		// That element of the main board is now temp1
		board[rand_num2] = temp1;
	}
}

// 2 - Generate random operators ( + , - , x )
void random_operators(char operators_array[]) {
	// Generate 12 different operators
	for(i = 0; i < 12; i++){
		// rand_num1 is a random number from 0-2
		rand_num1 = rand() % 3;

		// If rand_num1 is 0, add a '+' to the operator array.
		if(rand_num1 == 0){
			operators_array[i] = '+';
		}
		// Else, if rand_num is 1, add a '-' to the operator array.
		else if (rand_num1 == 1){
			operators_array[i] = '-';
		}
		// Else, add a '*' to the operator array.
		else{
			operators_array[i] = '*';
		}
	}
}

//3 - Calculate the results in columns and rows
void calculate_results(int row_results[], int column_results[], int main_board[], char operators_array[]){
	// Calculate row results
	for(i = 0; i <= 2; i++){
		// Loop through each row operator.
		for(j = 0+2*i; j < 2+2*i; j++){
			// If j is 0, 2, or 4 (starting operators of each row, check what operation is being performed on the first two elements of the ith row.
			if( j == 0 || j == 2 || j == 4){
				// If the jth element is '+', add the first two elements together
				if(operators_array[j] == '+'){
					row_results[i] = main_board[j+i*1] + main_board[j+1+1*i];
				}
				// Else, if the jth element is '-'. subtract the first two elements.
				else if(operators_array[j] == '-'){
					row_results[i] = main_board[j+i*1] - main_board[j+1+1*i];
				}
				// Else, multiply the first two elements together.
				else{
					row_results[i] = main_board[j+i*1] * main_board[j+1+1*i];
				}
			}
			// Else, the 3rd element is computed with the results of the first two elements
			else{
				// If the jth element is '+', add the 3rd element to the previous calculation.
				if(operators_array[j] == '+'){
                                        row_results[i] +=  main_board[j+1+1*i];
                                }
				// Else, if the jth element is '-'. subtract the 3rd element to the previous calculation.
                                else if(operators_array[j] == '-'){
                                        row_results[i] -= main_board[j+1+1*i];
	                        }
				// Else, multiply the 3rd element to the previous calculation.
                                else{
                                        row_results[i] *= main_board[j+1+1*i];
                                }
			}
		}
	}

	// Calculate the column results
	for(i = 0; i <= 2; i++){
		// Loop through each column operator.
		for(j = 6+i; j <= 9+i; j+= 3){
			// If j is 6, 7, or 8 (starting operators of each column, check what operation is being performed to the first two elements of the ith row.
			if(j == 6 || j == 7 || j == 8){
				// If the jth element is '+'. add the first two elements
				if(operators_array[j] == '+'){
                                        column_results[i] = main_board[j-6] + main_board[j-3];
                                }
				// If the jth element is '-', subtract the first two elements
                                else if(operators_array[j] == '-'){
                                        column_results[i] = main_board[j-6] - main_board[j-3];
                                }
				// Else, multiply the first two elements together.
                                else{
                                        column_results[i] = main_board[j-6] * main_board[j-3];
                                }
                        }
			// Else, the 3rd element is computed with the results of the first two elements
                        else{
				// If the jth element is '+', add the 3rd element to the previous calculation.
                                if(operators_array[j] == '+'){
                                        column_results[i] +=  main_board[j-3];
                                }
				// Else, if the jth element is '-', subtract the 3rd element to the previous calculation.
                                else if(operators_array[j] == '-'){
                                        column_results[i] -= main_board[j-3];
                                }
				// Else, multiply the 3rd element to the previous calculation.
                                else{
                                        column_results[i] *= main_board[j-3];
                                }
                        }
                }
        }
}


// 4 - Based on the selected level, 3 or 5 or 7 board values will be hidden.
void set_board(int game_board[], int missing_array[], int level) {
	// Set i to 0
	i = 0;
	// While i is less than the level multiplied by 2 plus 1, run the code.
	while (i < level*2+1){
		// r and c are random numbers from 0-2.
		int r = rand() % 3;
		int c = rand() % 3;
		// If the element of the game board is not '?', the missing array for that element minus 1 is now that element
		if(game_board[3*r+c] != '?'){
			missing_array[game_board[3*r+c]-1] = game_board[3*r+c];
			// The element of the game board is now '?'.
			game_board[3*r+c] = '?';
			// Increment i
			i++;
		}
	}
}

// 5 - Display the game board after each update
void display_board(char operators_array[], int game_board[], int temp_board[], int column_results[], int row_results[]) {
	printf("Game Board:\n");
	printf("---------------------------------------------------\n");
	// Display column operators
	for(i = 0; i < 3; i++){
		if(i > 0){
			// Loop through the operators and print them.
			for(j = 0; j < 3; j++){
				printf(" %c\t\t", operators_array[3*(i+1)+j]);
			}
			printf("\n");
		}

		// Loop through the numbers
		for(j = 0; j < 3; j++){
			// Display preset values
			if(game_board[(i*3)+j] != '?'){
				printf(" %d\t ", temp_board[(i*3)+j]);
			}
			// Display possible correct guesses
			else if (game_board[(i*3)+j] != temp_board [(i*3)+j]){
				printf(" %d?\t ", temp_board[(i*3)+j]);
			}
			// Display missing values
			else{
				printf(" ?\t ");
			}

			// Display operators
			if(j < 2){
				printf(" %c\t", operators_array[(i*2) + j]);
			}
			// Else, display row results
			else{
				printf("= %d", row_results[i]);
			}
		}
		printf("\n");

		// Display equal signs if i is 2.
		if(i == 2){
			printf(" =\t\t =\t\t = \n");
		}
	}

	// Display column results.
	for(i = 0; i < 3; i++){
		printf(" %d\t\t", column_results[i]);
	}
	printf("\n---------------------------------------------------\n");
	puts("List of Missing Values = ");
}

// 6 - Display the missing values and update missing_count
int display_missing_values(int missing_array[]) {
	// missing_count is set to 0.
	missing_count = 0;
	// Loop through the missing_array.
	for(i = 0; i < 9; i++){
		// If an element is not 0, add to missing_count and print the missing value.
		if(missing_array[i] != 0){
			printf("%d\t", missing_array[i]);
			missing_count++;
		}
		// Else, print nothing.
		else{
			printf("");
		}
	}
	printf("\n---------------------------------------------------\n");
	// Else, return missing_count to the main function.
	return missing_count;
}

// 7 - Check the results
int check_results(int temp_board[], int main_board[]) {
	// Loop through both the temp and main board arrays.
	for(i = 0; i < 9; i++){
		// If the ith element in the temp board is not equal to the ith element in the main board, check_game is assigned 0 (you lose).
		if(temp_board[i] != main_board[i]){
			check_game = 0;
		}
	}
	// Return check_game to the main function.
	return check_game;
}
