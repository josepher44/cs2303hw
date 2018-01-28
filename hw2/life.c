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
int main(int argc, char **argv) {
	printf("Game of Life\n");

	char *inputFileName; // Name of file containing initial grid
	FILE *input; // Stream descriptor for file containing initial grid
	int rows; // Number of rows in the grid
	int columns; // Number of columns in the grid
	int genlimit; // Number of generations to produce
	int doPrint=0; // 1 if user wants to print each generation, 0 if not
	int doPause=0; // 1 if user wants to pause after each generation, 0 if not
	int i=0; // loop incrementor
	int generations=0; // generation count;
	char **currentBoard; // A 2D array to hold the pattern
	char **bufferedBoard; // A 2D Array to hold the next generation board being formed
	char **pastBoard; // A 2D Array to hold the board from two generations ago, for loop checking

	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("  ./life rows columns generations inputFile [print] [pause]\n");
		return EXIT_FAILURE;
	}

	/* Save the command-line arguments.
	   Also need to check if print and/or pause arguments were entered,
	   and if so, what they were.
	   A switch statement might be handy here.
	*/
	rows = atoi(argv[1]); // Convert from character string to integer.
	columns = atoi(argv[2]);
	genlimit = atoi(argv[3]);
	inputFileName = argv[4];
	if(argc >5) //check if there are extra arguments
	{
		if (*argv[5]=='y')//check if the 1st extra argument sets doPrint true
		{
			doPrint=1; //first argument
		}

		//check if there is a second extra argument setting doPause to true
		if(argc == 7 && *argv[6]=='y')
			{
				doPause=1;
				printf("doing pause!\n");
			}
	}
	else
	{
		printf("Not doing either!\n");
	}


	/* Allocate array to hold overall grid
	*/
	currentBoard = readBoard(inputFileName, rows, columns);
	bufferedBoard = make2Dchar(rows, columns);
	pastBoard = make2Dchar(rows, columns);


	printf("\n\n ---Initial Board---\n");
	printCharArray(currentBoard, rows, columns);

	printf("\n\n ---Centering board---\n");
	currentBoard = centerPattern(currentBoard, rows, columns);
	printCharArray(currentBoard, rows, columns);

	while(generations<genlimit)
	{
		playOneGen(currentBoard, bufferedBoard, pastBoard, rows, columns);
		generations++;
		if(doPrint==1)
		{
			printf("\n\n ---New board---\n");
			printCharArray(currentBoard, rows, columns);
			if(doPause==1)
			{
				printf("\n\nGenerations executed: %d. Press any key to continue\n", generations);
				getchar();
			}
			else
			{
				printf("\n\nGenerations executed: %d.", generations);
			}
		}

	}
	if (doPrint==0)
	{
		printf("\n\n ---New board---\n");
		printCharArray(currentBoard, rows, columns);
		printf("\n\nGenerations executed: %d.", generations);
	}
	printf("\n\nProgram complete. Terminating", generations);







	/*Once opened, you can read from the file one character at a time with fgetc().
	 * You can read one line at a time using fgets().
	 * You can read from standard input (the keyboard) with getchar().
	*/

	return EXIT_SUCCESS;
}

/** Read initial board from file
 *  @param input File to read the initial board state from
 *  @param columns Number of columns specified by the user.
 *  If the input file has more columns than the board, the
 *  file will be rejected.
 *  @param rows Number of rows specified by the user. If
 *  the input file has more rows than the board, the file will
 *  be rejected.
 */

void playOneGen(char** currentArray, char** newArray, char** pastArray, int rows, int columns)
{
	int i;
	int j;

	for (i=0; i<rows; i++)
	{
		for (j=0; j<columns; j++)
		{
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
	for(i=0; i<rows; i++)
	{
		for(j=0; j<columns; j++)
		{
			pastArray[i][j]=currentArray[i][j];
			currentArray[i][j]=newArray[i][j];
		}
	}
}

void evaluateOccupied(char** oldArray, char** newArray, int y, int x, int rows, int columns)
{
	int i;
	int j;
	int count;
	//Starts at -1 because loop will pass through cell being executed, which is always occupied
	count=-1;
	for (i=-1; i<2; i++)
	{
		for (j=-1; j<2; j++)
		{
			/*
			 * Makes use of short circuit evaluation
			 * Does not make call to array if index is out of bounds, assume unoccupied
			 * If the index is in bounds, checks if neighbor is occupied
			 */
			if ((!(y+i<0 || x+j<0 || y+i>rows-1 || x+j>columns-1))&&oldArray[i+y][j+x]=='x')
			{
				count++;
			}

		}
	}

	if (count<2 || count>3)
	{
		newArray[y][x]=' ';
	}
	else
	{
		newArray[y][x]='x';
	}
}

void evaluateUnoccupied(char** oldArray, char** newArray, int y, int x, int rows, int columns)
{
	int i;
	int j;
	int count;
	//printf("evaluating cell %d, %d\n", x, y);

	count=0;
	for (i=-1; i<2; i++)
	{
		for (j=-1; j<2; j++)
		{
			/*
			 * Makes use of short circuit evaluation
			 * Does not make call to array if index is out of bounds, assume unoccupied
			 * If the index is in bounds, checks if neighbor is occupied
			 */
			//printf("offsets of x: %d, y: %d\n", j, i);
			if ((!(y+i<0 || x+j<0 || y+i>rows-1 || x+j>columns-1))&&oldArray[i+y][j+x]=='x')
			{
				count++;
			}
		}
	}

	if (count==3)
	{
		newArray[y][x]='x';
	}
	else
	{
		newArray[y][x]=' ';
	}
}

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

	bufferArray = make2Dchar(rows, columns);

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
	char str[columns+2];
	currentRow=0;
	while (fgets(str, sizeof str, input))
	{
		/*
		 * At the start of each loop execution, currentRows represents the row being read
		 * bufferArray contains an array representation of every line of the file above
		 * currentRows.
		 */
		if (currentRow>=rows)
		{
			printf("ERROR: File has more rows than specified board. Terminating\n");
			exit(EXIT_FAILURE);
		}
		printf("%s", str);
		if (strchr(str, '\n')==NULL)
		{
			printf("ERROR: File has more columns than specified board. Terminating\n");
			exit(EXIT_FAILURE);
		}
		//Write line to output
		for (i=0; i<(int)(strchr(str, '\n')-str); i++)
		{
			if (str[i]=='o')
			{
				bufferArray[currentRow][i] = ' ';
			}
			else
			{
				bufferArray[currentRow][i] = str[i];
			}

		}
		for (i=(int)(strchr(str, '\n')-str); i<columns; i++)
		{
			bufferArray[currentRow][i] = ' ';
		}
		currentRow++;
	}
	for (i=currentRow; i<rows; i++)
	{
		for(j=0; j<columns; j++)
		{

			bufferArray[i][j] = ' ';
		}
	}
	return bufferArray;
}
