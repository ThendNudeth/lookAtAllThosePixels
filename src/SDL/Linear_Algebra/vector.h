typedef struct {
    int dim;
    double* vs;
}Vector;

Vector* newZeroVector(int dim);
Vector* newVector(double vs[], int dim);
Vector* copyVector(Vector* v);

void destroyVector(Vector* v);

double sum(Vector* v);
double magnitude(Vector* v);
Vector* normalise(Vector* v);
Vector* scaleVector(double scale, Vector* v);

Vector* addVectors(Vector* v1, Vector* v2);
Vector* subtractVectors(Vector* v1, Vector* v2);
Vector* elemMult(Vector* v1, Vector* v2);
Vector* outer(Vector* v1, Vector* v2);
double inner(Vector* v1, Vector* v2);

char* vectorToString(Vector* v);
void printVector(Vector* v);