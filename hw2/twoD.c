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

char** centerPattern(char** array, int rows, int columns)
{
	printf("started centering the pattern");
	int xshift;
	int yshift;
	int i;
	int j;

	struct coordinate centroid;

	centroid = findCentroid(array, rows, columns);
	printf("centroid x is %d, centroid y is %d", centroid.x, centroid.y);
	printf("found the centroid");

	xshift = (columns-centroid.x)/2;
	yshift = (rows-centroid.y)/2;
	printf("xshift is %d, yshift is %d\n\n\n", xshift, yshift);
	if(xshift>0)
	{
		for (j=0; j<rows; j++)
		{
			for(i=columns-xshift-1; i>=0; i--)
			{
				array[j][i+xshift]=array[j][i];
			}
			for(i=0; i<xshift; i++)
			{
				array[j][i]=' ';
			}
		}
	}
	else
	{
		for (j=0; j<rows; j++)
		{
			for(i=xshift; i<rows; i++)
			{
				array[j][i+xshift]=array[j][i];
			}
			for(i=rows-1; i>rows-1+xshift; i--)
			{
				array[j][i]=' ';
			}
		}
	}

	if(yshift>0)
	{
		for (j=0; j<columns; j++)
		{
			for(i=rows-yshift-1; i>=0; i--)
			{
				array[i+yshift][j]=array[i][j];
			}
			for(i=0; i<yshift; i++)
			{
				array[i][j]=' ';
			}
		}
	}
	else
	{
		for (j=0; j<columns; j++)
		{
			for(i=yshift; i<columns; i++)
			{
				array[i+yshift][j]=array[i][j];
			}
			for(i=columns-1; i>columns-1+yshift; i--)
			{
				array[i][j]=' ';
			}
		}
	}

	return array;

}

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
		for(j=0; j<columns; j++)
		{
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
	printf("min_x: %d\nmax_x: %d\nmin_y: %d\nmax_y: %d", min_x, max_x, min_y, max_y);
	struct coordinate output = {(max_x+min_x), (max_y+min_y)};
	return output;
	//Compute the average x and y location of a filled cell

}
