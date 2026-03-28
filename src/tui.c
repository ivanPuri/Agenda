#include <ncurses.h>
#include <linkedlist.h>

int H, W;
int cmd_h, cmd_w, cmd_y, cmd_x;


// =======================================================
// low level functions
// =======================================================

static char* second_win_input(WINDOW* win){
    char* input = (char*) malloc(30);
    int i = 0;

    while (true){
        char ch = wgetch(win);
        
        if (ch == '\n') {
            break;
        }
        if (i >= 29) return NULL;  // Leave room for null terminator
        input[i++] = ch;
    }
    input[i] = '\0';  // Null terminate the string
    return input;
}

static void add(WINDOW* win){
    wmove(win, 1, 1);
    waddstr(win, "Enter Course Name: ");
    wrefresh(win);
    char* course_name = second_win_input(win);
    
    if (!course_name){
        wmove(win, 1, 1);
        Course* course;

        if (is_new_course(course_name)){ // new course
            create_course(course, course_name);
        }

        waddstr(win, "Enter Assignment Name: ");
        char* item_name = second_win_input(win);

        Item* assignment;
        strcpy(assignment->name, item_name);

        create_item(assignment, course, item_name);
        free(item_name);
    }
    
}

static WINDOW* cmd_window(){
    cmd_h = 5;
    cmd_w = 50;
    cmd_y = (H - cmd_h) / 2;
    cmd_x = (W - cmd_w) / 2;
    
    WINDOW* win = newwin(cmd_h, cmd_w, cmd_y, cmd_x);
    if (!win) return NULL;
    keypad(win, TRUE);
    box(win, 0, 0);
    wrefresh(win);

    return win;
}

static void set_size(){
  getmaxyx(stdscr, H, W);
}

static void draw_borders(){
  for (int i = 0; i < W/4; i++){
      addstr("=--=");
  }

  move(H - 1, 0);
  for (int i = 0; i < W/4; i++){
      addstr("=--=");
  }

  refresh();
}

static void main_display(){
    int course_w = 3;
    int course_h = 2;
    int item_w = 4;
   
    move(course_h, course_w);
    for (Course* curr = clist_head; curr != NULL; curr = curr->next){
       
        attron(A_UNDERLINE);
        addstr(curr->name);
        attroff(A_UNDERLINE);
        addstr(": ");

        move(++course_h, item_w);
        for (Item* icurr = curr->item_head; icurr != NULL; icurr = icurr->next){
            
            addstr(icurr->name);
            addstr(", ");

            int buffer_size = 64;
            char* time_buffer[64];
            get_time(icurr, time_buffer, buffer_size);
            addstr(time_buffer);
            
            move(++course_h, item_w);
        }
        move(++course_h, course_w);
    }
}

static char* get_cmd(){
    char* cmd = (char*) malloc(30);
    int i = 0;


    while (true){
        char ch = getch();
        
        if (ch == '\n') {
            break;
        }
        if (i >= 29) return NULL;  // Leave room for null terminator
        cmd[i++] = ch;
    }
    cmd[i] = '\0';  // Null terminate the string
    return cmd;     
}

static void handle_cmd(char* cmd){
    WINDOW* center_win = cmd_window();
   
    if (strcmp(cmd, "add") == 0){ // add ui function
        add(center_win);
    }

    delwin(center_win);
    free(cmd);
} 

static bool handle_input(){
    int input = getch();
    clrtoeol();
    
    if (input == ':'){
        nodelay(stdscr, FALSE);  // Enable blocking input for command mode
        curs_set(1);
        char* cmd = get_cmd();
        if (cmd != NULL) {
            handle_cmd(cmd);
        }
        nodelay(stdscr, TRUE);  // Re-enable non-blocking for main loop
        curs_set(0);

    }else if (input == 'q'){
        return false;
    }

    return true;
}


// =======================================================
// high level functions
// =======================================================


void start_window(){
    initscr();
    cbreak();
    // noecho();
    curs_set(0);
    // keypad(stdscr, TRUE);      
    nodelay(stdscr, TRUE);   
    set_size();

    draw_borders();
    main_display();
    bool cond = true;
    move(H - 2, 0);
    while(cond){
        cond = handle_input();
    }




    getch();
    endwin();
}



