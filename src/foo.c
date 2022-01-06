//
// Created by nicholas on 2022/01/04.
//

#include "dependencies.h"

#include "imageProcessor/imageProcessor.h"
#include "framebuffer/framebuffer.h"

int main(int argc, char** argv) {
  int width, height, bpp;

  accessFramebuffer();

  struct Image image = readImage("resources/e71.jpg");

  printf("%d\n", image.image[0]);

//  displayImage(image);

  stbi_image_free(image.image);

  return 0;
}