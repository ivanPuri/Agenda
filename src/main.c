#include <stdlib.h>
#include <stdarg.h>
#include "../headers/linkedlist.h"
#include "../headers/tui.h"
#include <Python.h>





// =======================================================
// low level functions
// =======================================================

static void read_from_file(){
    clist_size = load_in();
}

static void write_to_file(){
    bool status = unload(clist_size);
    if (!status) printf("write to file failed");
}

static time_t valid_date(char* input_date){

    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    time_t result_time = (time_t)-1;
    
    Py_Initialize();
    // Add src/ to Python path
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("src"));
    Py_DECREF(sys);
    Py_DECREF(path);
    pName = PyUnicode_FromString("parses");
    pModule = PyImport_Import(pName);
    
    if (pModule == NULL) {
        PyErr_Print();
        Py_DECREF(pName);
        return (time_t)-1;
    }
    
    pFunc = PyObject_GetAttrString(pModule, "parse_user_datetime_dateparser");
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(input_date));
    
    pValue = PyObject_CallObject(pFunc, pArgs);
    
    if (pValue != NULL) {
        result_time = (time_t)PyLong_AsLong(pValue);
        Py_DECREF(pValue);
    } else {
        PyErr_Print();
    }
    
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);
    Py_DECREF(pModule);
    Py_DECREF(pName);
    
    return result_time;
}

// =======================================================
// high level functions
// =======================================================


void add_assignment(char* name, char* course, char* due){

    time_t date = valid_date(due);
    if (date == (time_t) - 1){
        printf("invalid date: %s\n", due);
        return;
    }//date is valid


    Item* new_item = (Item*) calloc(1, sizeof(Item));
    strcpy(new_item->name, name);
    new_item->due_date = date;
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

void display_course(char* course){
    print_course(course);
}

void display_all(){
    print_all_courses();
}

int main(int argc, char** argv){

    read_from_file();
    if (argc == 1)
        start_window();
    else if(argc == 2){
       // if (strcmp(argv[1], "status") == 0)
            //display_all();
    }else if (argc == 3){
        if (strcmp(argv[1], "-d") == 0)
            display_course(argv[2]);
    }
    display_all();
    write_to_file();

    return 0;
}
