#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "first_pass.h"

void second_pass(File_Config **file_config, FILE* am_file) {

    /*initilazed varabels*/
    char input[MAX_LEN];
    char curr_word[MAX_LEN];
    char * ptr;

    printf("\t---------START 2 PASS-----------\n");

    /*for each line in the file*/
    while (fgets(input, MAX_LEN, am_file) != NULL){    
        printf("\tline %d: %s\n", get_curr_line_number(file_config), input);
        
        if (empty_line(input) || comment_line(input)){continue;}

        if (is_type_storge_string_ins(input) || is_extern_ins(input)){continue;}

        /*if the line is entry*/
        if(is_type_ins(is_entry_word, curr_word) == TRUE) { 
            handle_entry(file_config, input);
        } else {

            /*if code func handle  - IDO*/
        }
    }

    printf("\t---------END 2 PASS-----------\n");

}
