#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_LEN 80

/*TODO free functions*/

int main(int argc, char* argv[]) {

    int ctr;

    /*
   for every file read from terminal
    
    */ 
    for (ctr=1; ctr < argc; ctr++){

        /*creating macro phase*/

        /*macro phase vars*/
        FILE* am_file, *src_file;
        char *p, *file_name;
        char cur_word[MAX_LEN], input[MAX_LEN];
        int mcro=0;
        struct Macro_Node* head = NULL;
        struct Macro_Node* head_ptr = NULL;
        File_Config * file_Config;

        /*open an am file*/
        make_am_name(argv[ctr], cur_word);
        file_name = argv[ctr];
        am_file = fopen(cur_word,"w+");
        src_file = fopen(file_name, "r");
        if (am_file == NULL) {printf("Error creating am file");}
        if (src_file == NULL) {printf("Error creating reading file");}



        /*start reading line by line*/
        while (fgets(input, MAX_LEN, src_file) != NULL) {
            printf("input is: %s\n", input);
            p = input;
            get_next_word(input,cur_word);
            printf("cur_word is: %s\n", cur_word);
            if (mcro == 1){
                /*checking end of macro def*/
                if (strcmp(cur_word,"endmcro") ==0){
                    printf("end of macro def\n");
                    mcro=0;
                }
                /* if we are inside a macro, insert the lines to macro content*/
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
            /* beginning of macro def*/
            else if(strcmp(cur_word,"mcro") == 0){
                printf("its a macro def\n");
                p = skip_spaces(p);
                p += strlen(cur_word);
                get_next_word(p,cur_word);
                printf("macro name is: %s\n", cur_word);
                insertMacro_Node(&head, cur_word);
                mcro=1;
            }
            /* regular line*/
            else{
                printf("regular line\n");
                fwrite(input, 1, strlen(input), am_file);
            }

        }

    file_Config = first_pass(am_file);

    }
    
    
    return 0;
}

