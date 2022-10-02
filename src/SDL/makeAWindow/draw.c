#include "draw.h"

// void setCanvas(SDL_Rect screenRect, uint32_t *pixels) {
//     SCREEN_RECT = screenRect;
//     PIXELS = pixels;
//     return;
// }

void setPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    #ifdef HEAP_COLOURS
    Colour * col = newColourPtr(255, y+frame, x+frame, 255);
    setPixelViaColPtr(pixels, screenRect, x, y, newColourPtr(r, g, b, a));
    free(col);
    #else
    setPixelViaCol(PIXELS, SCREEN_RECT, x, y, newColour(r,g,b,a));
    #endif
    // fprintf(PIXEL_WRITE_LOG, "setting pixel at (%3d, %3d) to (%3d, %3d, %3d)\n", x, y, r, g, b);
}

void drawSomething(int frame) {
    for (int y = 0; y < SCREEN_RECT.h; y++) {
            for (int x = 0; x < SCREEN_RECT.w; x++) {
                int c = 1;
                setPixel(x, y, 100*(frame/(y+1)), c*(y+frame), c*(x+frame), 255);
                // setPixel(x, y, 0, 0, 255, 255);
            }
        }
}

void naive(int x0, int y0, int x1, int y1, Colour col) {
  double start, end;
  double c, m;

  if (x0==x1) {
    if (y0==y1)
    {
      setPixel(x0, y0, col.r, col.g, col.b, col.a);
      return;
    }
    if (y0<y1) {
      start = y0;
      end = y1;
    } else {
      start = y1;
      end = y0;
    }
    for (uint32_t y = start; y < end; ++y) {
      setPixel(x0, y, col.r, col.g, col.b, col.a);
    }
    return;
  }

  // printf("%f\n", (double) y1-y0);
  m = ((double) (y1 - y0)) /
      ((double) (x1 - x0));

  c = ((double) y0) - m * ((double) x0);

  if (x0<x1) {
    start = x0;
    end = x1;
  } else {
    start = x1;
    end = x0;
  }
  // printf("line debugging:\n"
  //           "m: %f c: %f\n"
  //           "x0: %d y0: %d x1: %d y1: %d\n", m, c, x0, y0, x1, y1);

  for (double x = start; x < end; ++x) {
    double y = round(m*x+c);
    setPixel(x, y, col.r, col.g, col.b, col.a);
  }
}

void naive2(int x0, int y0, int x1, int y1, Colour col) {
  uint32_t start, end;
  double c, m;

  if (x0==x1) {
    if (y0==y1)
    {
      setPixel(x0, y0, col.r, col.g, col.b, col.a);
      return;
    }
    if (y0<y1) {
      start = y0;
      end = y1;
    } else {
      start = y1;
      end = y0;
    }
    for (uint32_t y = start; y < end; ++y) {
      setPixel(x0, y, col.r, col.g, col.b, col.a);
    }
    return;
  }

  // printf("%f\n", (double) y1-y0);
  m = ((double) (y1 - y0)) /
      ((double) (x1 - x0));

  c = ((double) y0) - m * ((double) x0);

  if (fabs(m)>1)
  {
    if (y0<y1) {
      start = y0;
      end = y1;
    } else {
      start = y1;
      end = y0;
    }
    // printf("line debugging:\n"
    //           "m: %f c: %f\n"
    //           "x0: %d y0: %d x1: %d y1: %d\n", m, c, x0, y0, x1, y1);

    for (uint32_t y = start; y < end; ++y) {

      uint32_t x = round((y-c)/m);

      setPixel(x, y, col.r, col.g, col.b, col.a);
    }
    return;
  }
  
  if (x0<x1) {
    start = x0;
    end = x1;
  } else {
    start = x1;
    end = x0;
  }
  // printf("line debugging:\n"
  //           "m: %f c: %f\n"
  //           "x0: %d y0: %d x1: %d y1: %d\n", m, c, x0, y0, x1, y1);

  for (uint32_t x = start; x < end; ++x) {

    uint32_t y = round(m*x+c);

    setPixel(x, y, col.r, col.g, col.b, col.a);
  }
}

void oct1(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int D = 2 * dy - dx;
  uint32_t y = y0;

  for (uint32_t x = x0; x < x1; ++x) {
    setPixel(x, y, col.r, col.g, col.b, col.a);
    if (D > 0) {
      y++;
      D -= 2 * dx;
    }
    D += 2 * dy;
  }
}

void oct2(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int D = 2 * dx - dy;
  uint32_t x = x0;

  for (uint32_t y = y0; y < y1; ++y) {
    setPixel(x, y, col.r, col.g, col.b, col.a);
    if (D > 0) {
      x++;
      D -= 2 * (dy);
    }
    D += 2 * dx;
  }
}

void oct3(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
  int dx = x0 - x1;
  int dy = y1 - y0;
  int D = 2 * dx - dy;
  uint32_t x = x0;

  for (uint32_t y = y0; y < y1; ++y) {
    setPixel(x, y, col.r, col.g, col.b, col.a);
    if (D > 0) {
      x--;
      D -= 2 * (dy);
    }
    D += 2 * dx;
  }
}

void oct4(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
  int dx = x0 - x1;
  int dy = y1 - y0;
  int D = 2 * dy - dx;
  uint32_t y = y0;

  for (uint32_t x = x0; x > x1; --x) {
    setPixel(x, y, col.r, col.g, col.b, col.a);
    if (D > 0) {
      y++;
      D -= 2 * (dx);
    }
    D += 2 * dy;
  }
}

void oct5(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
  oct1(x1, y1, x0, y0, col);
}

void oct6(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
  oct2(x1, y1, x0, y0, col);
}

void oct7(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
  oct3(x1, y1, x0, y0, col);
}

void oct8(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
  oct4(x1, y1, x0, y0, col);
}

void BresLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
  int dy = y1 - y0;
  int dx = x1 - x0;

  // Points and lines parallel to axis
  if (dy==0)
  {
    if (dx==0)
    {
      setPixel(x0, y0, col.r, col.g, col.b, col.a);
      return;
    }
    // printf("hline");
    if (dx>0)
    {
      uint32_t start = x0;
      uint32_t end = x1;
      for (uint32_t x = start; x < end; x++)
      {
        setPixel(x, y0, col.r, col.g, col.b, col.a);
      }
    } else {
      uint32_t start = x1;
      uint32_t end = x0;
      for (uint32_t x = start; x < end; x++)
      {
        setPixel(x, y0, col.r, col.g, col.b, col.a);
      }
    }
    return;
  }

  if (dx==0)
  {
    // printf("vline");
    if (dy>0)
    {
      uint32_t start = y0;
      uint32_t end = y1;
      for (uint32_t y = start; y < end; y++)
      {
        setPixel(x0, y, col.r, col.g, col.b, col.a);
      }
    } else {
      uint32_t start = y1;
      uint32_t end = y0;
      for (uint32_t y = start; y < end; y++)
      {
        setPixel(x0, y, col.r, col.g, col.b, col.a);
      }
    }
    return;
  }
  
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

void setCirclePixel(uint32_t xc, uint32_t yc, uint32_t x, uint32_t y, Colour col) {
  setPixel(xc+x, yc+y, col.r, col.g, col.b, col.a);
  setPixel(xc-x, yc+y, col.r, col.g, col.b, col.a);
  setPixel(xc+x, yc-y, col.r, col.g, col.b, col.a);
  setPixel(xc-x, yc-y, col.r, col.g, col.b, col.a);
  setPixel(xc+y, yc+x, col.r, col.g, col.b, col.a);
  setPixel(xc-y, yc+x, col.r, col.g, col.b, col.a);
  setPixel(xc+y, yc-x, col.r, col.g, col.b, col.a);
  setPixel(xc-y, yc-x, col.r, col.g, col.b, col.a);

}

void BresCircle(uint32_t xc, uint32_t yc, uint32_t r, Colour col) {
  int x = 0, y = r;
  int d = 3 - 2 * r;
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

void drawLinePolar(uint32_t r0, double th0, uint32_t r1, double th1, Colour col) {
    // printf("executes\n");
    int x0 = r0*cos(th0);
    int y0 = r0*sin(th0);
    int x1 = r1*cos(th1);
    int y1 = r1*sin(th1);

    // printf("[%d, %d], [%d|%d, %d|%d]\n", x0, y0, x0+x1, x1, y0+y1, y1);
    drawLineCart(x0, y0, x0+x1, y0+y1, col);

}

void BresLine2(int x0, int y0, int x1, int y1, Colour col) {
  int dx = abs(x1 - x0);
  int sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1-y0);
  int sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;

  while (1)
  {
    setPixel(x0, y0, col.r, col.g, col.b, col.a);
    if (x0==x1 && y0==y1) break;
    int e2 = 2*err;
    if (e2 >= dy)
    {
      if (x0==x1) break;
      err = err + dy;
      x0 = x0 + sx;
    }
    if (e2 <= dx) {
      if (y0 == y1) break;
      err = err + dx;
      y0 = y0 + sy;
    }
  }
  
}
void drawLineCart(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Colour col) {
    #ifdef NAIVE
    naive(x0, y0, x1, y1, col);
    #elif NAIVE2
    naive2(x0, y0, x1, y1, col);
    #else
    BresLine(x0, y0, x1, y1, col);
    // printf("bres");
    #endif
}