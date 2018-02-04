#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"

/*
 * File contains functions for directly manipulating and creating 2d Arrays
 */

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
	}

	// Now allocate array for each row
	for (i = 0; i < rows; i++) {
		// i is the row we are about to allocate
		a[i] = malloc(columns * sizeof (int));
		if (!a[i]) {
			return (int **) NULL; // Unable to allocate
		}
	}
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

/** Prints a 2d array of characters to the console
 *
 * @param array The array to print
 * @param columns Number of columns to divide the array into
 * @param rows Number of rows to divide the array into
 *
 * @author Joe Gallagher
 */
void printCharArray(char** array, int rows, int columns)
{
	//Declare variables. i and j are loop incrementors
	int i;
	int j;
	for (i=0; i<rows; i++)
	{
		for(j=0; j<columns; j++)
		{
			printf("%c", array[i][j]);
		}
		printf("\n");
	}
}

struct coordinate
{
	int x;
	int y;
};


/** Centers an array relative to the base grid
 *
 * @param array The array to center
 * @param rows Number of rows the base grid has
 * @param columns Number of columns the base grid has
 * @return The centered array
 */
char** centerPattern(char** array, int rows, int columns)
{
	//Declare variables. xshift and yshift represent the amounts to shift the
	//pattern. i and j are loop increments
	int xshift;
	int yshift;
	int i;
	int j;

	struct coordinate centroid;

	centroid = findCentroid(array, rows, columns);


	xshift = (columns-centroid.x)/2;
	yshift = (rows-centroid.y)/2;
	if(xshift>0)
	{
		for (j=0; j<rows; j++)
		{
			//At the start of this loop, j represents the row to shift
			for(i=columns-xshift-1; i>=0; i--)
			{
				//at the start of this loop, i represents the column to shift
				array[j][i+xshift]=array[j][i];
			}
			for(i=0; i<xshift; i++)
			{
				//At the start of this loop, i represents the cell to write
				//blank
				array[j][i]=' ';
			}
		}
	}
	else
	{
		for (j=0; j<rows; j++)
		{
			//At the start of this loop, j represents the row to shift
			for(i=xshift; i<rows; i++)
			{
				//at the start of this loop, i represents the column to shift
				array[j][i+xshift]=array[j][i];
			}
			for(i=rows-1; i>rows-1+xshift; i--)
			{
				//At the start of this loop, i represents the cell to write
				//blank
				array[j][i]=' ';
			}
		}
	}

	if(yshift>0)
	{
		for (j=0; j<columns; j++)
		{
			//At the start of this loop, j represents the column to shift
			for(i=rows-yshift-1; i>=0; i--)
			{
				//at the start of this loop, i represents the row to shift
				array[i+yshift][j]=array[i][j];
			}
			for(i=0; i<yshift; i++)
			{
				//At the start of this loop, i represents the cell to write
				//blank
				array[i][j]=' ';
			}
		}
	}
	else
	{
		for (j=0; j<columns; j++)
		{
			//At the start of this loop, j represents the column to shift
			for(i=yshift; i<columns; i++)
			{
				//at the start of this loop, i represents the row to shift
				array[i+yshift][j]=array[i][j];
			}
			for(i=columns-1; i>columns-1+yshift; i--)
			{
				//At the start of this loop, i represents the cell to write
				//blank
				array[i][j]=' ';
			}
		}
	}

	return array;

}


/** Finds the geometric center of an array
 *
 * @param array The array to locate the center of
 * @param rows Number of rows the array has
 * @param columns Number of columns the base grid has
 * @return The x and y coordinate of the centroid
 */
struct coordinate findCentroid(char** array, int rows, int columns)
{
	//Declare variables. i and j are loop incrementors
	int i;
	int j;
	int min_x;
	int max_x;
	int min_y;
	int max_y;

	min_x=-1;

	for(i=0; i<rows; i++)
	{
		//At the start of this loop, i is the row to be checked
		for(j=0; j<columns; j++)
		{
			//At the start of this loop, j is the column to be checked
			if(array[i][j]=='x')
			{
				//For first value, set minimum and maximum no matter what
				if (min_x==-1)
				{
					min_y=i;
					max_y=i;
					min_x=j;
					max_x=j;
				}

				if(i<min_y)
				{
					min_y=i;
				}
				else if(i>max_y)
				{
					max_y=i;
				}

				if(j<min_x)
				{
					min_x=j;
				}
				else if(j>max_x)
				{
					max_x=j;
				}
			}
		}
	}
	struct coordinate output = {(max_x+min_x), (max_y+min_y)};
	return output;
}

/**
 * Checks the equality of two 2d arrays of known dimensions by comparing all
 * their elements
 * @param array1 The first array to compare
 * @param array2 The second array to compare
 * @param rows The row count of both arrays
 * @param columns The column count of both arrays
 * @return 1 if the arrays are equal, 0 if they are not
 */
int checkEquality(char** array1, char** array2, int rows, int columns)
{
	//Declare variables. i and j are loop incrementors
	int i;
	int j;

	for(i=0; i<rows; i++)
	{
		/*
		 * At the start of this loop, i represents the row being checked
		 */
		for(j=0; j<columns; j++)
		{
			/*
			 * At the start of this loop, i and j represent the y and x
			 * coordinates to be evaluated
			 */
			if(array1[i][j]!=array2[i][j])
			{
				//If any elements do not match, immediately return 0
				return 0;
			}
		}
	}
	//Only reached if all elements are equal
	return 1;
}
