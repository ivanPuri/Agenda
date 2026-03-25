#include "../headers/main.h"
#include "../headers/tui.h"

// this test is supposed to add 3 items all to different courses and then print the whole course_list
void test1(){ 
    char* assignment_name = "hw1";
    char* course_name = "449";
    char* date = "Monday";
    add(assignment_name, course_name, date);

    assignment_name = "hw2";
    course_name = "590";
    date = "Wednesday";
    add(assignment_name, course_name, date);

    assignment_name = "hw3";
    course_name = "1530";
    date = "Friday";
    add(assignment_name, course_name, date);

    printf("\n\nFINAL PRINT CHECK\n");
    print_all_courses();
}

//this test is going to add 3 items all in the same course and then display the course_list and the whole item list for that course
void test2(){
    char* assignment_name = "hw1";
    char* course_name = "449";
    char* date = "Monday";
    add(assignment_name, course_name, date);

    assignment_name = "hw2";
    course_name = "449";
    date = "Wednesday";
    add(assignment_name, course_name, date);

    assignment_name = "hw3";
    course_name = "449";
    date = "Friday";
    add(assignment_name, course_name, date);


    printf("\n\nFINAL PRINT CHECK\n");
    print_course(course_name);
}

//this test is going to write 3 items to 3 different courses 
void test3(){
    //course 1
    char* assignment_name = "hw1";
    char* course_name = "449";
    char* date = "July 14, 4:20 pm";
    add(assignment_name, course_name, date);

    assignment_name = "hw2";
    course_name = "449";
    date = "Wednesday";
    add(assignment_name, course_name, date);

    assignment_name = "hw3";
    course_name = "449";
    date = "Friday";
    add(assignment_name, course_name, date);

    //course 2
    assignment_name = "hw4";
    course_name = "590";
    date = "Monday";
    add(assignment_name, course_name, date);

    assignment_name = "hw5";
    course_name = "590";
    date = "Wednesday";
    add(assignment_name, course_name, date);

    assignment_name = "hw6";
    course_name = "590";
    date = "Friday";
    add(assignment_name, course_name, date);

    //course 3
    assignment_name = "hw7";
    course_name = "1530";
    date = "Monday";
    add(assignment_name, course_name, date);

    assignment_name = "hw8";
    course_name = "1530";
    date = "Wednesday";
    add(assignment_name, course_name, date);

    assignment_name = "hw9";
    course_name = "1530";
    date = "Friday";
    add(assignment_name, course_name, date);

    printf("\n\nFINAL PRINT CHECK\n");
    print_all_courses();
}

// this test is going to check the write to a file and the read from a file, 
//!DONT FORGET TO FREE ALL OF THE HEAP SPACE BEFORE YOU GO AND FUCK SOME SHIT UP
void test4(){
    start(); // function for getting the ape.bin magic written
    
    // test3(); // populating memory
    // unload(clist_size); 

    int size = load_in();

    // printf("size = %i\n\n\n", size);
    printf("\n\n\n\n MAIN PRINT CHECK\n");
    
    print_all_courses();
}


void test5(){
   start_window(); 
}



int main(int argc, char** argv){
    // load_in();
    test5();

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
