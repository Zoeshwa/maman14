#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "first_pass.h"

void second_pass(File_Config **file_config, FILE* am_file) {

    /*initilazed varabels*/
    char input[MAX_LEN];

    printf("\t---------START 2 PASS-----------\n");

    /*for each line in the file*/
    while (fgets(input, MAX_LEN, am_file) != NULL){    
        printf("\tline %d: %s\n", get_curr_line_number(file_config), input);
        
        if (empty_line(input) || comment_line(input)){continue;}
        
        /*TODO: if line entry - handle entry zoe*/
        /*if code func handle  - IDO*/
    }

    printf("\t---------END FIRST PASS-----------\n");

}
