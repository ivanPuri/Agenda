#include <stdbool.h>
#include "../headers/file_reader.h"




int clist_size = 0;
Course* clist_head = NULL;
Course* clist_tail = NULL;


//==================================================
// low level functions
//==================================================

static void get_str_from_time(time_t t, char* buffer, size_t size){
    struct tm *tm_info = localtime(&t);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S\0", tm_info);
}

static void node_link(void* A, void* B, bool is_course) {
    if (is_course){
        Course* a = (Course*) A;  
        Course* b = (Course*) B;  
        
        if (a == NULL){// if A is NULL
            clist_head = b;
            clist_tail = b;
        }else{
            if (b != NULL){// A and B are valid
                clist_tail->next = b;
                clist_tail = b;
            }
        }
    }else{
        Course* a = (Course*) A;
        Item* b = (Item*) B;
        
        if (a == NULL) { // list is empty
            a->item_head = b;
            a->item_tail = a->item_head;
        }else{ // list is not empty
            a->item_tail->next = b;
            a->item_tail = b;
        }
    }
    
}

static void node_unlink(void* A, void* B, bool is_course){
    if (is_course){
        // Course* b = (Course*) B;
        
        // // If unlinking the head, move head to next
        // if (clist_head == b) {
        //     clist_head = b->next;
        // } else {
        //     // Find previous course and bypass b
        //     for (Course* curr = clist_head; curr != NULL; curr = curr->next) {
        //         if (curr->next == b) {
        //             curr->next = b->next;
        //             break;
        //         }
        //     }
        // }
        
        // // If unlinking the tail, find new tail
        // if (clist_tail == b) {
        //     clist_tail = NULL;
        //     for (Course* curr = clist_head; curr != NULL; curr = curr->next) {
        //         clist_tail = curr;
        //     }
        // }
    }else{
        Course* a = (Course*) A;
        Item* b = (Item*) B;
        
        // If unlinking the head item, move head to next
        if (a->item_head == b) {
            a->item_head = b->next;
        } // If unlinking the tail item, find new tail
        else if (a->item_tail == b) {
            // a->item_tail = NULL;
            for (Item* curr = a->item_head->next; curr != NULL; curr = curr->next) {
                if (curr->next == b){
                    curr->next = NULL;
                    a->item_tail == NULL;
                    break;
                }

            }
        } else {
            // Find previous item and bypass b
            for (Item* curr = a->item_head; curr != NULL; curr = curr->next) {
                if (curr->next == b) {
                    curr->next = b->next;
                    break;
                }
            }
        }
        
        
    }
}

static Course* get_course_node(char* course_name){
    for (Course* curr = clist_head; curr != NULL; curr = curr->next){
        if (strcmp(curr->name, course_name) == 0)
            return curr; 
    }
    return NULL;
}

static void add_item(Item* new_item, Course* course){
    node_link( course,  new_item, false); 
    course->list_size++;    
}

static void print_course_iterate(Course* course){
    int i = 1;
    printf("== = == = == = == = == = - %s - = == = == = == = == = ==\n", course->name);
    for(Item* item = course->item_head; item != NULL; item = item->next){
        char buffer[64];
        get_str_from_time(item->due_date, buffer, sizeof(buffer));
        printf("Entry %d: %s -=- Due: %s \n", i++, item->name, buffer);
    } 
}


//==================================================
// High level functions
//==================================================

void create_course(Course* new_course, char* course_name){
    strcpy(new_course->name, course_name);
    if (clist_head == NULL)
        node_link((void*) clist_head, (void*) new_course, true);
    else
        node_link((void*) clist_tail, (void*) new_course, true);
    clist_size++;
}

void create_item(Item* new_item, Course* course, char* course_name){
    if (course != NULL){
        if (course->item_head == NULL){
                course->item_head = new_item;
                course->item_tail = course->item_head;
                course->list_size++;
        }else{
                add_item(new_item, course);   
        }
    }else{//assume it will always find it 
        Course* cp = get_course_node(course_name);
        add_item(new_item, cp);
    }

    return;
        
}

bool is_new_course(char* name){
    Course* course = get_course_node(name);
    if (course == NULL)
        return true;
    else
        return false;
}

void print_course(char* course_name){
    Course* course = get_course_node(course_name);
    if (course == NULL)
        printf("Course Name, %s, Not Found!\n", course_name);
    else{
       print_course_iterate(course);
    }
}

void print_all_courses(){

    if (clist_head == NULL) printf("list empty");
    else{
        for (Course* curr = clist_head; curr != NULL; curr = curr->next){
            print_course_iterate(curr);
            puts("\n");
        }
    }
}

char* get_time(Item* item, char* buffer, int size){
    get_str_from_time(item->due_date, buffer, size);
    return buffer;
}

Item* get_item(char* item_name, char* course_name){
    Course* course = get_course_node(course_name);
    for (Item* curr = course->item_head; curr != NULL; curr = curr->next){
        if (strcmp(curr->name, item_name) == 0 ){
            return curr;
        }
    }
    return NULL;
}

void remove_item(char* course_name, Item* item){
    node_unlink(get_course_node(course_name), item, false);
    free(item);
}

