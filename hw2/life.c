/* Game of Life
*/

#include <stdlib.h>
#include "twoD.h"
#include "life.h"

/** Main function.
 * @param argc Number of words on the command line.
 * @param argv Array of pointers to character strings containing the
 *    words on the command line.
 * @return 0 if success, 1 if invalid command line or unable to open file.
 *
 */
int main(int argc, char **argv)
{
	printf("Game of Life\n\n");

	char *inputFileName;	// Name of file containing initial grid
	int rows; 				// Number of rows in the grid
	int columns; 			// Number of columns in the grid
	int genlimit; 			// Number of generations to produce
	int doPrint=0; 			// 1 if printing after each generation, 0 if not
	int doPause=0; 			// 1 if pausing after each generation, 0 if not
	int generations=0; 		// generation count
	int exitCondition=0; 	/*
	 	 	 	 	 	 	 * Used to flag the program to terminate if it reaches
	 	 	 	 	 	 	 * steady state conditions
	 	 	 	 	 	 	 */
	char **currentBoard; 	// A 2D array to hold the pattern
	char **bufferedBoard;	/*
	 	 	 	 	 	 	 * A 2D Array to hold the next generation board
	 	 	 	 	 	 	 * being formed
	 	 	 	 	 	 	 */
	char **pastBoard; 		/*
							 * A 2D Array to hold the board from two generations
							 * ago, for loop checking
							 */


	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("  ./life rows columns generations inputFile [print] [pause]\n");
		return EXIT_FAILURE;
	}


	// Save the command-line arguments.
	rows = atoi(argv[1]); // Convert from character string to integer.
	columns = atoi(argv[2]);
	genlimit = atoi(argv[3]);
	inputFileName = argv[4];
	if(argc >5) //check if there are extra arguments
	{
		if (*argv[5]=='y')//check if the 1st extra argument sets doPrint true
		{
			doPrint=1;
		}

		//check if there is a second extra argument setting doPause to true
		if(argc == 7 && *argv[6]=='y')
		{
			doPause=1;
		}
	}


	/* Allocate arrays to hold past, present, and future grids
	*/
	currentBoard = readBoard(inputFileName, rows, columns);
	bufferedBoard = make2Dchar(rows, columns);
	pastBoard = make2Dchar(rows, columns);

	//Print the initial unshifted state
	printf("\n\n ---Initial Board---\n");
	printCharArray(currentBoard, rows, columns);

	//Perform centering operation, and print the result
	printf("\n\n ---Centered board---\n");
	currentBoard = centerPattern(currentBoard, rows, columns);
	printCharArray(currentBoard, rows, columns);

	while(generations<genlimit && exitCondition==0)
	{
		/*
		 * At the start of this loop, generations is equal to the generation
		 * to be printed. exitCondition will always be zero, and will break
		 * out of the loop if a steady state condition is detected.
		 * currentBoard will store the state of the previous generation's board.
		 * pastBoard stores the board from one generation ago.
		 */

		//Prints based on user prompt settings
		if(doPause==1)
		{
			printf("\n\nGenerations executed: %d. "
					"Press enter to continue\n", generations);
			getchar();
		}
		else if(doPrint==1)
		{
			printf("\n\nGenerations executed: %d.", generations);
		}

		//Increment the boards and the generation counter, print if set
		exitCondition = playOneGen(currentBoard, bufferedBoard,
				pastBoard, rows, columns);
		generations++;
		if(doPrint==1)
		{
			printf("\n\n ---New board---\n");
			printCharArray(currentBoard, rows, columns);

		}

		//Check if playOneGen flagged an exit condition
		if(exitCondition == 1)
		{
			printf("\n\nSteady state achieved at generation %d. "
					"Program complete. Terminating\n", generations);
		}
		else if (exitCondition == 2)
		{
			printf("\n\nTwo generation oscillation achieved at generation %d. "
					"Program complete. Terminating\n", generations);
		}


	}

	//Last print for last generation
	if (doPrint==0)
	{
		printf("\n\n ---New board---\n");
		printCharArray(currentBoard, rows, columns);
	}

	//Terminate program
	printf("\n\nGenerations executed: %d. Program complete. "
			"Terminating\n", generations);
	return EXIT_SUCCESS;
}



/** Play one generation of life
 *  @param currentArray The array storing the current board state
 *  @param newArray The array used to build the next generation's state
 *  @param pastArray The array used to store the previous state for checking
 *  for steady state conditions
 *  @return Returns a flag of 1 if the result is the same as the previous
 *  generation, and 2 if the result is a two generation oscillation. Returns
 *  0 otherwise.
 */
int playOneGen(char** currentArray, char** newArray, char** pastArray,
		int rows, int columns)
{
	//Declare variables. i and j are loop incrementors
	int i;
	int j;

	for (i=0; i<rows; i++)
	{
		/*
		 * At the start of this loop, i is the row being evaluated
		 */
		for (j=0; j<columns; j++)
		{
			/*
			 * At the start of this loop, j is the column being evaluated
			 */
			if (currentArray[i][j]=='x')
			{
				evaluateOccupied(currentArray, newArray, i, j, rows, columns);
			}
			else
			{
				evaluateUnoccupied(currentArray, newArray, i, j, rows, columns);
			}
		}
	}


	//Check if a steady state condition is achieved to drive return value
	if (checkEquality(currentArray, newArray, rows, columns)==1)
	{
		return 1;
	}
	else if (checkEquality(pastArray, newArray, rows, columns)==1)
	{
		return 2;
	}

	//If no steady state is achieved, update arrays
	for(i=0; i<rows; i++)
	{
		for(j=0; j<columns; j++)
		{
			pastArray[i][j]=currentArray[i][j];
			currentArray[i][j]=newArray[i][j];
		}
	}


	return 0;

}

/**
 * Checks if an occupied cell should be converted to unoccupied in the next
 * generation, and changes its value in newArray
 * @param oldArray The array to evaluate for life and death
 * @param newArray The array to write results to
 * @param y The y index of the cell being evaluated
 * @param x The x index of the cell being evaluated
 * @param rows The number of rows in the array
 * @param columns The number of columns in the array
 */
void evaluateOccupied(char** oldArray, char** newArray, int y, int x, int rows, int columns)
{
	/*
	 * declare variables. i and j are loop incrementors. count counts the
	 * number of adjacent occupied cells
	 */
	int i;
	int j;
	int count;
	//Starts at -1 because loop will pass through cell being executed, which is always occupied
	count=-1;
	for (i=-1; i<2; i++)
	{
		/*
		 * At the start of this loop, i represents the shift relative to the
		 * cell being evaluated
		 */
		for (j=-1; j<2; j++)
		{
			/*
			 * At the start of this loop, j represents the shift relative to the
			 * cell being evaluated
			 */


			/*
			 * Makes use of short circuit evaluation
			 * Does not make call to array if index is out of bounds, assume
			 * unoccupied
			 * If the index is in bounds, checks if neighbor is occupied
			 */
			if ((!(y+i<0 || x+j<0 || y+i>rows-1 || x+j>columns-1))&&
					oldArray[i+y][j+x]=='x')
			{
				count++;
			}

		}
	}

	//Set values
	if (count<2 || count>3)
	{
		newArray[y][x]=' ';
	}
	else
	{
		newArray[y][x]='x';
	}
}

/**
 * Checks if an unoccupied cell should be converted to occupied in the next
 * generation, and changes its value in newArray
 * @param oldArray The array to evaluate for life and death
 * @param newArray The array to write results to
 * @param y The y index of the cell being evaluated
 * @param x The x index of the cell being evaluated
 * @param rows The number of rows in the array
 * @param columns The number of columns in the array
 */
void evaluateUnoccupied(char** oldArray, char** newArray, int y, int x,
		int rows, int columns)
{
	/*
	 * declare variables. i and j are loop incrementors. count counts the
	 * number of adjacent occupied cells
	 */
	int i;
	int j;
	int count;

	count=0;
	for (i=-1; i<2; i++)
	{
		/*
		 * At the start of this loop, i represents the shift relative to the
		 * cell being evaluated
		 */
		for (j=-1; j<2; j++)
		{
			/*
			 * At the start of this loop, j represents the shift relative to the
			 * cell being evaluated
			 */

			/*
			 * Makes use of short circuit evaluation
			 * Does not make call to array if index is out of bounds, assume
			 * unoccupied
			 * If the index is in bounds, checks if neighbor is occupied
			 */
			if ((!(y+i<0 || x+j<0 || y+i>rows-1 || x+j>columns-1))&&
					oldArray[i+y][j+x]=='x')
			{
				count++;
			}
		}
	}

	//Set values
	if (count==3)
	{
		newArray[y][x]='x';
	}
	else
	{
		newArray[y][x]=' ';
	}
}

/** Read initial board from file. Ends the program if the file is larger
 *  than the board specified by the user.
 *  @param input File to read the initial board state from
 *  @param rows Number of rows specified by the user. If
 *  the input file has more rows than the board, the file will
 *  be rejected.
 *  @param columns Number of columns specified by the user.
 *  If the input file has more columns than the board, the
 *  file will be rejected.
 *  @return Returns a 2d array containing the board
 */
char** readBoard(char *inputFileName, int rows, int columns)
{
	/*declare variables. currentRow represents the row being read by fgets
	 *at the moment. i and j are loop incrementors. FILE is the file being read.
	*/
	int currentRow;
	int i;
	int j;
	FILE *input;
	char **bufferArray;

	//Initialize the array
	bufferArray = make2Dchar(rows, columns);

	//Read file, verify that operation completed correctly
	input = fopen(inputFileName, "r");
	if (!input)
	{
		printf("Unable to open input file: %s\n", inputFileName);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("file successfully read\n");
	}

	//Read each line into a string array
	char str[columns+2];
	currentRow=0;
	while (fgets(str, sizeof str, input))
	{
		/*
		 * At the start of each loop execution, currentRow represents the row
		 * being read
		 * bufferArray contains an array representation of every line of the
		 * file above
		 */
		if (currentRow>=rows)
		{
			printf("ERROR: File has more rows than specified board. Terminating\n");
			exit(EXIT_FAILURE);
		}
		if (strchr(str, '\n')==NULL)
		{
			printf("ERROR: File has more columns than specified board. Terminating\n");
			exit(EXIT_FAILURE);
		}

		//Write line to output, and convert to 'x' and ' ' format
		for (i=0; i<(int)(strchr(str, '\n')-str); i++)
		{
			/*
			 * At the start of each loop execution, i is the character to
			 * convert and write
			 */
			if (str[i]=='o')
			{
				bufferArray[currentRow][i] = ' ';
			}
			else
			{
				bufferArray[currentRow][i] = str[i];
			}

		}

		//Fill excess space to right with ' ' characters
		for (i=(int)(strchr(str, '\n')-str); i<columns; i++)
		{
			/*
			 * At the start of the loop, i represents the last specified
			 * character in the file
			 * At the start of each loop execution, i is the character to
			 * convert and write. It starts where the last loop left off
			 */
			bufferArray[currentRow][i] = ' ';
		}
		//Increment row
		currentRow++;
	}

	//Fill excess space below with ' ' characters
	for (i=currentRow; i<rows; i++)
	{
		/*
		 * Before the loop begins, i is set to the first empty row in the array
		 * At the start of the loop, i represents the row to write to.
		 */
		for(j=0; j<columns; j++)
		{
			/*
			 * At the start of the loop, j represents the column to write to
			 *
			 */
			bufferArray[i][j] = ' ';
		}
	}

	return bufferArray;
}
