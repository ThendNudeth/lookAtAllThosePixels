#include "particle.h"

typedef struct {
    // int* space;
    Particle** ps;
    uint32_t p_count;
}System;

System* newSystem();
void destroySystem(System* s);

void addParticleToSystem(System* s, Particle* p);

void drawSystem();