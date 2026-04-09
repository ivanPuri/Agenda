#include "../headers/linkedlist.h"
#define FILE_NAME "ape.bin"
#define MAGIC "APE"

extern int clist_size;
extern Course* clist_head;
extern Course* clist_tail;

//==================================================
// LOW LEVEL FUNCTIONS
//==================================================


static FILE* get_fp(){
    FILE* fp = fopen(FILE_NAME, "r+b");
    if (fp != NULL) return fp;

    else {
        printf("fopen returned NULL: %s", FILE_NAME);        
        return NULL;
    }
}
 
static bool valid_magic(FILE* fp){
    fseek(fp, 0, SEEK_SET);
    char buffer[4];
    fread(buffer, sizeof(MAGIC) - 1 , 1, fp);  
    buffer[3] = '\0';

    //test
    // printf("buffer: %s\n",buffer);
    // printf(MAGIC);

    if (strcmp(buffer, MAGIC) == 0) return true;
    else return false;
}

static FILE* get_write_fp(){
    FILE* fp = fopen(FILE_NAME, "w+b");
    fwrite(MAGIC, 1, sizeof(MAGIC)-1, fp);
    bool valid = valid_magic(fp);
    if (valid) return fp;
    else return NULL;
}

static int get_num_courses(FILE* fp){
    int number_of_courses;
    fread(&number_of_courses, sizeof(int), 1, fp);
    return number_of_courses;  
}

//==================================================
// HIGH LEVEL FUNCTIONS
//==================================================

bool unload(int list_size){ // DO NOT write pointers 
    FILE* fp = get_write_fp();
    if (valid_magic(fp)){
        fwrite(&list_size, sizeof(int), 1, fp); // the total number of course nodes in the list 


        for(Course* curr = clist_head; curr != NULL; curr = curr->next){ // writing every course node
            fwrite(&curr->name, sizeof(curr->name), 1, fp);
            fwrite(&curr->list_size, sizeof(curr->list_size), 1, fp);
            for(Item* curr_item = curr->item_head; curr_item != NULL; curr_item = curr_item->next){ // writing every item node per course node
                fwrite(&curr_item->due_date, sizeof(curr_item->due_date), 1, fp);
                fwrite(&curr_item->name, sizeof(curr_item->name), 1, fp);
            }        
        }
        fclose(fp);
        return true;
    }
    fclose(fp);
    return false;
}

int load_in(){
    FILE* fp = get_fp();
    int num_courses;

    if (valid_magic(fp)){
        num_courses = get_num_courses(fp);
        Item* item;
        Course* tmp;

        for(int i = 0; i < num_courses; i++){
            Course* course = (Course*) calloc(1, sizeof(Course));
            
            if (i == 0) clist_head = course;

            fread(&course->name, 1, sizeof(course->name), fp);
            fread(&course->list_size, sizeof(course->list_size), 1, fp);
          
            if (i > 0) tmp->next = course;
            tmp = course;
            Item* itmp;
            
            for (int b = 0; b < course->list_size; b++){
                item = (Item*) calloc(1, sizeof(Item));
                
                if (b == 0){
                  course->item_head = item;
                  itmp = item;  
                } else {
                    itmp->next = item;
                    itmp = item;
                }

                fread(&item->due_date, sizeof(item->due_date), 1, fp);
                fread(&item->name, sizeof(item->name), 1, fp);
                
                if (b == course->list_size - 1) course->item_tail = item;
            }
            
            if (i == num_courses - 1) clist_tail = tmp;  // Set clist_tail to the last course loaded
        }
        
    }else 
        num_courses = -1;

    fclose(fp);
    return num_courses;
}

void start(void){
    FILE *fp = get_fp();
    // writing just the MAGIC characters, not the null terminator, hence -1
    fwrite(MAGIC, 1, sizeof(MAGIC)-1, fp);
    // bool valid = valid_magic(fp);
    // printf("valid: %i", valid);
    
    fclose(fp);


}