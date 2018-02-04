/**
 * twoD.h
 *
 * @author: Mike Ciaraldi
 */

#ifndef TWOD_H_
#define TWOD_H_

// Function prototypes:
int** make2Dint(int rows, int columns);
char** make2Dchar(int rows, int columns);
void printCharArray(char** array, int rows, int columns);
struct coordinate findCentroid(char** array, int rows, int columns);
char** centerPattern(char** array, int rows, int columns);
int checkEquality(char** array1, char** array2, int rows, int columns);

#endif /* 2D_H_ */
