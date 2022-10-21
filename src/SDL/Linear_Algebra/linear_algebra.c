#include "../Dependencies/dependencies.h"
#include "linear_algebra.h"

int main() {

    double vs1[] = {1,2,3, 798, 1678.678165854};
    double vs2[] = {1,1};

    Vector* v1 = newVector(vs1, 5);
    Vector* v2 = newVector(vs2, 2);
    Vector* v0 = newZeroVector(10);

    printVector(v1);
    printVector(v2);
    printVector(v0);

    printFloat(magnitude(v1));
    printFloat(magnitude(v2));
    printFloat(magnitude(v0));

    Vector* v1n = normalise(v1);
    Vector* v2n = normalise(v2);
    Vector* v0n = normalise(v0);

    printVector(v1n);
    printVector(v2n);
    printVector(v0n);

    printFloat(magnitude(v1n));
    printFloat(magnitude(v2n));
    printFloat(magnitude(v0n));

    destroyVector(v1);
    destroyVector(v2);
    destroyVector(v0);

    destroyVector(v1n);
    destroyVector(v2n);
    destroyVector(v0n);
    printf("awe\n");

    double vsM[3][3];
    double c=0.0;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            vsM[i][j] = c++;
        }
        
    }

    Matrix* m = newMatrix(3, 3, vsM);
    // char* mStr = matrixToString(m);
    // printf("%s\n", mStr);
    // free(mStr);
    destroyMatrix(m);

    return 0;
}