#include "../headers/main.h"


// this test is supposed to add 3 items all to different courses and then print the whole course_list
void test1(){ 
    char* assignment_name = "hw1";
    char* course_name = "449";
    char* date = "Monday";
    add(assignment_name, course_name, date);

    char* assignment_name = "hw1";
    char* course_name = "590";
    char* date = "Wednesday";
    add(assignment_name, course_name, date);

    char* assignment_name = "hw1";
    char* course_name = "1530";
    char* date = "Friday";
    add(assignment_name, course_name, date);

}



//this test is going to add 3 items all in the same course and then display the course_list and the whole item list for that course
void test2(){}

//this test is going to write 3 items to 3 different courses and then write to a file, it will then set clist_head to NULL and read from the file and display the new list. DONT FORGET TO FREE ALL OF THE HEAP SPACE BEFORE YOU GO AND FUCK SOME SHIT UP
void test3(){}



int main(int argc, char** argv){

    test1();

    // if (argc == 1)
    //     display_all();
    // else if(argc == 3){
    //     if (strcmp(argv[1], "edit") == 0)
    //         edit(argv[2]);
    //     else if(strcmp(argv[1], "done") == 0 )
    //         done(argv[2]);
    //     else if(strcmp(argv[1], "display") == 0)
    //         display_course(argv[2]);
    // }else if (argc == 4){
    //     if (strcmp(argv[1], "display") == 0)
    //         display_item(argv[2], argv[3]);
    // }else if (argc == 5){
    //     if (strcmp(argv[1], "add") == 0)
    //         add(argv[2], argv[3], argv[4]);
    // }    

    return 0;
}
