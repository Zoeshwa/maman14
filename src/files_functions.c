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
    File_Config* file_config;
    file_config = (File_Config*)malloc(sizeof(Symbol_Table));
    file_config->symbol_table = intialiez_symbol_table();
    file_config->ins_head = intialiez_ins_head();
    file_config->data_head = intialiez_data_table();
    file_config->DC_counter = 0;
    file_config->IC_counter = 100;
    return file_config;
}

int get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type) {
    int counter_value;

    switch (symbol_type)
    {
        case EXTERNALT:
            counter_value = -1; /*MAYBE: not good?*/
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

