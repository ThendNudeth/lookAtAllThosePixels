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

void setPixel(uint32_t x, uint32_t y, uint32_t r,
              uint32_t g, uint32_t b, uint32_t a);
uint32_t getPixel();

void accessFramebuffer();
void drawLine(uint32_t X1[], uint32_t X2[]);
void drawCircle(uint32_t x, uint32_t y, int radius);
void drawRectangle(double angle, uint32_t X1[], uint32_t X2[]);

#endif //FRAMEBUFFERS_FRAMEBUFFER_H
