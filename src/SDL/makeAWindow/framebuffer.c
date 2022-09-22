#include "framebuffer.h"

void setPixel(uint32_t * pixels, SDL_Rect screenRect, uint32_t x, uint32_t y, Colour * col) {
  uint32_t pixel = ((uint32_t)col->a << 24) | (col->r << 16) | (col->g << 8) | (col->b << 0);
  pixels[y*screenRect.w + x] = pixel;
}

Colour * newColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  Colour* col = malloc(sizeof(Colour));
  col->r = r;
  col->g = g;
  col->b = b;
  col->a = a;

  return col;
}

uint32_t argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b) { return ((uint32_t)a << 24) | (r << 16) | (g << 8) | (b << 0); }


