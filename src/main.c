#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_LEN 80 /*ASK: not include the \0*/



void make_files(File_Config *file_config, char* file_name){
    FILE* ob_file, *ext_file, *ent_file;
    char ob_file_name[MAX_LEN], ext_file_name[MAX_LEN], ent_file_name[MAX_LEN], ob_word[2];
    Ins_Node *ins_head;
    Data_Node *data_head;
    Lable_Node * lable_head;

    ins_head = file_config->ins_head;
    data_head = file_config->data_head;

    add_extention(file_name, ob_file_name, "ob");
    add_extention(file_name, ext_file_name, "ext");
    add_extention(file_name, ent_file_name, "ent");
    
    ob_file = fopen(ob_file_name, "w+");
    /*write first line rep the number of IC and DC commands*/
    fprintf(ob_file, "%d %d\n", file_config->IC_counter + 1 , file_config->DC_counter);
    
    /* mane object file*/

    while (ins_head != NULL){     /*go over ins nodes*/

        bin_to_base64(ob_word, ins_head->bin_rep);
        fprintf("%s\n", ob_word);
        ins_head = ins_head->next;
    }
    while (data_head != NULL){     /*go over data nodes*/

        bin_to_base64(ob_word, get_bin_rep_data(data_head)); /*TODO: bin rep? ask Zoe*/
        fprintf("%s\n", ob_word);
        data_head = get_data_node_next(data_head);
    }

    lable_head = file_config-> label_head;
    /* make .ext and .ent files*/
    if (is_entry_file_needed(lable_head)){
        ent_file = fopen(ent_file_name, "w+");
        while (lable_head != NULL){
            if (lable_head->is_entry == 1){
                fprintf("%s %d\n", lable_head->name, lable_head->counter_value);
            }
            lable_head = lable_head->next;
        }
    }

    lable_head = file_config-> label_head;
    if (is_ext_file_needed(lable_head)){
        ext_file = fopen(ext_file_name, "w+");
        while (lable_head != NULL){
            if (lable_head->symbol_type == EXTERNAL){
                fprintf("%s %d\n", lable_head->name, lable_head->counter_value);
            }
            lable_head = lable_head->next;
        }
    }

}

int main_orignssss(int argc, char* argv[]) {
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
        add_extention(argv[ctr], am_file_name, "am");


        /*first_pass*/
        file_config = first_pass(am_file_name);
        
        printf("\n");

        if (!file_config->is_valid){
            printf("NOT GOOD - file \"%s\" have errors.\n", am_file_name);
            continue;
        }


        /*run secound pass*/
        second_pass(file_config, am_file_name);
        if (!file_config->is_valid){
            printf("NOT GOOD - file \"%s\" have errors.\n", am_file_name);
            continue;
        }
      
        print_file_config(file_config); 
        make_files(file_config, argv[ctr]);

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

/*void test_init_ins_node(Ins_Node** head, int type, int src, int dest, int opcode){
       (*head)->type = type;
       (*head)->operrands[0] = src; 
       (*head)->operrands[1] =  dest;
       (*head)->opcode = opcode; 
}
*/
int main(int argc, char* argv[]){
    File_Config * file_config;


    /*first_pass*/
    file_config = first_pass("data_valid_file.am");
    
    printf("\n");

    if (!file_config->is_valid){
        printf("NOT GOOD - file  have errors.\n");
    } else {

        /*run secound pass*/
        second_pass(file_config, "data_valid_file.am");
        if (!file_config->is_valid){
            printf("NOT GOOD - file  have errors.\n");
        }

    }


    print_file_config(file_config); 

    free_file_config(&file_config);


    printf("\tTHE FINAL END\n");

    return 0;

}