#pragma once

#include <stdlib.h>
#include "time_parser.h"
#include <stdbool.h>
#include <time.h>
#include "file_reader.h"


/* ===============================
   Struct definitions
   =============================== */

typedef struct Item {
    struct Item* next;
    time_t due_date;
    char name[20];
} Item;

typedef struct Course {
    struct Course* next;
    char name[20];
    int list_size;
    Item* item_tail;
    Item* item_head;
} Course;

extern int clist_size;
extern Course* clist_head;

void create_course(Course* new_course);
void create_item(Item* new_item, Course* course, char* course_name);
bool is_new_course(char* name);
void print_course(char* course_name);
