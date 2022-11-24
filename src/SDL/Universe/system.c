#include "system.h"
#include <stdio.h>

void addParticleToSystem(System* s, Particle* p) {
    
    printf("ADDING PARTICLE %lu TO SYSTEM WITH INITIAL CONDITIONS:\n", s->p_count);
    printParticle(p);
    s->ps[s->p_count] = p;
    s->p_count=s->p_count+1;
}

System* newSystem(int x0, int x1, int y0, int y1) {
    System* s = malloc(sizeof(System));
    s->bounds = malloc(sizeof(int*));
    s->bounds[0] = malloc(2*sizeof(int));
    s->bounds[1] = malloc(2*sizeof(int));
    s->ps=malloc(1000*sizeof(Particle*));

    s->p_count = 0;

    s->bounds[0][0] = x0;
    s->bounds[0][1] = x1;
    s->bounds[1][0] = y0;
    s->bounds[1][1] = y1;
    return s;
}

System* InertialTwoBodySystem(int x0, int x1, int y0, int y1) {
    System* s = newSystem(x0, x1, y0, y1);
    addParticleToSystem(s, new2dParticle(20, (x1-x0)/2+x0-100, (y1-y0)/2+y0, 0, 0, 0, 0));
    addParticleToSystem(s, new2dParticle(20, (x1-x0)/2+x0+100, (y1-y0)/2+y0, 0, 0, 0, 0));

    return s;
}

System* rotatingTwoBodySystem(int x0, int x1, int y0, int y1) {
    System* s = newSystem(x0, x1, y0, y1);
    addParticleToSystem(s, new2dParticle(20, (x1-x0)/2+x0-100, (y1-y0)/2+y0, 0, 0.2, 0, 0));
    addParticleToSystem(s, new2dParticle(20, (x1-x0)/2+x0+100, (y1-y0)/2+y0, 0, -0.2, 0, 0));

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

    BresCircle((s->bounds[0][1]-s->bounds[0][0])/2 + s->bounds[0][0], (s->bounds[1][1]-s->bounds[1][0])/2 + s->bounds[1][0], 3, newColour(255, 255, 255, 255), 1);
    // drawLineCart();
}
void drawSystem(System* s) {
    drawBounds(s);
    for (size_t i = 0; i < s->p_count; i++)
    {
        printf("DRAWING PARTICLE %lu\n", i);
        drawParticle(s->ps[i]);
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
gsl_vector* calculateGravitationalPull(Particle* p1, Particle* p2) {
    double G = 1;

    // Calculate the direction of the force.
    gsl_vector* gravity_force_vector = gsl_vector_alloc(p1->position->size);
    gsl_vector_memcpy(gravity_force_vector, p1->position);
    gsl_vector_sub(gravity_force_vector, p2->position);


    double len_sqrd = normalise(gravity_force_vector);
    printVector(gravity_force_vector);

    // Scale the vector according to the magnitude.
    // if (len_sqrd == 0.0) 
    //     return NULL;
    // else 
        gsl_vector_scale(gravity_force_vector, (p1->mass*p2->mass)/len_sqrd);
    
    printVector(gravity_force_vector);

    return gravity_force_vector;

    // applyForceToParticle(gravity_force_vector, p2);

    // gsl_vector_free(gravity_force_vector);

}

void calculateResultantForceVector(System* s, Particle* p, size_t j) {
    gsl_vector* net_force_vector = gsl_vector_calloc(p->acceleration->size);

    for (size_t i = 0; i < s->p_count; i++)
    {
        if (j != i) {
            printf("Considering particle %lu and %lu:\n", i, j);

            gsl_vector* gravity_force_vector = calculateGravitationalPull(s->ps[i], p);
            gsl_vector_add(net_force_vector, gravity_force_vector);

            gsl_vector_free(gravity_force_vector);
        }
            
    }
    
    applyForceToParticle(net_force_vector, p);
    printf("\nNet force acting on particle %lu:\n", j);
    printVector(net_force_vector);
    printf("\n");
    gsl_vector_free(net_force_vector);

}

void calculateSystemGravity(System* s) {
    for (size_t i = 0; i < s->p_count; i++)
    { 
        calculateResultantForceVector(s, s->ps[i], i);
    }
}

void updateSystemState(System* s) {

    printf("UPDATING SYSTEM STATE\n");
    calculateSystemGravity(s);

    for (size_t i = 0; i < s->p_count; i++)
    {   
        updateParticle(s->ps[i]);
        if (gsl_vector_get(s->ps[i]->position, 0) <= s->bounds[0][0]) {
            gsl_vector_set(s->ps[i]->position, 0, s->bounds[0][0]+1);
            gsl_vector_scale(s->ps[i]->velocity, 0);
            gsl_vector_scale(s->ps[i]->acceleration, 0);
        }
                
        if (gsl_vector_get(s->ps[i]->position, 0) >= s->bounds[0][1]) {
            gsl_vector_set(s->ps[i]->position, 0, s->bounds[0][1]-1);
            gsl_vector_scale(s->ps[i]->velocity, 0);
            gsl_vector_scale(s->ps[i]->acceleration, 0);
        }
        if (gsl_vector_get(s->ps[i]->position, 1) <= s->bounds[1][0]) {
            gsl_vector_set(s->ps[i]->position, 1, s->bounds[1][0]+1);
            gsl_vector_scale(s->ps[i]->velocity, 0);
            gsl_vector_scale(s->ps[i]->acceleration, 0);
        }
                
        if (gsl_vector_get(s->ps[i]->position, 1) >= s->bounds[1][1]) {
            gsl_vector_set(s->ps[i]->position, 1, s->bounds[1][1]-1);
            gsl_vector_scale(s->ps[i]->velocity, 0);
            gsl_vector_scale(s->ps[i]->acceleration, 0);
        }
                
        printf("Particle %lu:\n", i);
        printParticle(s->ps[i]);
        
        for (size_t j = 0; j < s->p_count; j++)
        {   
            if (i!=j) {
                printf("Distance petween p%lu and p%lu:\n", i, j);
                gsl_vector* pos_diff = gsl_vector_alloc(s->ps[i]->position->size);
                gsl_vector_memcpy(pos_diff, s->ps[i]->position);
                gsl_vector_sub(pos_diff, s->ps[j]->position);
                gsl_vector_mul(pos_diff, pos_diff);
                double dist = sqrt(gsl_vector_sum(pos_diff));
                printFloat(dist);
                printVector(s->ps[i]->position);
                printVector(s->ps[j]->position);
                if (dist < 1.0)
                {
                    printf("COLLISION\n");
                }
                gsl_vector_free(pos_diff);
            }
              
        }
        
    }
    printf("SYSTEM STATE UPDATED\n");
}