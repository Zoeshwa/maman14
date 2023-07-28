#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_LEN 80

/*TODO free functions*/

int main_original(int argc, char* argv[]) {

    int ctr;
    /*for every file read from terminal*/ 
    for (ctr=1; ctr < argc; ctr++){
        FILE* am_file;
        File_Config * file_config;

        /*creating an am file*/
        am_file = make_am_file(argv[ctr]); 

        /*first_pass*/
        file_config = first_pass(am_file);
        if (!file_config->is_valid){
            continue;
        }

        /*TODO: run secound pass*/

    }
    
    
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

int main(){
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