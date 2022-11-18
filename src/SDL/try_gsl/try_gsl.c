#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

/*
    Successfully compiled with:
    gcc -Wall -I/opt/homebrew/include -c try_gsl.c
    gcc -L/opt/homebrew/lib try_gsl.o -lgsl -lgslcblas -lm
*/

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

int main (void)
{
  double x = 5.0;
  double y = gsl_sf_bessel_J0 (x);
  printf ("J0(%g) = %.18e\n", x, y);

  gsl_vector* v = gsl_vector_alloc(2);

  gsl_vector_fprintf(stdout, v, "%.2f");
  printVector(v);

  gsl_vector_free(v);


  gsl_matrix* m = gsl_matrix_alloc(3, 3);

  gsl_matrix_fprintf(stdout, m, "%.2f");
  printMatrix(m);

  gsl_matrix_free(m);
  return 0;
}