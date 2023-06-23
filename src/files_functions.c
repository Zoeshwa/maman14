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

