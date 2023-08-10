#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enums.h"

/*Description: Printing errors with line number in which have error*/
/*Input: error_msg - the error to print, line_num - in which have error*/
void print_error(char* error_msg, int line_num) {
    fprintf(stdout,"ERROR in line %d: %s\n",line_num, error_msg);
}

/*Description: Printing errors concerning files (opening, writing, etc.)*/
/*Input: error_msg - the error to print, file_name - the file name which have error*/
void print_error_file(char* error_msg, char* file_name) {
    fprintf(stdout,"ERROR: %s - %s\n", error_msg, file_name);
}