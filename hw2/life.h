/**
 * twoD.h
 *
 * @author: Joe Gallagher
 */

#include <stdio.h>

#ifndef LIFE_H_
#define LIFE_H_

// Function prototypes:
char** readBoard(char *inputFileName, int rows,  int columns);
void playOneGen(char** oldArray, char** newArray, char** pastArray, int rows, int columns);
void evaluateOccupied(char** oldArray, char** newArray, int y, int x, int rows, int columns);
void evaluateUnoccupied(char** oldArray, char** newArray, int y, int x, int rows, int columns);


#endif /* LIFE_H_ */
