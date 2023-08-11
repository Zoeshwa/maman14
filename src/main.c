#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


int main(int argc, char* argv[]) {
    int ctr;
    File_Config * file_config;
    char *am_file_name;

    am_file_name = (char*) calloc(MAX_LEN, sizeof(char));

    /*for every file read from terminal*/ 
    for (ctr = 1; ctr < argc; ctr++){
        printf("\t----------START:file \"%s\"\n", argv[ctr]); /*DELETE*/
        /*creating an am file*/
        if (make_am_file(argv[ctr]) == FALSE){
            continue;
        };
  
         /*open the am file to read*/
        add_extention(argv[ctr], am_file_name, "am");

        /*first_pass*/
        file_config = first_pass(am_file_name);
        
        printf("\n"); /*DELETE*/

        if (!get_is_valid_file(file_config)){
            printf("NOT GOOD - file \"%s\" have errors.\n", am_file_name);
            free_file_config(&file_config);
            continue;
        }

        /*run secound pass*/
        second_pass(file_config, am_file_name);
        if (!get_is_valid_file(file_config)){
            printf("NOT GOOD - file \"%s\" have errors.\n", am_file_name);
            free_file_config(&file_config);
            continue;
        }

        
        print_file_config(file_config);  /*DELETE*/
        /*make the needed files*/
        make_files(file_config, argv[ctr]);
        free_file_config(&file_config);

        printf("\t----------END:file \"%s\"\n", argv[ctr]); /*DELETE*/
    }

    free(am_file_name);

    printf("\tTHE FINAL END\n"); /*DELETE*/

    return 0;
}