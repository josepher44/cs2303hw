/* Game of Life
*/

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"

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
	int gens; // Number of generations to produce
	int doPrint=0; // 1 if user wants to print each generation, 0 if not
	int doPause=0; // 1 if user wants to pause after each generation, 0 if not
	int i=0; // loop incrementor
	char **gridA; // A 2D array to hold the pattern

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
	gens = atoi(argv[3]);
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
	gridA = make2Dchar(rows, columns);

	for(i=0; i<rows; i++)
	{
		gridA[0][i]=(char)i+65;
	}
	for(i=0; i<rows; i++)
	{
		printf("%c", gridA[0][i]);
	}


	/* Eventually, need to try to open the input file.
	*/
	input = fopen(inputFileName, "r");
	if (!input) {
		printf("Unable to open input file: %s\n", inputFileName);
		return EXIT_FAILURE;
	}
	else
	{
		printf("file successfully read\n");
	}

	/*Once opened, you can read from the file one character at a time with fgetc().
	 * You can read one line at a time using fgets().
	 * You can read from standard input (the keyboard) with getchar().
	*/

	return EXIT_SUCCESS;
}
