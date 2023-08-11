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
    if (!mark_entry_label(get_label_node_head(file_config), words[i], curr_line_num)) {
        update_validity_file_config(&file_config, FALSE);
    }

    free_words(words);
}


/* Description: Do the secound pass
   Input: A pointer to the current file_config, and am file name to read from.
*/
void second_pass(File_Config *file_config, char* am_file_name) {
    char input[MAX_LEN + 1];
    FILE* am_file;
    Ins_Node *ins_head;
    Lable_Node *lable_head;
    int ext_in_use;

    printf("\t---------START 2 PASS-----------\n");  /*DELETE*/
    am_file = fopen(am_file_name, "r");
    if (am_file == NULL) {
        ERROR_READING_FILE("am_file_name");
    } else { /*the file opened*/
        while (fgets(input, MAX_LEN, am_file) != NULL){ /*for each line in the file*/ 

            if (empty_line(input) || comment_line(input)){continue;} 

            if (is_data_storage_ins(input) || is_extern_ins(input)){continue;}

            /*if the line is entry*/
            if(is_type_ins(is_entry_word, input) == TRUE) { 
                handle_entry(file_config, input);
            }
        }

        /*go over the IC to update the binary words based on the lable adresses*/
        ins_head = get_file_ins_head(file_config);
        while(ins_head != NULL){
                if (get_ins_node_type(ins_head) == DIR){ /*encountered a lable line that doesnt have a bin adress since it wasnt known in first pass */
                    make_bin_DIR_word(&ins_head, file_config);
                }
                ins_head = get_ins_next(ins_head);
        } 

        /*check if the ext lables are used*/
        lable_head = get_label_node_head(file_config);
        while (lable_head != NULL){ 
            ext_in_use = FALSE;

            if (get_label_symbol_type(lable_head) == EXTERNAL){  /*for each extern lable*/

                ins_head = get_file_ins_head(file_config); /*search if used as param in ins list*/
                while(ins_head != NULL && ext_in_use != 1){
                    if (strcmp(get_label_name(lable_head), get_ins_label(ins_head)) == 0){
                        ext_in_use = TRUE;
                    }
                    ins_head = get_ins_next(ins_head);
                }
                
                if (ext_in_use == FALSE){
                    ERR_EXT_NOT_IN_USE(get_curr_line_number(file_config));
                    update_validity_file_config(&file_config, FALSE);   
                }
            }
            lable_head = get_label_next(lable_head);
        }

        fclose(am_file);
    }

    printf("\t---------END 2 PASS-----------\n"); /*DELETE*/

}
