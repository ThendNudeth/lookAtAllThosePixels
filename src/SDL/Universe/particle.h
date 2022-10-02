#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double px; //pixel
    double py;
    double vx; //pixel/frame
    double vy;
    double ax; //pixel/frame^2
    double ay;
}Particle;

Particle* newParticle();
void destroyParticle(Particle* p);

void drawParticle(Particle* p);