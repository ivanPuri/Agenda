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
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

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
    // if (clist_head == NULL)
        node_link((void*) clist_tail, (void*) new_course, true);
    // else
    //     node_link((void*) , (void*) new_course);
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




