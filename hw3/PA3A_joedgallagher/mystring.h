/** mystring.h
 * @author Mike Ciaraldi
 * My own versions of some of the C-style string functions
*/

#include <stdio.h>

// Function prototype(s):
char* mystrdup1(const char* src);
char* mystrdup2(const char* src);
size_t mystrlen1(const char* src);
size_t mystrlen2(const char* src);
char *mystrcpy(char *dest, const char *src);
char *mystrcat(char *dest, const char *src);
