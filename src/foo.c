//
// Created by nicholas on 2022/01/04.
//

#include "dependencies.h"
#include <ncurses.h>

#include "imageProcessor/imageProcessor.h"

int main(int argc, char** argv) {
  int width, height, bpp, opt;

  initscr();

  WINDOW * win = newwin(25, 80, 0, 0);
  refresh();

  box(win, 0, 0);
//  wborder(win, 0,0,0,0,0)
  mvwprintw(win, 1, 1, "Hello world!");
  wrefresh(win);


  getch();

  endwin();

//  while ((opt = getopt(argc, argv, ":if:lrx")) != -1) {
//    switch(opt) {
//      case 'i':
//      case 'l':
//      case 'r':
//        printf("option: %c\n", opt);
//        break;
//      case 'f':
//        printf("filename: %s\n", optarg);
//        break;
//      case ':':
//        printf("option needs a value\n");
//        break;
//      case '?':
//        printf("unknown option: %c\n", optopt);
//        break;
//    }
//  }
//
//  for(; optind < argc; optind++) {
//    printf("extra arguments: %s\n", argv[optind]);
//  }

//  accessFramebuffer();

//  Image* image = readImage("resources/e71.jpg");

//  displayImage(image);

//  freeImage(image);

//  uint32_t X1[] = {0,0};
//  uint32_t X2[] = {1500, 750};
//  drawLine(X1, X2);


  return 0;
}



