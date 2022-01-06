//
// Created by nicholas on 2022/01/02.
//

#include "../dependencies.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imageProcessor.h"
#include "../framebuffer/framebuffer.h"

struct Image readImage(char address[]) {
  int width, height, bpp;
  struct Image image;

  printf("%s\n", address);
  uint8_t* rgb_image = stbi_load(address, &width, &height, &bpp, 3);
  printf("pixel 0.0: %d\n",rgb_image[0]);
//  printf("pixel 0.1: %d\n",rgb_image[1]);
//  printf("pixel 0.2: %d\n",rgb_image[2]);
//  printf("pixel 1.0: %d\n",rgb_image[3]);

//  uint8_t image_mat[height][width][bpp];
//  int i = 0;
//  for (int y = 0; y < height; ++y) {
//    for (int x = 0; x < width; ++x) {
//      for (int ch = 0; ch < bpp; ++ch) {
//        image_mat[y][x][ch] = rgb_image[i];
//        i++;
//      }
//    }
//  }

  image.image = rgb_image;
  image.height = height;
  image.width = width;
  image.bpp = bpp;

  return image;
}

void displayImage(struct Image image) {
  int i;

  if (image.bpp==3) {
    i = 0;
    for (uint32_t y = 0; y < image.height; y++) {
      for (uint32_t x = 0; x < image.width; x++) {
        setPixel(x, y, image.image[i], image.image[i+1], image.image[i+2], 0xFF);
        i+=3;
      }
    }
  } else if (image.bpp==4) {
    i = 0;
    for (uint32_t y = 0; y < image.height; y++) {
      for (uint32_t x = 0; x < image.width; x++) {
        setPixel(x, y, image.image[i], image.image[i+1], image.image[i+2], image.image[i+3]);
        i+=4;
      }
    }
  } else {
    perror("Unsupported number of channels");
  }

}