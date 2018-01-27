#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"

/** Make a 2D array of integers
 *
 * @param rows Number of rows
 * @param columns Number of columns
 * @return Pointer to the array of pointers to the rows.
 * 	  or null pointer if unable to allocate memory.
 * 	  Note: Will not free partially-allocated memory.
 *
 * @author Mike Ciaraldi
 */

int** make2Dint(int rows, int columns) {

	int **a; // Array of pointers to rows
	unsigned int i; // Loop counter

	// First allocate the array of pointers to rows
	a = (int **) malloc(rows * sizeof(int *));
	if (!a)
	{ // Unable to allocate the array
		return (int **) NULL;
		printf("first null");
	}

	// Now allocate array for each row
	for (i = 0; i < rows; i++) {
		// i is the row we are about to allocate
		a[i] = malloc(columns * sizeof (int));
		if (!a[i]) {
			return (int **) NULL; // Unable to allocate
			printf("second null");
		}
	}
	printf("not null");
	int test = (int)sizeof(a)/sizeof(a[0][0]);
	printf("%d\n", test);
	return a;
}

/** Make a 2D array of characters
 *
 * @param rows Number of rows
 * @param columns Number of columns
 * @return Pointer to the array of pointers to the rows.
 * 	  or null pointer if unable to allocate memory.
 * 	  Note: Will not free partially-allocated memory.
 *
 * @author Joe Gallagher
 */
char** make2Dchar(int rows, int columns) {

	char **a; // Array of pointers to rows
	unsigned int i; // Loop counter

	// First allocate the array of pointers to rows
	a = (char**) malloc(rows * sizeof(char *));
	if (!a)
	{ //Unable to allocate the array
		return (char **) NULL;
	}

	// Now allocate array for each row
	for (i = 0; i < rows; i++) {
		// i is the row we are about to allocate
		a[i] = malloc(columns * sizeof (char));
		if (!a[i]) {
			return (char **) NULL; // Unable to allocate
		}
	}
	return a;
}
