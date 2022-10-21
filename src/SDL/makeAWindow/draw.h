#include "framebuffer.h"

// void setCanvas(SDL_Rect screenRect, uint32_t *pixels);

void drawSomething(int frame);

void drawLinePolar(uint32_t r0, double th0, uint32_t r1, double th1, Colour col);
void drawLineCart(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col);

void drawDot(uint32_t x, uint32_t y, Colour col);
void BresCircle(uint32_t xc, uint32_t yc, uint32_t r, Colour col);