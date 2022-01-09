//
// Created by nicholas on 2022/01/02.
//

#ifndef FRAMEBUFFERS_IMAGEPROCESSOR_H
#define FRAMEBUFFERS_IMAGEPROCESSOR_H

typedef struct {
    uint8_t *** image;
    int height;
    int width;
    int bpp;
}Image;

Image* readImage(char address[]);
void displayImage(Image* image);
void freeImage(Image* image);
#endif //FRAMEBUFFERS_IMAGEPROCESSOR_H
