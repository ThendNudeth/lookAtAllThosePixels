#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <math.h>

SDL_Rect SCREEN_RECT;
uint32_t *PIXELS;
FILE * PIXEL_WRITE_LOG;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
}Colour;

uint32_t argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

void setPixelViaColPtr(uint32_t *pixels, SDL_Rect screenRect, uint32_t x, uint32_t y, Colour * col);
void setPixelViaCol(uint32_t *pixels, SDL_Rect screenRect, uint32_t x, uint32_t y, Colour col);

Colour * newColourPtr(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
Colour newColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
Colour newRandomColour();