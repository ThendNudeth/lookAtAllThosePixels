#include "../Dependencies/dependencies.h"
#include "matrix.h"

Matrix* newMatrix(int nrows, int ncols, double vs[nrows][ncols]) {
    printf("CREATING NEW MATRIX:\n");
    Matrix* m = malloc(sizeof(Matrix));
    m->nrows = nrows;
    m->ncols = ncols;

    m->vs = malloc(ncols * sizeof(Vector*));
    for (size_t i = 0; i < ncols; i++)
    {
        double vi[nrows];
        for (size_t j = 0; j < nrows; j++)
        {
            vi[j] = vs[j][i];
        }
        
        m->vs[i] = newVector(vi, nrows);
        printf("NEW MATRIX COLUMN:\n");
        printVector(m->vs[i]);
    }
    
    
    printf("\nMATRIX COLUMNS:\n");
    for (size_t i = 0; i < m->ncols; i++)
    {
        printVector(m->vs[i]);
    }
    
    return m;
}

char* matrixToString(Matrix* m) {
    
    char* m_out = malloc((m->ncols * 3 * 64 + 2) * m->nrows * 3 + 2);
    m_out[0] = '[';

    for (size_t i = 1; i < m->nrows; i++)
    {
        m_out[i] = '[';
        // for (size_t j = 0; j < m->ncols; j++)
        // {
        //     char buffer[64];
        //     int ret = snprintf(buffer, sizeof buffer, "%f", m->vs[i][j]);
        //     strcat(buffer, ", ");
        //     strcat(m_out, buffer);
        // }

        // char buffer[64];
        // printf("%f\n", m->vs[i][0]);
        // int ret = snprintf(buffer, sizeof buffer, "%f", m->vs[i][m->ncols-1]);
        // strcat(buffer, "]");
        // strcat(m_out, buffer);

        
    }
    
    

    // char buffer[64];
    // int ret = snprintf(buffer, sizeof buffer, "%f", v->vs[v->dim-1]);
    // strcat(buffer, "]");
    // strcat(m_out, buffer);
    
    return m_out;
}

void destroyMatrix(Matrix* m) {
    for (size_t i = 0; i < m->ncols; i++)
    {
        destroyVector(m->vs[i]);
    }
    free(m->vs);
    free(m);
    
}