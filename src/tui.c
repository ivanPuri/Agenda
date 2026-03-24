#include <ncurses.h>

void draw_borders();

void start_window(){
  initscr();

  draw_borders();
  refresh();

  getch();
  endwin();
}



void draw_borders(){
  for (int i = 0; i < 50; i++){
      addstr("=--=");
  }
}
