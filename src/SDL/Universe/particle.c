#include "particle.h"

Particle* newParticle(
    double mass,
    double px, //pixel
    double py,
    double vx, //pixel/frame
    double vy,
    double ax, //pixel/frame^2
    double ay) 
    {
    Particle* p = malloc(sizeof(Particle));
    p->mass = mass;
    p->px = px;
    p->py = py;
    p->vx = vx;
    p->vy = vy;
    p->ax = ax;
    p->ay = ay;
    return p;
}

void destroyParticle(Particle* p) {
    free(p);
    // printf("particle freed\n");
}

void drawParticle(Particle* p, Colour col) {
    drawDot(p->px, p->py, col);
}

void updateParticle(Particle* p) {
    p->px += p->vx;
    p->py += p->vy;
    p->vx += p->ax;
    p->vy += p->ay;
    // printf()
}

Vector direction() {

}