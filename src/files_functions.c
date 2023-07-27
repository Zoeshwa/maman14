#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_functions.h"

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


File_Config* intialiez_file_config() {
    printf("in intialiez_file_config()\n");
    File_Config* file_config;
    file_config = (File_Config*)malloc(sizeof(File_Config));
    file_config->label_head = NULL;
    file_config->ins_head = insert_ins_head();
    file_config->ins_tail = file_config->ins_head;
    file_config->data_head = NULL;
    file_config->data_tail = file_config->data_head;
    file_config->curr_line_num = 1;
    file_config->is_valid = 1;
    file_config->DC_counter = 0;
    file_config->IC_counter = 100; 
    return file_config;
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

/*MAYBE: pass only how many to add?*/
void set_file_config_DC(File_Config* file_config,int DC_counter) {
    file_config->DC_counter = DC_counter; 
}

/*MAYBE: pass only how many to add?*/
void set_file_config_IC(File_Config* file_config,int IC_counter) {
    file_config->IC_counter = IC_counter; 
}


/*TODO: update */
void free_file_config(File_Config* file_config) {

    if(get_file_ins_head(file_config) != NULL){
        free_ins_node(get_file_ins_head(file_config));
    }

    free(file_config);
}
