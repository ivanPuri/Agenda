#include <stdbool.h>
#include "../headers/time_parser.h"
#include "../headers/file_reader.h"




int clist_size = 0;
Course* clist_head = NULL;


//==================================================
// low level functions
//==================================================
static void read_from_file(){
    clist_size = load_in();
}

static void write_to_file(){
    bool status = unload(clist_size);
    if (!status) printf("write to file failed");
}

static void node_link(void* A, void* B, bool is_course) {
    if (is_course){
        Course* a = (Course*) A;  
        Course* b = (Course*) B;  
        
        if (a == NULL) // if A is NULL
                a = b;
            else{
                if (B != NULL){// A and B are valid
                   b->next = a->next;
                   a->next = b;
                }
        }
    }else{
        Course* a = (Course*) A;
        Item* b = (Item*) B;
        
        if (a->item_head == NULL) 
            a->item_head = b;
        else{
            b->next = a->item_tail->next;
            a->item_tail->next = b->next;
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
    node_link((void*) course, (void*) new_item, false);        
}

//==================================================
// High level functions
//==================================================


void create_course(Course* new_course){
    node_link((void*) clist_head, (void*) new_course, true);
    clist_size++;
}

void create_item(Item* new_item, Course* course, char* course_name){
    if (course != NULL){
        if (course->item_tail == NULL){
                course->item_head = new_item;
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
        printf("Course Name, %s, Not Found!", course_name);
    else{
       int i = 0;
       printf("== = == = == = == = == = - %s - = == = == = == = == = ==", course_name);
       for(Item* item = course->item_head; item != NULL; item = item->next){
            printf("Entry %d: %s",i++, item->name);
       } 
    }
}
