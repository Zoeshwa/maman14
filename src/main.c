#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_LEN 80 /*ASK: not include the \0*/


int main(int argc, char* argv[]) {
    int ctr;
    File_Config * file_config;
    char am_file_name[MAX_LEN];

    /*for every file read from terminal*/ 
    for (ctr = 1; ctr < argc; ctr++){
        /*creating an am file*/
        printf("\t----------START:file \"%s\"\n", argv[ctr]);
        make_am_file(argv[ctr]); 
  
         /*open the am file to read*/
        add_extention(argv[ctr], am_file_name, "am");


        /*first_pass*/
        file_config = first_pass(am_file_name);
        
        printf("\n");

        if (!get_is_valid_file(file_config)){
            printf("NOT GOOD - file \"%s\" have errors.\n", am_file_name);
            continue;
        }

        /*run secound pass*/
        second_pass(file_config, am_file_name);
        if (!get_is_valid_file(file_config)){
            printf("NOT GOOD - file \"%s\" have errors.\n", am_file_name);
            continue;
        }

        /*DELETE*/
        print_file_config(file_config); 

        make_files(file_config, argv[ctr]);
        free_file_config(&file_config);

        printf("\t----------END:file \"%s\"\n", argv[ctr]);
    }

    printf("\tTHE FINAL END\n");

    return 0;
}

int main_o(int argc, char* argv[]) {
    run_words_functions_testers();


    return 0;
}