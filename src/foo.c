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
                       "draw a line",
                       "draw a rectangle",
                       "draw"};
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

  if (highlight==0) {
    accessFramebuffer();

    Image* image = readImage("resources/e71.jpg");

    displayImage(image);

    freeImage(image);
  }


//  uint32_t X1[] = {0,0};
//  uint32_t X2[] = {1500, 750};
//  drawLine(X1, X2);

  exit_curses(0);
  return 0;
}



