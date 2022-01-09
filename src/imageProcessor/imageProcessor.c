//
// Created by nicholas on 2022/01/02.
//

#include "../dependencies.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imageProcessor.h"
#include "../framebuffer/framebuffer.h"

Image* readImage(char address[]) {
  int width, height, bpp;
  Image* image;

  uint8_t* rgb_image = stbi_load(address, &width, &height, &bpp, 3);

  uint8_t *** image_mat = (uint8_t ***) malloc(sizeof(uint8_t **)*height);

  int i = 0;
  for (int y = 0; y < height; ++y) {
    image_mat[y] = (uint8_t **) malloc(width * sizeof(uint8_t *));

    for (int x = 0; x < width; ++x) {
      image_mat[y][x] = (uint8_t *) malloc(bpp * sizeof(uint8_t));

      for (int ch = 0; ch < bpp; ++ch) {
        image_mat[y][x][ch] = rgb_image[i];
        i++;
      }
    }
  }

  stbi_image_free(rgb_image);

  image = (Image*) malloc((sizeof(uint8_t)*height*width*bpp)+(3* sizeof(int)));

  image->image = image_mat;
  image->height = height;
  image->width = width;
  image->bpp = bpp;

  return image;
}

void displayImage(Image* image) {
  int i;

  if (image->bpp==3) {
    for (uint32_t y = 0; y < image->height; y++) {
      for (uint32_t x = 0; x < image->width; x++) {
        setPixel(x, y, image->image[y][x][0], image->image[y][x][1],
                 image->image[y][x][2], 0xFF);
      }
    }
  }
  else if (image->bpp==4) {
    i = 0;
    for (uint32_t y = 0; y < image->height; y++) {
      for (uint32_t x = 0; x < image->width; x++) {
        setPixel(x, y, image->image[y][x][0], image->image[y][x][1],
                 image->image[y][x][2], image->image[y][x][3]);
        i+=4;
      }
    }
  } else {
    perror("Unsupported number of channels");
  }
}

void freeImage(Image* image) {
  for (int y = 0; y < image->height; ++y) {
    for (int x = 0; x < image->width; ++x) {
      free(image->image[y][x]);
    }
    free(image->image[y]);
  }
  free(image->image);
  free(image);
}