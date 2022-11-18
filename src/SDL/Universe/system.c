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
        drawParticle(s->ps[i], newRandomColour());
    } 
}

double normalise(gsl_vector* v) {

    gsl_vector* n = gsl_vector_alloc(v->size);
    gsl_vector_memcpy(n, v);
    gsl_vector_mul(n, n);
    printVector(n);
    double len_sqrd = gsl_vector_sum(n);

    if (len_sqrd == 0.0)
    {
        gsl_vector_free(n);
        return 0;
    }
    
    printf("length squared: ");
    printFloat(len_sqrd);
    double len = sqrt(len_sqrd);
    printf("length: ");
    printFloat(len);
    printFloat(1.0/len);
    gsl_vector_scale(v, 1.0/(len));
    gsl_vector_free(n);

    return len_sqrd;

}

void applyForceToParticle(gsl_vector* force_vector, Particle* p) {
    // F = ma
    // a = F/m
    gsl_vector* gravitational_acceleration = gsl_vector_alloc(force_vector->size);
    gsl_vector_memcpy(gravitational_acceleration, force_vector);
    gsl_vector_scale(gravitational_acceleration, 1/p->mass);

    gsl_vector_memcpy(p->acceleration, gravitational_acceleration);
    // p->acceleration = gravitational_acceleration;
    // gsl_vector_add(p->acceleration, gravitational_acceleration);
    gsl_vector_free(gravitational_acceleration);

}

/** 
 * Calculate the gravitational pull of particle p1 on particle p2.
 * **/
void calculateGravitationalPull(Particle* p1, Particle* p2) {
    double G = 1;

    // Calculate the direction of the force.
    gsl_vector* gravity_force_vector = gsl_vector_alloc(p1->position->size);
    gsl_vector_memcpy(gravity_force_vector, p1->position);
    gsl_vector_sub(gravity_force_vector, p2->position);

    double len_sqrd = normalise(gravity_force_vector);
    printVector(gravity_force_vector);

    // Scale the vector according to the magnitude.
    if (len_sqrd == 0.0) 
        gsl_vector_scale(gravity_force_vector, 0);
    else 
        gsl_vector_scale(gravity_force_vector, (p1->mass*p2->mass)/len_sqrd);
    
    printVector(gravity_force_vector);

    applyForceToParticle(gravity_force_vector, p2);

    gsl_vector_free(gravity_force_vector);

}

void updateSystemState(System* s) {
    for (size_t i = 0; i < s->p_count; i++)
    {   
        // for (size_t j = 0; i < s->p_count; i++)
        // {
        //     if (i!=j) calculateGravitationalPull(s->ps[i], s->ps[j]);
        // }
        if (i == 0)
            calculateGravitationalPull(s->ps[1], s->ps[0]);
        if (i == 1)
            calculateGravitationalPull(s->ps[0], s->ps[1]);
        
        updateParticle(s->ps[i]);
        if (gsl_vector_get(s->ps[i]->position, 0) < s->bounds[0][0]) 
                gsl_vector_set(s->ps[i]->position, 0, s->bounds[0][0]);
        if (gsl_vector_get(s->ps[i]->position, 0) > s->bounds[0][1]) 
                gsl_vector_set(s->ps[i]->position, 0, s->bounds[0][1]);
        if (gsl_vector_get(s->ps[i]->position, 1) < s->bounds[1][0]) 
                gsl_vector_set(s->ps[i]->position, 1, s->bounds[1][0]);
        if (gsl_vector_get(s->ps[i]->position, 1) > s->bounds[1][1]) 
                gsl_vector_set(s->ps[i]->position, 1, s->bounds[1][1]);
        printf("Particle %lu:\n"
            "\tax: %.4f, ay: %.4f, vx: %.4f, vy: %.4f, px: %.2f, py: %.2f\n", i,
            gsl_vector_get(s->ps[i]->acceleration, 0), 
            gsl_vector_get(s->ps[i]->acceleration, 1), 
            gsl_vector_get(s->ps[i]->velocity, 0), 
            gsl_vector_get(s->ps[i]->velocity, 1), 
            gsl_vector_get(s->ps[i]->position, 0),
            gsl_vector_get(s->ps[i]->position, 1));
    }
}