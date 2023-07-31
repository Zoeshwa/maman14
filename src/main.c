#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_LEN 80

int main(int argc, char* argv[]) {
    /*char input[MAX_LEN];*/
    int ctr;
    FILE* am_file;
    File_Config * file_config;
    char am_file_name[MAX_LEN];

    /*for every file read from terminal*/ 
    for (ctr = 1; ctr < argc; ctr++){
        /*creating an am file*/
        printf("\t----------START:file \"%s\"\n", argv[ctr]);
        am_file = make_am_file(argv[ctr]); 

        /*open the am file to read*/
        make_am_name(argv[ctr], am_file_name);
        am_file = fopen(am_file_name, "r");

        /*first_pass*/
        file_config = first_pass(am_file);
        
        printf("\n");
        print_file_config(file_config);

        if (!file_config->is_valid){
            printf("NOT GOOD - file \"%s\" have errors.\n", am_file_name);
            continue;
        }

        /*TODO: run secound pass*/
        fclose(am_file);
        free_file_config(&file_config);
        printf("\t----------END:file \"%s\"\n", argv[ctr]);
    }
    printf("\tTHE FINAL END\n");

    return 0;
}




/*int main_ido(){
    File_Config* file_conf;
    FILE* am_file;
    Ins_Node* test_ptr;
    char input[MAX_LEN];

    am_file = fopen("assembly.am","r");
    file_conf = intialiez_file_config();

    while (fgets(input, MAX_LEN, am_file) != NULL){  
        printf("input is: %s\n", input)  ;
        handle_code_line(file_conf, input);
        file_conf->curr_line_num += 1;
        print_ins_node(file_conf->ins_tail);

    }

    test_ptr = file_conf->ins_head;
    while (test_ptr != NULL){
        print_ins_node(test_ptr);
        test_ptr = test_ptr->next;
    }
    return 0;

}*/

int main_test(){
    /*
    File_Config* file_config;
    char input[MAX_LEN] = "LABEL: .data 1, 25.25, +s15, -8, +78, 0, -100 ";

    file_config = intialiez_file_config();

    printf("input is: %s\n", input)  ;
    handle_data_ins(file_config, input, input+12);
    
    printf("Validity of file: %d\n", file_config->is_valid);
    print_Data_Node(file_config->data_head);

    free_file_config(&file_config);
    
   run_handle_data_ins();
    */
    run_labels_tests();

    return 0;

}