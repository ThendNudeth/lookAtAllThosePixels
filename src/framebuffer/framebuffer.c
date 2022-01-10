//
// Created by nicholas on 2022/01/04.
//


#include "../dependencies.h"

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
}

void drawLine(uint32_t X1[], uint32_t X2[]) {
  uint32_t start, end;
  double x0, m;
  
  if (X1[0]==X2[0]) {
    printf("Vertical line.");

    if (X1[1]<X2[1]) {
      start = X1[1];
      end = X2[1];
    } else {
      start = X2[1];
      end = X1[1];
    }

    for (uint32_t y = start; y < end; ++y) {
      setPixel(X1[0], y, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    return;
  }

  m = ((double) (X2[1] - X1[1])) /
      ((double) (X2[0] - X1[0]));

  x0 = ((double) X1[1]) - m * ((double) X1[0]);

  if (X1[0]<X2[0]) {
    start = X1[0];
    end = X2[0];
  } else {
    start = X2[0];
    end = X1[0];
  }

  for (uint32_t x = start; x < end; ++x) {

//    printf("%d: %f\n", x, m*x+x0);
    uint32_t y = round(m*x+x0);
//    printf("%d: %d\n", x, y);
    setPixel(x, y, 0xFF, 0xFF, 0xFF, 0xFF);
  }

}

uint32_t getRawPixel(uint32_t x, uint32_t y) {
  uint32_t location = x * (vinfo.bits_per_pixel / 8) +
                      y * finfo.line_length;
  return *((uint32_t*) (fbp + location));
}

