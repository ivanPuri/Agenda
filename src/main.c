#include <stdlib.h>
#include <stdarg.h>
#include "../headers/linkedlist.h"







// =======================================================
// low level functions
// =======================================================

static time_t valid_date(char* input_date){
    //"25 21:30";
    // time_t date = vtp(input_date);
    // if (date == (time_t) - 1)
    //     return (time_t) -1;
    // else
    //     return date;
}

// =======================================================
// high level functions
// =======================================================

Item* done(char* name){
    return NULL;
}

void add(char* name, char* course, char* due){

    time_t date = time(NULL);
    // if (date == (time_t) - 1){
    //     printf("invalid date: %s\n", due);
    //     return;
    // }//date is valid


    Item* new_item = (Item*) calloc(1, sizeof(Item));
    strcpy(new_item->name, name);
    new_item->due_date = date;


    if (is_new_course(course)){
       Course* new_course = (Course*) calloc(1, sizeof(Course));
       create_course(new_course, course);     
       create_item(new_item, new_course, course);
   }else{
       create_item(new_item, NULL, course);    
   } 
   print_course(course);
}

void edit(char* name){}

void display_item(char* course, char* name){}

void display_course(char* course){
    print_course(course);
}

void display_all(){}

/*
    int main(int argc, char** argv){
        if (argc == 1)
            display_all();
        else if(argc == 3){
            if (strcmp(argv[1], "edit") == 0)
                edit(argv[2]);
            else if(strcmp(argv[1], "done") == 0 )
                done(argv[2]);
            else if(strcmp(argv[1], "display") == 0)
                display_course(argv[2]);
        }else if (argc == 4){
            if (strcmp(argv[1], "display") == 0)
                display_item(argv[2], argv[3]);
        }else if (argc == 5){
            if (strcmp(argv[1], "add") == 0)
                add(argv[2], argv[3], argv[4]);
        }    

        return 0;
    }
*/
