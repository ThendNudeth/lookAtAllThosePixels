//
// Created by nicholas on 2022/01/02.
//

#include "../dependencies.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imageProcessor.h"

struct Image readImage(char address[]) {
  printf("hello");
  int width, height, bpp;
  struct Image image;

  printf("%s", address);
  uint8_t* rgb_image = stbi_load("e71.jpg", &width, &height, &bpp, 3);
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

//  image.image = rgb_image;
//  image.height = height;
//  image.width = width;
//  image.bpp = bpp;

  return image;
}