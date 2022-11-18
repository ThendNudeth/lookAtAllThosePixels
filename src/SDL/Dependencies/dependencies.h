#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

void printFloat(double f);
void printString(char* s);
void printInt(int i);
void printUint(size_t i);

char* vectorToString(gsl_vector* v);
void printVector(gsl_vector* v);
char* matrixToString(gsl_matrix* m);
void printMatrix(gsl_matrix* m);