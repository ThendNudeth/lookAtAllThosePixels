#include <stdlib.h>
#include <stdio.h>
#include "../makeAWindow/draw.h"
#include "../linear_algebra.h"

typedef struct {
    double mass;
    double px; //pixel
    double py;
    double vx; //pixel/frame
    double vy;
    double ax; //pixel/frame^2
    double ay;
}Particle;

Particle* newParticle(
    // System* s,
    double mass,
    double px, //pixel
    double py,
    double vx, //pixel/frame
    double vy,
    double ax, //pixel/frame^2
    double ay);

void destroyParticle(Particle* p);

void drawParticle(Particle* p, Colour col);

void updateParticle(Particle* p);

Vector direction(Particle* p);