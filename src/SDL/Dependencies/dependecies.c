#include "dependencies.h"

void printFloat(double f) {
    printf("%f\n", f);
}

void printString(char* s) {
    printf("%s\n", s);
}

void printInt(int i) {
    printf("%d\n", i);
}

void printUint(size_t i) {
    printf("%lu\n", i);
}

char* vectorToString(gsl_vector* v) {
    
    char* v_out = malloc(v->size * 3 * 64 + 2);
    v_out[0] = '[';

    for (size_t i = 0; i < v->size-1; i++)
    {
        char buffer[64];
        int ret = snprintf(buffer, sizeof buffer, "%f", gsl_vector_get(v, i));
        strcat(buffer, ", ");
        strcat(v_out, buffer);
    }

    char buffer[64];
    int ret = snprintf(buffer, sizeof buffer, "%f", gsl_vector_get(v, v->size-1));
    strcat(buffer, "]");
    strcat(v_out, buffer);
    
    return v_out;
}

void printVector(gsl_vector* v) {
    char* vStr = vectorToString(v);
    printf("V: %s\n", vStr);
    free(vStr);
}

char* matrixToString(gsl_matrix* m) {
    

    char* m_out = malloc(m->size1 * (m->size2 * 3 * 64 + 3) + 2);
    m_out[0] = '[';
    m_out[1] = '\n';

    for (size_t i = 0; i < m->size1; i++)
    {
        strcat(m_out, "[");

        for (size_t j = 0; j < m->size2-1; j++)
        {
            char buffer[64];
            int ret = snprintf(buffer, sizeof buffer, "%f", gsl_matrix_get(m, i, j));
            strcat(buffer, ", ");
            strcat(m_out, buffer);
        }

        char buffer[64];
        int ret = snprintf(buffer, sizeof buffer, "%f", gsl_matrix_get(m, i, m->size2-1));
        strcat(buffer, "]\n");
        strcat(m_out, buffer);

    }
    
    strcat(m_out, "]\n");

    return m_out;
}

void printMatrix(gsl_matrix* m) {
    char* mStr = matrixToString(m);
    printf("M: %s\n", mStr);
    free(mStr);
}