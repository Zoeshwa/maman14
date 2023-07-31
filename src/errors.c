#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enums.h"

void print_error(char* error_msg, int line_num) {
    fprintf(stdout,"ERROR in line %d: %s\n",line_num, error_msg);
}