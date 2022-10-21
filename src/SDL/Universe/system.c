#include "system.h"
#include <stdio.h>

void addParticleToSystem(System* s, Particle* p) {
    
    // printf("adding particle to index %u\n", s->p_count);
    s->ps[s->p_count] = p;
    s->p_count=s->p_count+1;
}

System* newSystem(int x0, int x1, int y0, int y1) {
    System* s = malloc(sizeof(System));
    s->bounds = malloc(sizeof(int*));
    s->bounds[0] = malloc(2*sizeof(int));
    s->bounds[1] = malloc(2*sizeof(int));
    s->ps=malloc(sizeof(Particle*));

    s->p_count = 0;

    s->bounds[0][0] = x0;
    s->bounds[0][1] = x1;
    s->bounds[1][0] = y0;
    s->bounds[1][1] = y1;
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
void drawBounds(System* s) {
    drawLineCart(s->bounds[0][0], s->bounds[1][0], s->bounds[0][1], s->bounds[1][0], newColour(255, 0, 0, 255));
    drawLineCart(s->bounds[0][0], s->bounds[1][0], s->bounds[0][0], s->bounds[1][1], newColour(255, 0, 0, 255));
    drawLineCart(s->bounds[0][1], s->bounds[1][0], s->bounds[0][1], s->bounds[1][1], newColour(255, 0, 0, 255));
    drawLineCart(s->bounds[0][0], s->bounds[1][1], s->bounds[0][1], s->bounds[1][1], newColour(255, 0, 0, 255));

    // drawLineCart();
}
void drawSystem(System* s) {
    drawBounds(s);
    for (size_t i = 0; i < s->p_count; i++)
    {
        drawParticle(s->ps[i], newColour(255, 255, 255, 255));
    } 
}

void calculateGravityPair(Particle* p1, Particle* p2) {
    double G = 0.0001;
    double r12[] = {p2->px-p1->px, p2->py-p1->py};
    printf("%f %f\n", r12[0], r12[1]);

    double r12_mag = sqrt((r12[0]*r12[0])+(r12[1]*r12[1]));

    double r12_norm[2];
    r12_norm[0] = r12[0]/r12_mag;
    r12_norm[1] = r12[1]/r12_mag;

    double a1 = G*p2->mass/(r12_mag*r12_mag);
    double a2 = G*p1->mass/(r12_mag*r12_mag);

    p1->ax = a1*r12_norm[0];
    p1->ay = a1*r12_norm[1];

    p2->ax = -r12_mag*r12_norm[0];
    p2->ay = -r12_mag*r12_norm[1];
    

}

void updateSystemState(System* s) {
    for (size_t i = 0; i < s->p_count; i++)
    {   
        // calculateGravityPair(s->ps[0], s->ps[1]);
        updateParticle(s->ps[i]);
        if (s->ps[i]->px < s->bounds[0][0]) s->ps[i]->px = s->bounds[0][0];
        if (s->ps[i]->px > s->bounds[0][1]) s->ps[i]->px = s->bounds[0][1];
        if (s->ps[i]->py < s->bounds[1][0]) s->ps[i]->py = s->bounds[1][0];
        if (s->ps[i]->py > s->bounds[1][1]) s->ps[i]->py = s->bounds[1][1];
        printf("Particle %lu:\n"
            "\tax: %.1f, ay: %.1f, vx: %.1f, vy: %.1f, px: %.1f, py: %.1f\n", i,
            s->ps[i]->ax, s->ps[i]->ay, s->ps[i]->vx, s->ps[i]->vy, s->ps[i]->px, s->ps[i]->py);
    }
}