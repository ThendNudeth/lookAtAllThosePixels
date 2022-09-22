#include <stdlib.h>
#include <SDL.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
}Colour;

uint32_t argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

void setPixel(uint32_t *pixels, SDL_Rect screenRect, uint32_t x, uint32_t y, Colour * col);

Colour * newColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);