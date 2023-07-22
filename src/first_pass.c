#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "first_pass.h"

#define MAX_LEN 80 /*TODO: maybe in the header?*/

File_Config* first_pass(FILE* am_file) {
    /*initilazed varabels*/
    File_Config* file_config;
    char input[MAX_LEN];

    file_config = intialiez_file_config();

    /*for each line in the file*/
    while (fgets(input, MAX_LEN, am_file) != NULL){    

        if (empty_line(input) || comment_line(input)){continue;}
        handle_new_line(file_config, input);
        file_config->curr_line_num++;
    }

    /*checks if needs to continue process since it might have an error*/
    if (file_config->is_valid){
        /*TODO:*/
        update_symbol_table_by_IC(file_config);
    }
    return file_config;
}

void handle_new_line(File_Config* file_config, char* line) {
    char * ptr;
    char cur_word[MAX_LEN];
    int is_line_have_symbol; 
    ptr = line;
    /*get the first word*/
    get_next_word(cur_word, ptr);
    ptr = skip_spaces(ptr);

    is_line_have_symbol = is_lable(cur_word); /*label of the line*/    
    
    if(is_data_storage_ins(line)) { /*ins: .data or .string*/
        if(is_line_have_symbol) {
            /*handle insert data symbol for the command*/
            handle_label(file_config, cur_word, DATA);
            
            /*get next words*/
            ptr += strlen(cur_word);
            get_next_word(cur_word, line);
            ptr = skip_spaces(ptr);
        }

        handle_data_ins(file_config, line, ptr);
        return;

    } else if(is_external_or_entry_ins(line)) { /*.entry or .extranal*/
        
        /*insert symbol with type*/
        if(is_line_have_symbol) {
            ptr += strlen(cur_word);
            get_next_word(cur_word, ptr);
            ptr = skip_spaces(ptr);
        }

        if(is_extern_ins(line)) {
            handle_extren_line(file_config, line, ptr);
        }
        return ;

    } else{ /* is instruction*/
        if (is_line_have_symbol) {
            handle_label(file_config, cur_word, CODE);
            ptr += strlen(cur_word);
            get_next_word(cur_word, ptr);
            ptr = skip_spaces(ptr);
        }

        handle_code_line(file_config, line, ptr);
        return ;
    }
}

void handle_extren_line(File_Config* file_config, char* line, char* curr_ptr) {
    char *ptr, **words;
    char cur_word[MAX_LEN];
    int  i;

    ptr = curr_ptr;
    ptr = skip_spaces(ptr);

    /*add to symbol table each label*/
    /*get the params as words array*/
    words = (char**)malloc(MAX_LEN * sizeof(char*));
    
    /*TODO
    parsing_ido(words, &len, curr_ptr);
*/
    for(i = 0; words[i] != NULL; i++) {
        handle_label(file_config, cur_word, EXTERNAL);
    }

}


void handle_code_line(File_Config* file_config, char* line, char* curr_ptr) {
    /* 
    add_ins_to_list(file_config->ins_head,file_config->IC_counter);
*/
        /* TODO*/
        
}

void handle_data_ins(File_Config* file_config, char* line, char* curr_ptr) {
     
        /* TODO: 7 in page 18 - handle data ins*/
        int counter;
        char cur_word[MAX_LEN];
        /*
        char **params;
        
        Data_Type data_type;
        */

        counter = get_DC_counter(file_config);

        /*get the the first word*/
        /*which type of data
        if(is_data_word(cur_word)) {
            data_type = DATA;
        } else {
            data_type = STRING;
        }
*/
        /*get the params
        parsing_ido(params, curr_ptr);

*/
        /*TODO: update data table*/
        while (strlen(curr_ptr) > 0)
        {
            /*TODO: get params from the ins - with comma*/

            /*next word*/
            get_next_word(cur_word, curr_ptr);
            curr_ptr= skip_spaces(curr_ptr);
            curr_ptr =  curr_ptr + strlen(cur_word);
            
            /*TODO: validate data*/

            /*TODO: convert to int*/

            /*add to DATA table TODO: value set
            counter += number_of_oprends;
            add_data_node_to_table(file_config->data_table, value, is_char, counter);
            number_of_oprends++;
            
            */
        }
        

        /*TODO: update ins*/

        /*update DC_counter*/
        set_file_config_DC(file_config, counter);
}

/*Description: givien a word - check if its legal lable and insert to the lable list if needed*/
/*Input: file_config for the current file, word to handle, type of the lable*/
void handle_label(File_Config* file_config, char* word, Symbol_Type symbol_type) { 
    int counter_value;

    /*validate the starting label*/
    if (!(is_valid_lable(file_config->label_head, word))) {
        PRINT_NUM_LINE_ERROR(file_config->curr_line_num);
        /*ASK: we need to continou?*/
        return;
    }
    /*add to symbol table - get the counter and remove colon*/
    counter_value = get_counter_by_type(file_config, symbol_type);
    remove_colon_at_end(word);

    insert_to_symbol_table(&(file_config->label_head), word, counter_value, symbol_type);
}


/*TODO: */
void update_symbol_table_by_IC(File_Config * file_config) {

}

