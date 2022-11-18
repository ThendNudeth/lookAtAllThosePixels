#include "particle.h"

Particle* newParticle(
    double mass,
    gsl_vector* position,
    gsl_vector* velocity,
    gsl_vector* acceleration) 
    {
    Particle* p = malloc(sizeof(Particle));
    p->mass = mass;
    p->position = position;
    p->velocity = velocity;
    p->acceleration = acceleration;
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

void drawParticle(Particle* p, Colour col) {
    BresCircle(gsl_vector_get(p->position, 0), gsl_vector_get(p->position, 1), 6, col, 1);
    // drawDot(gsl_vector_get(p->position, 0), gsl_vector_get(p->position, 1), col);
}

void updateParticle(Particle* p) {
    gsl_vector_add(p->position, p->velocity);
    gsl_vector_add(p->velocity, p->acceleration);
    // printf()
}

// gsl_vector* direction() {
//     return NULL;
// }