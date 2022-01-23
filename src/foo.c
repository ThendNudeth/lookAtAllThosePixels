//
// Created by nicholas on 2022/01/04.
//

#include "dependencies.h"
#include <ncurses.h>

#include "imageProcessor/imageProcessor.h"

int main(int argc, char** argv) {
  int width, height, x, y;

  initscr();

  WINDOW * win = newwin(25, 80, 0, 0);
  box(win, 0, 0);
//  wborder(win, 0,0,0,0,0)

//  mvwprintw(win, 1, 1, "Hello world!");
  mvwprintw(win, 1, 1, "What would you like to do?");
  refresh();
  wrefresh(win);

  keypad(win, true);

  const int NUM_OPTIONS = 4;
  char * options[] = {"show a picture",
                       "draw a line (naive)",
                       "draw a line (Bresenham)",
                       "exit"};
  int choice;
  int highlight = 0;

  while (1) {
    for (int i = 0; i < NUM_OPTIONS; ++i) {
      if (i == highlight) {
        wattron(win, A_REVERSE);
      }
      mvwprintw(win, i+3, 1, options[i]);
      wattroff(win, A_REVERSE);
    }
    choice = wgetch(win);

    switch (choice) {
      case KEY_UP:
        highlight--;
        if (highlight == -1) {
          highlight = 0;
        }
        break;
      case KEY_DOWN:
        highlight++;
        if (highlight == NUM_OPTIONS) {
          highlight = NUM_OPTIONS-1;
        }
      default:
        break;
    }
    if (choice == 10) break;
  }

//  getbegyx(win, y, x);
//  getmaxyx(win, height, width);
//  mvwprintw(win, 1, 1, "%d %d", height, width);
//  wrefresh(win);
//  keypad()

  endwin();

  accessFramebuffer();
  clearScreen();

  if (highlight==0) {

    Image* image = readImage("resources/e71.jpg");

    displayImage(image);

    freeImage(image);
  }
  
  if (highlight==1) {

    uint32_t X1[] = {0,0};
    uint32_t X2[] = {1500, 750};

    drawLine(X1, X2);

  }

  if (highlight == 2) {

    uint32_t X1[] = {0,0};
    uint32_t X2[] = {1500, 750};

    Colour* red = newColour(255, 0, 0, 0);
    Colour* green = newColour(0, 255, 0, 0);
    Colour* blue = newColour(0, 0, 255, 0);
    Colour* yellow = newColour(255, 255, 0, 0);
    Colour* magenta = newColour(255, 0, 255, 0);
    Colour* cyan = newColour(0, 255, 255, 0);
    Colour* gray = newColour(128, 128, 128, 0);
    Colour* white = newColour(255, 255, 255, 0);

//    drawLine(X1, X2);
    BresLine(0, 0, 200, 100, red); //oct1
    BresLine(210, 100, 10, 0, green); //oct5

    BresLine(0, 0, 100, 200, blue); //oct2
    BresLine(110, 200, 10, 0, yellow); //oct6

    BresLine(100, 0, 0, 200, magenta); //oct3
    BresLine(10, 200, 110, 0, cyan); //oct7

    BresLine(200, 0, 0, 100, gray); //oct4
    BresLine(10, 100, 210, 0, white); //oct8

    BresCircle(50, 50, 30, red);

    free(red);
    free(green);
    free(blue);
    free(yellow);
    free(magenta);
    free(cyan);
    free(white);
    free(gray);

  }
  if (highlight == 3) {
    int a = -1;
    uint32_t b = 10;
    uint32_t c = 12;
    uint32_t d = -10;
    printf("%d", abs((int) d)); //Hoekom werk dit?
    return 0;
  }

  int quit = 0;
  printf("Press ENTER to quit.");
  while (quit != 10) {
    quit = getchar();
  }

  clearScreen();

  return 0;
}



