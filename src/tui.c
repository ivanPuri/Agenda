#include <ncurses.h>
#include <linkedlist.h>

int H, W;


void set_size(){
  getmaxyx(stdscr, H, W);

}

void draw_borders(){
  for (int i = 0; i < W/4; i++){
      addstr("=--=");
  }

  move(H - 1, 0);
  for (int i = 0; i < W/4; i++){
      addstr("=--=");
  }

  refresh();
}

void main_display(){
    int course_w = 3;
    int course_h = 2;
    attron(A_UNDERLINE);
    mvprintw(course_h - 1, course_w, "COURSES :");
    mvprintw(course_h - 1, course_w + 15, "ASSIGNMENTS :");
    attroff(A_UNDERLINE);

    move(course_h, course_w);
    for (Course* curr = clist_head; curr != NULL; curr = curr->next){
        addstr(curr->name);
        addstr(": \t  ");
        for (Item* icurr = curr->item_head; icurr != NULL; icurr = icurr->next){
            addstr(icurr->name);
            addstr(", ");
        }
        move(++course_h, course_w);
    }
}

void start_window(){
  initscr();

  set_size();
  draw_borders();
  main_display();

  getch();
  endwin();
}


