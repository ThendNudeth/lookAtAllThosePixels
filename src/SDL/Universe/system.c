#include "system.h"
#include <stdio.h>

void addParticleToSystem(System* s, Particle* p) {
    
    // printf("adding particle to index %u\n", s->p_count);
    s->ps[s->p_count] = p;
    s->p_count=s->p_count+1;
}

System* newSystem() {
    System* s = malloc(sizeof(System));
    // int* space = malloc(sizeof(int));
    // s->space = space;
    s->ps=malloc(sizeof(Particle*));
    s->p_count = 0;
    return s;
}

void destroySystem(System* s) {
    for (size_t i = 0; i < s->p_count; i++)
    {   
        printf("destroying particle %lu\n", i);
        destroyParticle(s->ps[i]);
    }
    free(s->ps);
    // free(s->space);
    free(s);
}

void drawSystem() {
    
}