// This work (SDLblit.cpp, by Cory Bloyd) is free of known copyright restrictions.
// https://creativecommons.org/publicdomain/zero/1.0/

// #include "draw.h"
#include "../Universe/system.h"
// #define HEAP_COLOURS 0
// ^ Use -D HEAP_COLOURS to run with pixel values stored on the heap instead of stack.
// ^ If you choose to do this, prepare for a significant drop in fps.



void iAmaLeak() {
    for (size_t i = 0; i < 1; i++)
    {
        int* mem =  malloc(sizeof(int));
    }
}

void shifty() {
    printf("%d\n", (10));
    printf("%d\n", (10<<1));
    printf("%d\n", (10>>1));
    printf("%d\n", (1));
    printf("%d\n", (1<<1));
    printf("%d\n", (1>>1));
    printf("%d\n", (0));
    printf("%d\n", (0<<1));
    printf("%d\n", (0>>1));
}

// void makeAUniverse() {
//     System* s = newSystem();

//     // addParticleToSystem(s, newParticle());

//     destroySystem(s);
// }


int openWindowAndRenderStuff(int argc, char *argv[]) {
    
    // 0. Open logging
    FILE * frameTsLog;
    frameTsLog = fopen("logs/frameTimes","a");
    PIXEL_WRITE_LOG = fopen("logs/PixelWrites","w");

    if (frameTsLog == NULL || PIXEL_WRITE_LOG == NULL)
    {
        printf("fptr null");
        return 1;
    }
    
    // 1. Initialise library and create pointer to window->create pointer to renderer->create pointer to texture
    SDL_Init(SDL_INIT_VIDEO);

    // SCREEN_RECT can be found in framebuffer.h/framebuffer.c
    if (argc>1) {
        char *p;
        SCREEN_RECT.w = strtol(argv[1], &p, 10);
        SCREEN_RECT.h = strtol(argv[2], &p, 10);
    }

    System* s = newSystem(1,SCREEN_RECT.w-1, 1, SCREEN_RECT.h-1);
    addParticleToSystem(s, new2dParticle(2, SCREEN_RECT.w/2, SCREEN_RECT.h/2, 0, 0.2, 0, 0));
    addParticleToSystem(s, new2dParticle(2, SCREEN_RECT.w/2+40, SCREEN_RECT.h/2, 0, -0.2, 0, 0));
    
    SDL_Window   *window   = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_RECT.w, SCREEN_RECT.h, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture  *texture  = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_RECT.w, SCREEN_RECT.h);
    
    // 2. Start frame rendering loop
    uint32_t tickDeltas;
    for (int frame = 0; /*frame < 3*/; ++frame) {
        SDL_Event event;

        if (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                #ifdef HEAP_COLOURS
                fprintf(frameTsLog,"heap_col|");
                #else
                fprintf(frameTsLog,"stack_col|");
                #endif

                #ifdef NAIVE
                fprintf(frameTsLog,"naive|");
                #elif NAIVE2
                fprintf(frameTsLog,"naive2|");
                #else
                fprintf(frameTsLog,"Bres|");
                #endif
                fprintf(frameTsLog,"\n");
                fprintf(frameTsLog, "avg tpf: %d, avg fps: %d\n", (tickDeltas/frame), 1000/(tickDeltas/frame));
                fclose(frameTsLog);
                destroySystem(s);
                return 0;
            }
        }
            
        // 2.1 Lock texture so that it is write-only
        int pitch;
        // uint32_t *pixels;
        SDL_LockTexture(texture, &SCREEN_RECT, (void**)&PIXELS, &pitch);
        uint32_t startTicks = SDL_GetTicks();

        // 2.2 Write to texture
        // drawSomething(frame);
        drawSystem(s);
        updateSystemState(s);
        // BresCircle(320, 240, 100, newColour(255,255,255,255), 1);

        uint32_t endTicks = SDL_GetTicks();

        // 2.3 Unlock texture so that we can read from it
        SDL_UnlockTexture(texture);

        // 2.4 Clear the "canvas"
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // 2.5 Blit the texture to the renderer
        SDL_RenderCopy(renderer, texture, &SCREEN_RECT, &SCREEN_RECT);

        // 2.6 Display the texture
        SDL_RenderPresent(renderer);

        uint32_t tickDelta = endTicks - startTicks;
        tickDeltas += tickDelta;

        char title[32];
        SDL_SetWindowTitle(window, SDL_itoa(tickDelta, title, 10));
    }

    printf("Crash\n");
    return 1;
}
int main(int argc, char *argv[]) {

    // shifty();
    // makeAUniverse();

    // iAmaLeak();

    return openWindowAndRenderStuff(argc, argv);

    return 0;

    
}