// This work (SDLblit.cpp, by Cory Bloyd) is free of known copyright restrictions.
// https://creativecommons.org/publicdomain/zero/1.0/
#include <SDL.h>
#include "framebuffer.h"


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

int main(int argc, char *argv[]) {

    // shifty();

    // iAmaLeak();

    // 0. Open logging
    FILE * fptr;
    fptr = fopen("logs/frameTimes","a");

    if (fptr==NULL)
    {
        printf("fptr null");
        return 1;
    }
    

    // 1. Initialise library and create pointer to window->create pointer to renderer->create pointer to texture
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Rect    screenRect = { 0,0,1024,1024 };
    SDL_Window   *window   = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenRect.w, screenRect.h, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture  *texture  = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screenRect.w, screenRect.h);
    
    // 2. Start frame rendering loop
    uint32_t tickDeltas;
    for (int frame = 0; ; ++frame) {
        SDL_Event event;
        // printf("%d\n", frame);
        if (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT || frame>=120) {
                printf("colptr:\n");
                printf("avg tpf: %d, avg fps: %d\n", (tickDeltas/frame), 1000/(tickDeltas/frame));
                fprintf(fptr, "avg tpf: %d, avg fps: %d\n", (tickDeltas/frame), 1000/(tickDeltas/frame));
                fclose(fptr);
                return 0;
            }
        }
            
                
        
        // 2.1 Lock texture so that it is write-only
        int pitch;
        uint32_t *pixels;
        SDL_LockTexture(texture, &screenRect, (void**)&pixels, &pitch);
        uint32_t startTicks = SDL_GetTicks();

        // 2.2 Write to texture
        for (int y = 0; y < screenRect.h; y++) {
            for (int x = 0; x < screenRect.w; x++) {
                Colour * col = newColour(255, y+frame, x+frame, 255);
                setPixel(pixels, screenRect, x, y, col);
                free(col);
            }
        }
        uint32_t endTicks = SDL_GetTicks();

        // 2.3 Unlock texture so that we can read from it
        SDL_UnlockTexture(texture);

        // 2.4 Clear the "canvas"
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // 2.5 Blit the texture to the renderer
        SDL_RenderCopy(renderer, texture, &screenRect, &screenRect);

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