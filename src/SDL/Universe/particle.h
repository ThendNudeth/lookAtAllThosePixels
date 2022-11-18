#include <stdlib.h>
#include <stdio.h>
#include "../makeAWindow/draw.h"
#include "../Dependencies/dependencies.h"

typedef struct {
    double mass;
    gsl_vector* position;
    gsl_vector* velocity;
    gsl_vector* acceleration;
}Particle;

Particle* newParticle(
    // System* s,
    double mass,
    gsl_vector* position,
    gsl_vector* velocity,
    gsl_vector* acceleration);

Particle* new2dParticle(double mass,
    double px,
    double py,
    double vx,
    double vy,
    double ax,
    double ay);
    
void destroyParticle(Particle* p);

void drawParticle(Particle* p, Colour col);

void updateParticle(Particle* p);

// gsl_vector* direction(Particle* p);
// Copy .net6 to slavesvc+change config vcoredb and backuplocation and nlogconfig to slavelogs