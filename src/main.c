#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_LEN 80

void run_first_pass(char* input) {
    
        char * pointer;
        char cur_word[MAX_LEN];

        
        int IC_counter, DC_counter, line_num, is_line_have_symbol, is_line_data_ins;
        struct Ins_Node *ins_head, *curr_ins;
        /*
        struct Data_Node *Data_head, *cur_Data;*/ 
        /*
        Lable_Node* Lables_head;
        */    
        Symbol_Table* symbol_table;


        line_num = 1;
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
            
            /*get the first word in the line*/
            /*FIX*/
            get_next_word_old(input,cur_word, pointer);
            pointer = skip_spaces(pointer);

            is_line_have_symbol = is_lable(cur_word);
            /*TODO - also get next word if the first is symbol*/
            is_line_data_ins = is_data_storage_ins(input);/*.data or .string*/
            
            if(is_line_data_ins) {
                if(is_line_have_symbol) {
                    if (!(is_valid_lable(symbol_table, cur_word))) {
                        curr_ins->is_error = TRUE;
                        update_error(&curr_ins, "not a valid lable\n");
                        continue;
                }
                insert_to_symbol_table(symbol_table, cur_word, DC_counter , DATA); 
                
                pointer += strlen(cur_word);
                get_next_word_old(input,cur_word, pointer);
                pointer = skip_spaces(pointer);
                /* TODO: 7 in page 18 - handle data ins
                DC = update_data_list(cur_Data, pointer, input, DC);
                */
                continue;
                }
            } else if(is_scope_ins(input)) { /*.entry or .extranal*/
                if(is_extern_ins(input)) {

                    /*TODO: handle extren struct*/
                }
                continue;
            } else{ /* is instruction*/
                if (is_line_have_symbol) {
                    if (!(is_valid_lable(symbol_table, cur_word))) {
                        curr_ins->is_error = TRUE;
                        update_error(&curr_ins, "not a valid lable\n");
                        continue;
                    }
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





int main(int argc, char* argv[]){

    run_tester();

    return 0;
    }

