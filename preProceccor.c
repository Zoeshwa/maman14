#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "first_pass.h"

#define MAX_LEN 80


// Macro_Node in macro linked list
struct Macro_Node {
    char* name;
    char* content;
    int lines;
    struct Macro_Node* next;
};

// Function to insert a new Macro_Node at the beginning of the list
void insertMacro_Node(struct Macro_Node** head, char* name) {
    // Create a new Macro_Node
    struct Macro_Node* newMacro_Node = (struct Macro_Node*)malloc(sizeof(struct Macro_Node));
    // Allocate memory for the name and copy the string
    newMacro_Node->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newMacro_Node->name, name);
    newMacro_Node->content = (char*)malloc(MAX_LEN*sizeof(char));
    int lines =0;
    newMacro_Node->next = NULL;

    // If the list is empty, make the new Macro_Node the head of the list
    if (*head == NULL) {
        *head = newMacro_Node;
    } else {
        // Otherwise, insert the new Macro_Node at the beginning
        newMacro_Node->next = *head;
        *head = newMacro_Node;
    }
}

/* gets a pointer and moves it forward untill reaches non white char */
char* skip_spaces(char* p){
	while (*p == ' ' || *p == '	'){
		p++;
	}
	return p;
}

char* get_next_word(char* str, char* word, char* ptr){
    int i=0;
    ptr = skip_spaces(ptr);
    while(*ptr != '\n' && *ptr != EOF && *ptr != ' ' && *ptr != '\t'){
        word[i] = *ptr;
        i++;
        ptr++;
    }
    word[i] = '\0';
return word;
}


void make_am_name(char* file, char* name){
    int i =0;
    while (*file != '.'){
         name[i] = *file;
         i++;
         file++;
    }
    name[i++] = '.';
    name[i++] = 'a';
    name[i++] = 'm';
    name[i] = '\0';
}

void update_macro_contect(struct Macro_Node** head, char* line){
    (*head)->lines += 1;
    (head)->content = (char)realloc((head)->content, MAX_LEN(*head)->lines*sizeof(char));
    //first insertion of content
    if ((*head)->lines == 1){(*head)->content[0] = '\0';}
    line = skip_spaces(line);
    strcat( (*head)->content, line);
    printf("macro contect is: %s\n", (*head)->content );
}

struct Macro_Node* search_macro_list(struct Macro_Node* head, char* name) {
    struct Macro_Node* current = head;

    // Traverse the list and search for the target value
    while (current != NULL) {
        if (strcmp(current->name,name) == 0) {
            printf("found in macro list. macro %s\n", current->name);
            return current;  // Found the value, return the Macro_Node
        }
        current = current->next;
    }
    printf("not in macro list\n");
    return NULL;  // Value not found, return NULL
}

// update_data_list ( ){
//                     if (Data_head = NULL){ //first line
//                         insertIns_Node(&Data_head, DC);
//                         cur_Data = Data_head;
//                     }
//                     else{ // any other line
//                         DC +=1;
//                         insertIns_Node(&cur_Data, DC);
//                     }

// }

void main(int argc, char* argv[]){
    int ctr;

    // for every file read from terminal
    for (ctr=1; ctr < argc; ctr++){

        //first pass phase



        //macro phase vars
        FILE* am_file, *src_file;
        char *p, *file_name;
        char cur_word[MAX_LEN], input[MAX_LEN];
        int mcro=0;

        //open an am file
        make_am_name(argv[ctr], cur_word);
        file_name = argv[ctr];
        am_file = fopen(cur_word,"w+");
        src_file = fopen(file_name, "r");
        if (am_file == NULL) {printf("Error creating am file");}
        if (src_file == NULL) {printf("Error creating reading file");}
        struct Macro_Node* head = NULL;
        struct Macro_Node* head_ptr = NULL;


        //start reading line by line
        while (fgets(input, MAX_LEN, src_file) != NULL){
            printf("input is: %s\n", input);
            p = input;
            get_next_word(input,cur_word, p);
            printf("cur_word is: %s\n", cur_word);
            if (mcro == 1){
                //checking end of macro def
                if (strcmp(cur_word,"endmcro") ==0){
                    printf("end of macro def\n");
                    mcro=0;
                }
                // if we are inside a macro, insert the lines to macro content
                else{
                    printf("updating macro contect\n");
                    update_macro_contect(&head, input);
                }
                continue;
            }
            head_ptr = search_macro_list(head, cur_word);
            if (head_ptr != NULL){
                printf("found in macro list, writing content to file\n");
                fwrite(head_ptr->content, 1, strlen(head_ptr->content), am_file);
            }
            // beginning of macro def
            else if(strcmp(cur_word,"mcro") == 0){
                printf("its a macro def\n");
                p = skip_spaces(p);
                p += strlen(cur_word);
                get_next_word(input,cur_word, p);
                printf("macro name is: %s\n", cur_word);
                insertMacro_Node(&head, cur_word);
                mcro=1;
            }
            // regular line
            else{
                printf("regular line\n");
                fwrite(input, 1, strlen(input), am_file);
            }

        }

        int IC = 100;
        int DC = 0;
        int line_num = 1;
        struct Ins_Node* lines_head = NULL;
        struct Ins_Node* cur_line = NULL;

        struct Lable_Node* Lables_head = NULL;

        struct Data_Node* Data_head = NULL;
        struct Data_Node* cur_Data = Data_head;       

        //first pass
        while (fgets(input, MAX_LEN, am_file) != NULL){        
            
            p = input;
            char* lable = NULL;
            

            if (empty_line(input) || comment_line(input)){continue;}

            //otherwise lines should be added
            if (lines_head == NULL){ //first line
                insertIns_Node(&lines_head, IC, line_num);
                cur_line = lines_head;
            }
            else{ // any other line
                IC += 1;
                insertIns_Node(&cur_line, IC, line_num);
            }
            
            get_next_word(input,cur_word, p);
            p = skip_spaces(p);

            if (is_lable(cur_word)){
                if (!(is_valid_lable(cur_word))) {
                    cur_line->error = 1;
                    update_error(&cur_line, "not a valid lable\n");
                    continue;
                }
                lable = (char*)malloc((strlen(cur_word)) * sizeof(char));
                strcpy(lable, cur_word);
                p += strlen(cur_word);
                get_next_word(input,cur_word, p);
                p = skip_spaces(p);
            }
            
            if (is_data(cur_word)){ // .data, .extern or .string .entry
                insertLable_Node(&Lables_head, lable, DC ,cur_word, "D"); //1 is for DC 0 for IC
                p = skip_spaces(p);
                DC = update_data_list(cur_Data, p, input, DC);
                continue;
            }
            else{ // is instruction
                if (lable != NULL){
                    insertLable_Node(&Lables_head, lable, DC , 1); //1 is for DC 0 for IC
                }
                cur_line = update_Ins_list(cur_line, p, input, IC);

            }


         
        
        
        
        }    

    }

}