#include "particle.h"

typedef struct {
    // int* space;
    int** bounds; // [[x0, x1], [y0, y1], etc..]
    Particle** ps;
    uint32_t p_count;
}System;

System* newSystem(int x0, int x1, int y0, int y1);
void destroySystem(System* s);

void addParticleToSystem(System* s, Particle* p);

void drawSystem(System* s);

void updateSystemState(System* s);