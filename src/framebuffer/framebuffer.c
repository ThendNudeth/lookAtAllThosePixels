//
// Created by nicholas on 2022/01/04.
//


#include "../dependencies.h"
#include "framebuffer.h"

struct fb_fix_screeninfo finfo;
struct fb_var_screeninfo vinfo;
size_t size;
uint8_t *fbp;

void setPixel(uint32_t x, uint32_t y, uint32_t r,
              uint32_t g, uint32_t b, uint32_t a) {
  uint32_t pixel = (r << vinfo.red.offset)|
                   (g << vinfo.green.offset)|
                   (b << vinfo.blue.offset)|
                   (a << vinfo.transp .offset);
  uint32_t location = x*vinfo.bits_per_pixel/8 +
                      y*finfo.line_length;
  *((uint32_t*) (fbp + location)) = pixel;
}

void accessFramebuffer() {
  int fd = open("/dev/fb0", O_RDWR);

  if (fd==-1) {
    perror("Can not access framebuffer.\n");
  }


  int vsuccess = ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);

  if (vsuccess==-1) {
    perror("Can not get screen info.\n");
    return;
  }

  int fsuccess = ioctl(fd, FBIOGET_FSCREENINFO, &finfo);

  if (fsuccess==-1) {
    perror("Can not get screen info.\n");
    return;
  }

  size = vinfo.yres * finfo.line_length;
  fbp = mmap(0, size, PROT_READ |
              PROT_WRITE, MAP_SHARED, fd, 0);
  if (fbp == (void *) -1) {
    perror("Could not map framebuffer to memory.\n");
    return;
  }

  printf("framebuffer successfully accessed.\n");
//  uint32_t x = 0;
//  uint32_t y = 400;
//  for (x = 0; x < 800; x++) {
//    setPixel(x, y, 0xFF, 0xFF, 0x00, 0xFF);
//  }
}

