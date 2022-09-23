//
// Created by nicholas on 2022/01/02.
//

#ifndef FRAMEBUFFERS_FRAMEBUFFER_H
#define FRAMEBUFFERS_FRAMEBUFFER_H

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
}Colour;

enum method {
    Naive     = 0,
    Bresenham,
    Highm,
    Lowm
};

void setPixel(uint32_t x, uint32_t y, uint32_t r,
              uint32_t g, uint32_t b, uint32_t a);

uint32_t getPixel();

void accessFramebuffer();

void clearScreen();

Colour * newColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void drawLine(uint32_t X1[], uint32_t X2[]);

void naive(uint32_t X1[], uint32_t X2[]);
void BresLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col);
void BresCircle(uint32_t xc, uint32_t yc, uint32_t r, Colour * col);

#endif //FRAMEBUFFERS_FRAMEBUFFER_H
