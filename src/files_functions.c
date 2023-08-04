#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_functions.h"


File_Config* intialiez_file_config() {
    File_Config* file_config;
    file_config = (File_Config*)malloc(sizeof(File_Config));
    file_config->label_head = NULL;

    file_config->ins_head = insert_ins_head();
    file_config->ins_tail = file_config->ins_head;

    file_config->data_head = NULL;
    file_config->data_tail = file_config->data_head;

    file_config->curr_line_num = 1;
    file_config->is_valid = TRUE;
    file_config->DC_counter = 0;
    file_config->IC_counter = 100; 
    return file_config;
}

int get_curr_line_number(File_Config* file_config){
    return file_config->curr_line_num;
}

int get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type) {
    int counter_value;

    switch (symbol_type)
    {
        case EXTERNAL:
            counter_value = 0;
            break;
        case CODE:
            counter_value = file_config->IC_counter; 
            break;
        case DATA:
            counter_value = file_config->DC_counter; 
            break;
        
        default:
            counter_value = -1;
            break;
    }

    return counter_value;
}

int get_DC_counter(File_Config* file_config) {
    return file_config->DC_counter;
}

int get_IC_counter(File_Config* file_config) {
    return file_config->IC_counter;
}

Ins_Node* get_file_ins_head(File_Config* file_config) {
    return file_config->ins_head;
}

Data_Node* get_data_node_head(File_Config* file_config) {
    return file_config->data_head;
}

Data_Node* get_data_node_tail(File_Config* file_config) {
    return file_config->data_tail;
}

Lable_Node* get_label_node_head(File_Config* file_config) {
    return file_config->label_head;
}

/*MAYBE: pass only how many to add?*/
void set_file_config_DC(File_Config* file_config,int DC_counter) {
    file_config->DC_counter = DC_counter; 
}

/*MAYBE: pass only how many to add?*/
void set_file_config_IC(File_Config* file_config,int IC_counter) {
    file_config->IC_counter = IC_counter; 
}

void update_validity_file_config(File_Config** file_config, int validity) {
    if(validity == FALSE)
        (*file_config)->is_valid = FALSE;
}

void update_DC_counter(File_Config** file_config, int num_to_add) {
    if(get_data_node_tail(*file_config) !=NULL) 
        (*file_config)->DC_counter += num_to_add;
}

/*Description: Function to free the memory of the File_Config data structure */
/*Input: a pointer to a pointer of the file config to free*/
void free_file_config(File_Config** file_config_ptr) {
    File_Config* file_config;
    if (file_config_ptr == NULL || *file_config_ptr == NULL) {
        return;
    }

    file_config = *file_config_ptr;

    free_lable_list(&(file_config->label_head));
    free_ins_list(&(file_config->ins_head));
    free_data_list(&(file_config->data_head));

    free(file_config);

    /* Set the file_config pointer to NULL to avoid accessing freed memory */
    *file_config_ptr = NULL;
}

/*ASK: is it allways work?*/
void add_extention(char* file_original_name, char* with_ext_name, char* ext){
    int i;
    
    i = 0;
    while (*file_original_name != '\0'){
         with_ext_name[i] = *file_original_name;
         i++;
         file_original_name++;
    }
    with_ext_name[i++] = '.';
    while (*ext != '\0'){
        with_ext_name[i++] = *ext;
        ext++;
    }
    with_ext_name[i] = '\0';
}

/*
void make_am_name(char* file_original_name, char* am_name){
    int i;
    
    i = 0;
    while (*file_original_name != '.'){
         am_name[i] = *file_original_name;
         i++;
         file_original_name++;
    }
    am_name[i++] = '.';
    am_name[i++] = 'a';
    am_name[i++] = 's';
    am_name[i] = '\0';
}
*/


const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void bin_to_base64(char arr[2], const char* binary_word) {
    int i, bin_value;
    bin_value = 0;
    for (i = 0; i < 12; i++) {
        bin_value <<= 1;
        if (binary_word[i] == '1') {
            bin_value |= 1;
        }
    }

    arr[0] = base64_table[(bin_value >> 6) & 0x3F];
    arr[1] = base64_table[bin_value & 0x3F];
}

int is_entry_file_needed(Lable_Node *lable_head){
    Lable_Node *head;
    head = lable_head;
    while (head != NULL){
        if (head->is_entry == 1){
            return 1;
        }
    }
    return 0;
}

int is_ext_file_needed(Lable_Node *lable_head){
    Lable_Node *head;
    head = lable_head;
    while (head != NULL){
        if (head->symbol_type == EXTERNAL){
            return 1;
        }
    }
    return 0;
}




