#include "particle.h"

Particle* newParticle() {
    Particle* p = malloc(sizeof(Particle));
    p->ax = 0;
    p->ay = 0;
    p->px = 0;
    p->py = 0;
    p->vx = 0;
    p->vy = 0;
    return p;
}

void destroyParticle(Particle* p) {
    free(p);
    // printf("particle freed\n");
}