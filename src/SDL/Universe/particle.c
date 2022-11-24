#include "particle.h"

Particle* newParticle(
    double mass,
    gsl_vector* position,
    gsl_vector* velocity,
    gsl_vector* acceleration) 
    {
    Particle* p = malloc(sizeof(Particle));
    p->mass = mass;
    p->col = newRandomColour();
    p->position = position;
    p->velocity = velocity;
    p->acceleration = acceleration;

    printf("NEW PARTICLE CREATED W. INITIAL CONDITIONS:\n");
    printParticle(p);
    return p;
}

Particle* new2dParticle(double mass,
    double px,
    double py,
    double vx,
    double vy,
    double ax,
    double ay) 
    {
    gsl_vector * p = gsl_vector_alloc(2);
    gsl_vector_set (p, 0, px);
    gsl_vector_set (p, 1, py);

    gsl_vector * v = gsl_vector_alloc(2);
    gsl_vector_set (v, 0, vx);
    gsl_vector_set (v, 1, vy);

    gsl_vector * a = gsl_vector_alloc(2);
    gsl_vector_set (a, 0, ax);
    gsl_vector_set (a, 1, ay);

    return newParticle(mass, p, v, a);

}

void destroyParticle(Particle* p) {
    gsl_vector_free(p->acceleration);
    gsl_vector_free(p->velocity);
    gsl_vector_free(p->position);
    free(p);
    // printf("particle freed\n");
}

void drawParticle(Particle* p) {
    printParticle(p);
    BresCircle(gsl_vector_get(p->position, 0), gsl_vector_get(p->position, 1), 3, p->col, 1);
    // drawDot(gsl_vector_get(p->position, 0), gsl_vector_get(p->position, 1), col);
    printf("PARTICLE DRAWN\n");
}

void updateParticle(Particle* p) {
    printf("UPDATING PARTICLE\n");
    gsl_vector_add(p->position, p->velocity);
    gsl_vector_add(p->velocity, p->acceleration);
    // printf()
}

void printParticle(Particle* p) {
    printf("acceleration:\n");
    printVector(p->acceleration);
    printf("velocity:\n");
    printVector(p->velocity);
    printf("position:\n");
    printVector(p->position);

}

gsl_vector* direction(Particle* p) {
    return NULL;
}

double speed(Particle* p) {
    return 1.0;
}

gsl_vector* momentum(Particle* p) {
    return NULL;
}
