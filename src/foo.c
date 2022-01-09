//
// Created by nicholas on 2022/01/04.
//

#include "dependencies.h"

#include "imageProcessor/imageProcessor.h"
#include "framebuffer/framebuffer.h"

int main(int argc, char** argv) {
  int width, height, bpp;

  accessFramebuffer();

  Image* image = readImage("resources/e71.jpg");

  displayImage(image);

  freeImage(image);

//  uint32_t X1[] = {0,0};
//  uint32_t X2[] = {1500, 750};
//  drawLine(X1, X2);

  return 0;
}
