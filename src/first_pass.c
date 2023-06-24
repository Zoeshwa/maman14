#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "first_pass.h"

#define MAX_LEN 80 /*TODO: maybe in the header?*/

/*TODO: update counters after handle*/
void first_pass() {
    /*initilazed varabels*/
    File_Config* file_config;
    char cur_word[MAX_LEN], input[MAX_LEN];
    Ins_Node *curr_ins;
    int line_num, is_line_have_symbol, is_line_data_ins; 
    char * ptr;

    line_num = 1;
    file_config = intialiez_file_config();
    curr_ins = NULL;

    /* TODO: change stind -> am_file) */    
    /*for each line in the file*/
    while (fgets(input, MAX_LEN, stdin) != NULL){    
        ptr = input;

        if (empty_line(input) || comment_line(input)){continue;}
        
        /*TODO: line counter update*/

        /*otherwise lines should be added*/
        add_ins_to_list(file_config->ins_head,curr_ins,file_config->IC_counter,line_num);
        
        /*get the first word*/
        get_next_word(cur_word, ptr);
        ptr = skip_spaces(ptr);

        is_line_have_symbol = is_lable(cur_word); /*label of the line*/    
        is_line_data_ins = is_data_storage_ins(input);/*ins: .data or .string*/
        
        if(is_line_data_ins) {
            if(is_line_have_symbol) {
                /*handle insert data symbol for the command*/
                handle_label(file_config, curr_ins, cur_word, DATA);
                
                /*get next words*/
                ptr += strlen(cur_word);
                get_next_word(cur_word, input);
                ptr = skip_spaces(ptr);
            }

            handle_data_ins(file_config, curr_ins, input, ptr);
            continue;

        } else if(is_scope_ins(input)) { /*.entry or .extranal*/
            
            if(is_line_have_symbol) {
                set_error_ins(curr_ins, FALSE, WARNING_LABEL_NOT_USE);
                ptr += strlen(cur_word);
                get_next_word(cur_word, input);
                ptr = skip_spaces(ptr);
            }

            if(is_extern_ins(input)) {
                handle_extren_line(file_config, curr_ins, input, ptr);
            }
            continue;

        } else{ /* is instruction*/
            if (is_line_have_symbol) {
                handle_label(file_config, curr_ins, cur_word, CODE);

                ptr += strlen(cur_word);
                get_next_word(cur_word, input);
                ptr = skip_spaces(ptr);
            }
            handle_code_line(file_config, curr_ins, input, ptr);
            continue;

        }
    }

    /*TODO: check if theres error. if so - print them and stop */
    /*TODO: else - update symbol of type data by addinig IC final value*/
    /*TODO: run secound pass*/
}

void handle_extren_line(File_Config* file_config, struct Ins_Node* curr_ins, char* line, char* curr_ptr) {
    char * ptr;
    char cur_word[MAX_LEN];
    int number_of_oprends;

    ptr = curr_ptr;
    number_of_oprends = 0;

    /*add to symbol table each label*/
    while (strlen(ptr) > 0) 
    {
        /*TODO: get params from the ins - with comma*/
        get_next_word(cur_word, ptr);
        ptr= skip_spaces(ptr);
        ptr =  ptr + strlen(cur_word);
        /*add the label to the symbol_table*/
        handle_label(file_config, curr_ins, cur_word, EXTERNALT);
        number_of_oprends++;
    }
    /*update the cur_ins*/
    update_extern_ins(curr_ins, number_of_oprends);
    /*TODO: add the params also to the ins?*/
}


void handle_code_line(File_Config* file_config, struct Ins_Node* curr_ins, char* line, char* curr_ptr) {
     
        /* TODO*/
        
}

void handle_data_ins(File_Config* file_config, struct Ins_Node* curr_ins, char* line, char* curr_ptr) {
     
        /* TODO: 7 in page 18 - handle data ins*/
        int counter, number_of_oprends, curr_value, is_char;
        char cur_word[MAX_LEN];

        counter = get_DC_counter(file_config);
        number_of_oprends = 0;

       /*which type of data*/
        is_char = is_type_storge_string_ins(line);

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


void handle_label(File_Config* file_config, struct Ins_Node* curr_ins, char* word, Symbol_Type symbol_type) { 
    int counter_value;
    /*validate the starting label*/
    if (!(is_valid_lable(file_config->symbol_table, word))) {
        set_error_ins(curr_ins, TRUE, ERROR_NOT_VALID_LABEL);
        /*MAYBE: we need to continou?*/
        return;
    }
    /*add to symbol table*/
    counter_value = get_counter_by_type(file_config, symbol_type);
    insert_to_symbol_table(file_config->symbol_table, word, counter_value, symbol_type); 
}





