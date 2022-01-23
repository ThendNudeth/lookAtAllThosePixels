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

uint32_t getRawPixel(uint32_t x, uint32_t y) {
  uint32_t location = x * (vinfo.bits_per_pixel / 8) +
                      y * finfo.line_length;
  return *((uint32_t*) (fbp + location));
}

void clearScreen() {
  printf("%d %d \n", vinfo.yres, finfo.line_length);
  for (int y = 0; y < vinfo.yres; ++y) {
    for (int x = 0; x < vinfo.xres; ++x) {
      setPixel(x, y, 0x00, 0x00, 0x00, 0x00);
    }

  }
}

Colour * newColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  Colour* col = malloc(sizeof(Colour));
  col->r = r;
  col->g = g;
  col->b = b;
  col->a = a;

  return col;
}
///////////////////////////////////////////////////////////////////////////////

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

void oct1(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int D = 2 * dy - dx;
  uint32_t y = y0;

  for (uint32_t x = x0; x < x1; ++x) {
    setPixel(x, y, col->r, col->g, col->b, col->a);
    if (D > 0) {
      y++;
      D -= 2 * (dx);
    }
    D += 2 * dy;
  }
}

void oct2(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int D = 2 * dx - dy;
  uint32_t x = x0;

  for (uint32_t y = y0; y < y1; ++y) {
    setPixel(x, y, col->r, col->g, col->b, col->a);
    if (D > 0) {
      x++;
      D -= 2 * (dy);
    }
    D += 2 * dx;
  }
}

void oct3(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col) {
  int dx = x0 - x1;
  int dy = y1 - y0;
  int D = 2 * dx - dy;
  uint32_t x = x0;

  for (uint32_t y = y0; y < y1; ++y) {
    setPixel(x, y, col->r, col->g, col->b, col->a);
    if (D > 0) {
      x--;
      D -= 2 * (dy);
    }
    D += 2 * dx;
  }
}

void oct4(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col) {
  int dx = x0 - x1;
  int dy = y1 - y0;
  int D = 2 * dy - dx;
  uint32_t y = y0;

  for (uint32_t x = x0; x > x1; --x) {
    setPixel(x, y, col->r, col->g, col->b, col->a);
    if (D > 0) {
      y++;
      D -= 2 * (dx);
    }
    D += 2 * dy;
  }
}

void oct5(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col) {
  oct1(x1, y1, x0, y0, col);
}

void oct6(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col) {
  oct2(x1, y1, x0, y0, col);
}

void oct7(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col) {
  oct3(x1, y1, x0, y0, col);
}

void oct8(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col) {
  oct4(x1, y1, x0, y0, col);
}

void BresLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour* col) {
  int dy = y1 - y0;
  int dx = x1 - x0;
  if ((dy<0) == (dx<0)) { // positive (downwards) slope
    if (abs(dy)> abs(dx)) { // steep slope
      if (x0<x1) oct2(x0, y0, x1, y1, col);
      else oct6(x0, y0, x1, y1, col);
    } else { // shallow slope
      if (x0<x1) oct1(x0, y0, x1, y1, col);
      else oct5(x0, y0, x1, y1, col);
    }
  } else { // negative (upwards) slope
    if (abs(dy)> abs(dx)) { // steep slope
      if (x0>x1) oct3(x0, y0, x1, y1, col);
      else oct7(x0, y0, x1, y1, col);
    } else { // shallow slope
      if (x0>x1) oct4(x0, y0, x1, y1, col);
      else oct8(x0, y0, x1, y1, col);
    }
  }
}

void setCirclePixel(uint32_t xc, uint32_t yc, uint32_t x, uint32_t y, Colour * col) {
  setPixel(xc+x, yc+y, col->r, col->g, col->b, col->a);
  setPixel(xc-x, yc+y, col->r, col->g, col->b, col->a);
  setPixel(xc+x, yc-y, col->r, col->g, col->b, col->a);
  setPixel(xc-x, yc-y, col->r, col->g, col->b, col->a);
  setPixel(xc+y, yc+x, col->r, col->g, col->b, col->a);
  setPixel(xc-y, yc+x, col->r, col->g, col->b, col->a);
  setPixel(xc+y, yc-x, col->r, col->g, col->b, col->a);
  setPixel(xc-y, yc-x, col->r, col->g, col->b, col->a);

}

void BresCircle(uint32_t xc, uint32_t yc, uint32_t r, Colour * col) {
  uint32_t x = 0, y = r;
  uint32_t d = 3 - 2 * r;
  setCirclePixel(xc, yc, x, y, col);

  while (y >= x) {
    // for each pixel we will
    // draw all eight pixels

    x++;

    // check for decision parameter
    // and correspondingly
    // update d, x, y
    if (d > 0)
    {
      y--;
      d = d + 4 * (x - y) + 10;
    }
    else
      d = d + 4 * x + 6;
    setCirclePixel(xc, yc, x, y, col);
  }
}



