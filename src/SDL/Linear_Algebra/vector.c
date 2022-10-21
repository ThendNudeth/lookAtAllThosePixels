#include "../Dependencies/dependencies.h"
#include "vector.h"


// CONSTRUCTORS
// ==================================================================
Vector* newVector(double vs[], int dim) {
    printf("CREATING NEW VECTOR:\n");
    Vector* v = malloc(sizeof(Vector));
    v->vs = malloc(dim * sizeof(double));
    v->dim = dim;
    for (size_t i = 0; i < dim; i++)
    {
        v->vs[i] = vs[i];
    }

    printf("NEW VECTOR CREATED:\n");
    printVector(v);
    return v;
}

Vector* newZeroVector(int dim) {
    printf("CREATING NEW VECTOR:\n");
    Vector* v = malloc(sizeof(Vector));
    v->vs = malloc(dim * sizeof(double));
    v->dim = dim;

    printf("NEW VECTOR CREATED:\n");
    printVector(v);
    return v;
}

Vector* copyVector(Vector* v) {
    printf("COPYING VECTOR:\n");
    Vector* copy = malloc(sizeof(Vector));
    copy->vs = malloc(v->dim * sizeof(double));
    copy->dim = v->dim;
    for (size_t i = 0; i < v->dim; i++)
    {
        copy->vs[i] = v->vs[i];
    }

    printf("NEW VECTOR COPIED:\n");
    printVector(copy);
    return copy;
}
// ==================================================================


// DESTRUCTOR
// ==================================================================
void destroyVector(Vector* v) {
    free(v->vs);
    free(v);
}
// ==================================================================


// SINGLE VECTOR OPERATIONS
// ==================================================================
double sum(Vector* v) {
    double s = 0.0;
    for (size_t i = 0; i < v->dim; i++)
    {
        s += v->vs[i];
    }
    return s;
}
double magnitude(Vector* v) {
    double m = 0.0;
    for (size_t i = 0; i < v->dim; i++)
    {
        m += (v->vs[i]*v->vs[i]);
    }
    
    m = sqrt(m);
    return m;
    
}

Vector* normalise(Vector* v) {
    double m = magnitude(v);

    if (m==0.0)
    {
        return copyVector(v);
    }
    
    Vector* vn = newZeroVector(v->dim);
    for (size_t i = 0; i < v->dim; i++)
    {
        vn->vs[i] = v->vs[i]/m;
    }

    return vn;
}

Vector* scaleVector(double scale, Vector* v) {
    Vector* scaled = newZeroVector(v->dim);
    for (size_t i = 0; i < v->dim; i++)
    {
        scaled->vs[i] = scale * v->vs[i];
    }
    return scaled;
}
// ==================================================================


// DOUBLE VECTOR OPERATIONS
// ==================================================================
Vector* addVectors(Vector* v1, Vector* v2) {
    Vector* v = newZeroVector(v1->dim);
    for (size_t i = 0; i < v1->dim; i++)
    {
        v->vs[i] = v1->vs[i] + v2->vs[i];
    }
    return v;
}

Vector* subtractVectors(Vector* v1, Vector* v2) {
    Vector* v = newZeroVector(v1->dim);
    for (size_t i = 0; i < v1->dim; i++)
    {
        v->vs[i] = v1->vs[i] - v2->vs[i];
    }
    return v;
}

// Vector* normalise(Vector* v) {
//     double m = magnitude(v);

//     if (m==0.0)
//     {
//         return copyVector(v);
//     }
    
//     Vector* vn = newZeroVector(v->dim);
//     for (size_t i = 0; i < v->dim; i++)
//     {
//         vn->vs[i] = v->vs[i]/m;
//     }

//     return vn;
// }
// ==================================================================


// TOSTRING
// ==================================================================
char* vectorToString(Vector* v) {
    
    char* v_out = malloc(v->dim * 3 * 64 + 2);
    v_out[0] = '[';

    for (size_t i = 0; i < v->dim-1; i++)
    {
        char buffer[64];
        int ret = snprintf(buffer, sizeof buffer, "%f", v->vs[i]);
        strcat(buffer, ", ");
        strcat(v_out, buffer);
    }

    char buffer[64];
    int ret = snprintf(buffer, sizeof buffer, "%f", v->vs[v->dim-1]);
    strcat(buffer, "]");
    strcat(v_out, buffer);
    
    return v_out;
}

void printVector(Vector* v) {
    char* vStr = vectorToString(v);
    printf("V: %s\n", vStr);
    free(vStr);
}
// ==================================================================