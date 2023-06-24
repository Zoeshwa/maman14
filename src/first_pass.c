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
        
        /*otherwise lines should be added*/
        add_ins_to_list(file_config->ins_head,curr_ins,file_config->IC_counter,line_num);
        
        /*get the first word*/
        get_next_word(cur_word, ptr);
        ptr = skip_spaces(ptr);

        is_line_have_symbol = is_lable(cur_word); /*label of the line*/
        
        
        if(is_line_have_symbol) {
            /*validate the starting label*/
            if (!(is_valid_lable(file_config->symbol_table, cur_word))) {
                set_error_ins(curr_ins, TRUE, ERROR_NOT_VALID_LABEL);
                continue;
            }
        }
    
        is_line_data_ins = is_data_storage_ins(input);/*ins: .data or .string*/
        
        if(is_line_data_ins) {
        /*inset symbol*/
            if(is_line_have_symbol) {
                /*handle insert data symbol for the command*/
                handle_label(file_config, curr_ins, cur_word, DATA);
            }
            /*get next words*/
            ptr += strlen(cur_word);
            get_next_word_old(input, cur_word, ptr);
            ptr = skip_spaces(ptr);

            handle_data_ins(file_config, curr_ins, input, ptr);
            continue;

        } else if(is_scope_ins(input)) { /*.entry or .extranal*/

            if(is_line_have_symbol) {
                set_error_ins(curr_ins, FALSE, WARNING_LABEL_NOT_USE);
            }

            if(is_extern_ins(input)) {
                handle_extren_line(file_config, cur_word, input, ptr);
            }
            continue;

        } else{ /* is instruction*/
            if (is_line_have_symbol) {
                handle_label(file_config, curr_ins, cur_word, CODE);

                ptr += strlen(cur_word);
                get_next_word_old(input,cur_word, ptr);
                ptr = skip_spaces(ptr);

                handle_code_line(file_config, cur_word, input, ptr);
                continue;
            }

        }
    }

    /*TODO: check if theres error. if so - print them and stop */
    /*TODO: else - update symbol of type data by addinig IC final value*/
    /*TODO: run secound pass*/
}


void run_first_pass(char* input) {
    
        char * pointer;
        char cur_word[MAX_LEN];

        File_Config* file_config;


        
        int IC_counter, DC_counter, line_num, is_line_have_symbol, is_line_data_ins;
        struct Ins_Node *ins_head, *curr_ins;
        File_Config* file_config;
        /*
        struct Data_Node *Data_head, *cur_Data;*/ 
        /*
        Lable_Node* Lables_head;
        */    
        Symbol_Table* symbol_table;

        file_config = intialiez_file_config();
        line_num = 1;
        /*TODO: delete*/
        IC_counter = 100;
        DC_counter = 0;
        ins_head = NULL;
        curr_ins = NULL;
        /*
            Data_head = NULL;
        */
        /*
        cur_Data = Data_head;
        Lables_head = NULL;
        */
        symbol_table = intialiez_symbol_table();


        /*first pass*/
        /*
        while (fgets(input, MAX_LEN, am_file) != NULL){    
            */    
        while (fgets(input, MAX_LEN, stdin) != NULL){    
            pointer = input;

            if (empty_line(input) || comment_line(input)){continue;}

            /*otherwise lines should be added*/
            add_ins_to_list(ins_head,curr_ins,IC_counter,line_num);
        
            /*get the first word*/
            get_next_word(cur_word, pointer);
            pointer = skip_spaces(pointer);

            is_line_have_symbol = is_lable(cur_word); /*label of the line*/
            
            
            if(is_line_have_symbol) {
                /*validate the starting label*/
                if (!(is_valid_lable(symbol_table, cur_word))) {
                    set_error_ins(curr_ins, TRUE, ERROR_NOT_VALID_LABEL);
                    continue;
                }
            }
            is_line_data_ins = is_data_storage_ins(input);/*ins: .data or .string*/
            
            if(is_line_data_ins) {
                /*inset symbol*/
                if(is_line_have_symbol) {
                    /*handle insert data symbol for the command*/
                    handle_label(file_config, curr_ins, cur_word, DATA);
                    /* TODO: delete
                    insert_to_symbol_table(symbol_table, cur_word, DC_counter , DATA);
                    */ 
                    /*get next words*/
                    pointer += strlen(cur_word);
                    get_next_word_old(input,cur_word, pointer);
                    pointer = skip_spaces(pointer);
                    /* TODO: 7 in page 18 - handle data ins
                    DC = update_data_list(cur_Data, pointer, input, DC);
                    */
                    continue;
                }
            } else if(is_scope_ins(input)) { /*.entry or .extranal*/
                if(is_line_have_symbol) {
                    set_error_ins(curr_ins, FALSE, WARNING_LABEL_NOT_USE);
                }

                if(is_extern_ins(input)) {
                    /*TODO: handle extren struct*/
                    handle_extren_line(file_config, cur_word, input, pointer);
                }
                continue;
            } else{ /* is instruction*/
                if (is_line_have_symbol) {
                    insert_to_symbol_table(symbol_table, cur_word, IC_counter , CODE); 
                    pointer += strlen(cur_word);
                    get_next_word_old(input,cur_word, pointer);
                    pointer = skip_spaces(pointer);
                    /* TODO: handle ins
                    curr_ins = update_Ins_list(curr_ins, pointer, input, IC);
                    */
                    continue;
                }

            }
        
        }    
}

void handle_extren_line(File_Config* file_config, struct Ins_Node* curr_ins, char* line, char* curr_ptr) {
    char * ptr;
    char cur_word[MAX_LEN];

    ptr = curr_ptr;
    /*update the cur_ins */

    /*add to symbol table each label*/
    while (strlen(ptr) > 0) 
    {
        get_next_word(cur_word, ptr);
        ptr= skip_spaces(ptr);
        ptr =  ptr + strlen(cur_word);
        /*add the label to the symbol_table*/
        handle_label(file_config, curr_ins, cur_word, EXTERNALT);
    }
    /*TODO....*/
}


void handle_code_line(File_Config* file_config, struct Ins_Node* curr_ins, char* line, char* curr_ptr) {
     
        /* TODO*/
        
}

void handle_data_ins(File_Config* file_config, struct Ins_Node* curr_ins, char* line, char* curr_ptr) {
     
        /* TODO: 7 in page 18 - handle data ins
            DC = update_data_list(cur_Data, pointer, input, DC);
        */
        
}


void handle_label(File_Config* file_config, struct Ins_Node* curr_ins, char* word, Symbol_Type symbol_type) { 
    int counter_value;
    /*validate the starting label*/
    if (!(is_valid_lable(file_config->symbol_table, word))) {
        set_error_ins(curr_ins, TRUE, ERROR_NOT_VALID_LABEL);
        return;
    }
    /*add to symbol table*/
    counter_value = get_counter_by_type(file_config, symbol_type);
    insert_to_symbol_table(file_config->symbol_table, word, counter_value, symbol_type); 
}





