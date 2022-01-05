//
// Created by nicholas on 2022/01/02.
//

#ifndef FRAMEBUFFERS_IMAGEPROCESSOR_H
#define FRAMEBUFFERS_IMAGEPROCESSOR_H

struct Image {
    uint8_t* image;
    int height;
    int width;
    int bpp;
};

int valueAt(int x, int y, int ch);
struct Image readImage(char address[]);
#endif //FRAMEBUFFERS_IMAGEPROCESSOR_H
