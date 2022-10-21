#include "vector.h"

typedef struct {
    int nrows;
    int ncols;
    Vector** vs; // An array of column vectors
    // double** vs;
}Matrix;

Matrix* newMatrix(int nrows, int ncols, double vs[nrows][ncols]);

Vector** rowVectors(Matrix*);
Vector** colVectors(Matrix*);

Matrix* transpose(Matrix* m);

void destroyMatrix(Matrix* m);
