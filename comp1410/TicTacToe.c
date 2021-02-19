/*
 * Student Name: Dennis Dao
 * Student Number: 110010116
 */

#include <stdio.h>

// The program prints a tic tac toe board that can be played.

// Function prototypes
void initializeBoard(int m, int n, char board[][n]);
void printBoard(int m, int n, char board[][n]);
void createBoard(int m, int n, char board[][n]);
int isValidBoard(int m, int n, char board[][n]);
void listWinningCells(int m, int n, char board[][n]);
char whoIsTheWinner(int m, int n, char board[][n]);
// Extra functions to check winning cells.
char rowWin(int m, int n, char board[][n]);
char colWin(int m, int n, char board[][n]);
char diagonalWin(int m, int n, char board[][n]);

// Main function (Q7 Answer)
int main(void){
	setbuf(stdout, NULL);
	// Declared variables
	int rows = 3;
	int cols = 3;
	char board[rows][cols];
	char input;
	char winner;
	int loop = 1;
	int test;
	char playAgain;
	int spotsTaken;

	initializeBoard(rows, cols, board);
	// Call initializeBoard function
	while(loop){
		whoIsTheWinner(rows, cols, board);
		// Prompt user for various options
		puts("Press 'p' to print the tic-tac-toe board");
       		puts("Press 'c' to create a tic-tac-toe board with some X and O cells");
        	puts("Press 't' to test if a tic-tac-toe board board is a valid or invalid board");
        	puts("Press 'w' to predict winning cell for player X or O");
		puts("Press 'd' to determine winning player.");
        	puts("Press 'e' to Exit");
		scanf(" %c", &input);

		// Check each case for an option
		switch(input){
			// Printing board
			case 'p':
			case 'P':
				printf("\n");
				printBoard(rows, cols, board);
				break;

			// Creating board
                       	case 'c':
                       	case 'C':
				printf("\n");
				createBoard(rows, cols, board);
				break;

			// Testing validity of board
                       	case 't':
                       	case 'T':
				test = isValidBoard(rows, cols, board);
				if(test == 0 || test == 1){
					puts("Valid board.");
				}
				else{
					puts("Invalid board.");
				}
                                printf("\n");
                               	break;

			// Predicting a winner
                       	case 'w':
                       	case 'W':
				listWinningCells(rows, cols, board);
				break;

			// Extra function - Determining the winner.
			case 'd':
			case 'D':
				// Count how many taken spots there are on the board.
				spotsTaken = 0;
                                for(int i = 0; i < rows; i++){
                                        for(int j = 0; j < cols; j++){
                                                if(board[i][j] == 'X' || board[i][j] == 'O'){
                                                        spotsTaken++;
                                                }
                                        }
                                }
				winner = whoIsTheWinner(rows, cols, board);

				// Print out a winning message if there is a winner.
				if(winner == 'X' || winner == 'O'){
					printf("\nPlayer %c has won.\n\n", winner);
					// Prompt if player wants to play again.
					puts("Play again? (Y = yes, N = no)");
					scanf(" %c", &playAgain);
					switch(playAgain){
						case 'y':
						case 'Y':
							// Reinitialize the board if they do.
							initializeBoard(rows, cols, board);
						break;
						case 'n':
						case 'N':
							loop = 0;
							puts("See you soon!");
							break;
						}
				}
				else if(winner == 'D' && spotsTaken == 9){
					printf("\nDraw. There is no winner.\n\n");
                                        // Prompt if player wants to play again.
                                        puts("Play again? (Y = yes, N = no)");
                                        scanf(" %c", &playAgain);
                                        switch(playAgain){
                                                case 'y':
                                                case 'Y':
                                                        // Reinitialize the board if they do.
                                                        initializeBoard(rows, cols-1, board);
                                                break;
                                                case 'n':
                                                case 'N':
                                                        loop = 0;
                                                        puts("See you soon!");
                                                        break;
                                                }
				}
                                printf("\n");
                               	break;

			// Exiting the program
			case 'e':
			case 'E':
				// Change loop to 0 to break out the while loop.
				loop = 0;
				puts("See you soon!");
				break;

			// If no case matches.
			default:
				puts("Invalid input!");
                                printf("\n");
				break;
		}
	}
}

// Function definitions
// Initializing Tic-Tac-Toe Board (Q1 Answer)
void initializeBoard(int m, int n, char board[][n]){
	int c = 1;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			board[i][j] = c + '0';
			c++;
		}
	}
}

// Printing Tic-Tac-Toe Board (Q2 Answer)
void printBoard(int m, int n, char board[][n]){
	printf("-------------\n");
	for(int i = 0; i < m; i++){
		printf("|");
		for(int j = 0; j < n; j++){
			// Printing element in the ith, jth location of the array.
			printf(" %c |", board[i][j]);
			}
		printf("\n-------------\n");
		}
	printf("\n");
}

// Creating Tic-Tac-Toe Board (Q3 Answer)
void createBoard(int m, int n, char board[][n]){
	// Cell number
	int cell = 0;
	// Input X or O
	char input;

	// Loop until the user enters -1.
	do{
		// Call printBoard function
		printBoard(m, n, board);
		// Prompt user for a cell number
		puts("Enter the number of the cell where you want to insert X or O or enter -1 to exit.");
		scanf("%d", &cell);

		// Entering -1.
		if(cell == -1){
			break;
		}
		// If valid cell is entered, prompt user for X or O.
		else if(cell > 0 && cell < 10){
			puts("Type X or O");
			scanf(" %c", &input);
			// Array number is cell - 1.
			int index = cell - 1;
			int row = index / 3;
			int col = index % 3;
			// Check if character input is valid.
			if(input == 'X' || input == 'O'){
				// Check if spot has not been taken.
				if(board[row][col] != 'X' && board[row][col] != 'O'){
					// Set input to location on board
					board[row][col] = input;
				}
			}
		}
	}while(cell != -1);
	printf("\n");
}

// Checking if a board is a valid board (Q4 Answer)
int isValidBoard(int m, int n, char board[][n]){
	// Count of Xs and Os in the board
	int oCount = 0;
	int xCount = 0;
	// Loop through each position in the array
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			// If ith, jth location in the array matches X or O, increment respective counter
			if(board[i][j] == 'X'){
				xCount++;
			}
			else if(board[i][j] == 'O'){
				oCount++;
			}
		}
	}
	/*
         * Board is valid if there is nothing on the board or if the difference
	 * between Xs and Os/ Os and Xs is 0 or 1
	 */
        // No Xs and/or Os on the board
        if(xCount == 0 && oCount == 0){
                return 0;
        }
	// Difference of Xs and Os
	if((xCount - oCount) == 0 || (xCount - oCount) == 1){
		return 0;
	}
	// Difference of Os and Xs
	else if((oCount - xCount) == 0 || (oCount - xCount) == 1){
		return 0;
	}
	// Invalid number of Xs and/or Os on the board
	else{
		return -1;
	}
}

// Listing winning cells (Q5 Answer)
void listWinningCells(int m, int n, char board[][n]){
	// Check validity of board
	int valid = isValidBoard(m, n, board);
	if(valid == -1){
		puts("No winning cells can be predicted at this time. The board is invalid.");
		printf("\n");
	}
	else{
		// Check that positions near a certain cell are the same and the cell is not occupied yet.
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				// Check leftmost row cell
				if(board[i][j+1] == board[i][j+2] && j == 0 && board[i][j] != 'X' && board[i][j] != 'O'){
					printf("Cell #%d is a winning cell for player %c.\n\n", i*3+1, board[i][j+1]);
				}
				// Check middle row cell
				if(board[i][j-1] == board[i][j+1] && j == 1 && board[i][j] != 'X' && board[i][j] != 'O'){
					printf("Cell #%d is a winning cell for player %c.\n\n", i*3+2, board[i][j-1]);
				}
				// Check rightmost cell
				if(board[i][j-2] == board[i][j-1] && j == 2 && board[i][j] != 'X' && board[i][j] != 'O'){
					printf("Cell #%d is a winning cell for player %c.\n\n", i*3+3, board[i][j-1]);
				}
				// Check topmost column cell
				if(board[i+1][j] == board[i+2][j] && i == 0 && board[i][j] != 'X' && board[i][j] != 'O'){
					printf("Cell #%d is a winning cell for player %c.\n\n", 1+j, board[i+1][j]);
				}
				// Check middle column cell
				if(board[i-1][j] == board[i+1][j] && i == 1 && board[i][j] != 'X' && board[i][j] != 'O'){
					printf("Cell #%d is a winning cell for player %c.\n\n", 4+j, board[i-1][j]);
				}
				// Check bottomost column cell
                                if(board[i-1][j] == board[i-2][j] && i == 2 && board[i][j] != 'X' && board[i][j] != 'O'){
                                        printf("Cell #%d is a winning cell for player %c.\n\n", 7+j, board[i-1][j]);
                                }
				// Check top left cell
				if(board[i+1][j+1] == board[i+2][j+2] && i == 0 && j == 0 && board[i][j] != 'X' && board[i][j] != 'O'){
                                        printf("Cell #1 is a winning cell for player %c.\n\n", board[i+1][j+1]);
                                }
                                // Check bottom left cell
                                if(board[i-1][j+1] == board[i-2][j+2] && i == 2 && j == 0 && board[i][j] != 'X' && board[i][j] != 'O'){
                                        printf("Cell #7 is a winning cell for player %c.\n\n", board[i-1][j+1]);
                                }
				// Check top right cell
                                if(board[i+1][j-1] == board[i+2][j-2] && i == 0 && j == 2 && board[i][j] != 'X' && board[i][j] != 'O'){
                                        printf("Cell #3 is a winning cell for player %c.\n\n", board[i+1][j-1]);
                                }
                                // Check bottom right cell
                                if(board[i-1][j-1] == board[i-2][j-2] && i == 2 && j == 2 && board[i][j] != 'X' && board[i][j] != 'O'){
                                        printf("Cell #9 is a winning cell for player %c.\n\n", board[i-1][j-1]);
                                }
                                // Check centre cell for "\" diagonal
                                if(board[i-1][j-1] == board[i+1][j+1] && i == 1 && j == 1 &&  board[i][j] != 'X' && board[i][j] != 'O'){
                                        printf("Cell #5 is a winning cell for player %c.\n\n", board[i-1][j-1]);
                                }
                                // Check centre cell for "/" diagonal
                                if(board[i+1][j-1] == board[i-1][j+1] && i == 1 && j == 1 && board[i][j] != 'X' && board[i][j] != 'O'){
                                        printf("Cell #5 is a winning cell for player %c.\n\n", board[i+1][j-1]);
                                }
			}
		}
	}
}

// Who is the winner (Q6 Answer)
char whoIsTheWinner(int m, int n, char board[][n]){
	// Flag variables for winners.
	char rowWinner;
	char colWinner;
	char diagonalWinner;
	// Assign each variable to respective flag function.
	rowWinner = rowWin(m, n, board);
	colWinner = colWin(m, n, board);
	diagonalWinner = diagonalWin(m, n, board);

	// If a winner was found, return the winner.
	if(rowWinner != 'F'){
		return rowWinner;
	}
	else if(colWinner != 'F'){
		return colWinner;
	}
	else if(diagonalWinner != 'F'){
		return diagonalWinner;
	}
	else{
		return 'D';
	}
}

// Helper function to Q6 - checks the rows for a winner recursively
char rowWin(int m, int n, char board[][n]){
	// Check if there is a row of the same 3 characters
	if(board[m-1][0] == board[m-1][1] && board[m-1][1] == board [m-1][2]){
		return board [m-1][0];
	}
	// Move to the next row by recalling the function
	else if(m > 0){
		return rowWin(m-1, n, board);
	}
	// Return F to signify no winners were found in the rows.
	else{
		return 'F';
	}
}

// Helper function to Q6 - checks the columns for a winner recursively.
char colWin(int m, int n, char board[][n]){
	// Check if there is a column of the same 3 characters.
	if(board[0][m-1] == board[1][m-1] && board[1][m-1] == board[2][m-1]){
		return board[0][m-1];
	}
        // Move to the next column by recalling the function (without changing n and the dimensions of the array)
        else if(m > 0){
                return colWin(m-1, n, board);
        }
	// Return F to signify no winners found in the columns.
        else{
		return 'F';
	}
}

// Helper function to Q6 - checks diagonals for a winner.
char diagonalWin(int m, int n, char board[][n]){
	// Check if a \ diagonal of the same 3 characters exists.
	if(board[m-3][n-3] == board[m-2][n-2] &&  board[m-2][n-2] == board[m-1][n-1]){
		return board[m-3][n-3];
	}
	// Check if a / diagonal of the same 3 characters exists.
	else if(board[m-1][n-3] == board[m-2][n-2] &&  board[m-2][n-2] == board[m-3][n-1]){
		return board[m-1][n-3];
	}
	// Return F to signify no winners found in the diagonals.
	else{
		return 'F';
	}
}
