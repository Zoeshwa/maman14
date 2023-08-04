#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "first_pass.h"

void handle_entry(File_Config *file_config, char* line) {
    char *ptr, **words;
    int  i, curr_line_num, len;

    i = 0;
    curr_line_num = get_curr_line_number(file_config);

    ptr = line;
    words = get_words(ptr);
    len = get_len_words_array(words);

    /*get to the params*/  
    if(is_lable(words[i])) { /*if the first word is lable -> skip*/
        i++; 
        ptr = skip_next_word(line, ptr);
    }
    /*skip on the entry word*/
    i++; 
    ptr = skip_next_word(line, ptr);

    /*validate the params*/
    if(!is_legal_params(ptr, curr_line_num)) {
        update_validity_file_config(&file_config, FALSE);
        return;
    }

    /*validate the entry line - have one params*/
    if(len - i != 1) {
        update_validity_file_config(&file_config, FALSE);
        ERROR_MULTIPLE_ARGUMENTS(curr_line_num);
    }

    /*flag the label in the list to be entry*/
    if (!mark_entry_label(file_config->label_head, words[i], curr_line_num)) {
        update_validity_file_config(&file_config, FALSE);
    }

    free_words(words);
}

void second_pass(File_Config *file_config, char* am_file_name) {
    /*initilazed varabels*/
    char input[MAX_LEN];
    FILE* am_file;
    printf("\t---------START 2 PASS-----------\n");
    am_file = fopen(am_file_name, "r");

    /*for each line in the file*/
    while (fgets(input, MAX_LEN, am_file) != NULL){    
        printf("line: |%s|\n", input);

        if (empty_line(input) || comment_line(input)){continue;}

        if (is_type_storge_string_ins(input) || is_extern_ins(input)){continue;}

        /*if the line is entry*/
        if(is_type_ins(is_entry_word, input) == TRUE) { 
            printf("is entry\n");
            handle_entry(file_config, input);
        } else {

            /*if code func handle  - IDO*/
        }

    }
    fclose(am_file);

    printf("\t---------END 2 PASS-----------\n");

}
