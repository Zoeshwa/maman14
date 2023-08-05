#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_functions.h"

struct File_Config {
    int curr_line_num;
    int is_valid;
    int DC_counter;
    int IC_counter;
    Lable_Node* label_head;
    Ins_Node* ins_head;
    Ins_Node* ins_tail;
    Data_Node* data_head;
    Data_Node* data_tail;
};

File_Config* intialiez_file_config() {
    File_Config* file_config;
    file_config = (File_Config*)malloc(sizeof(File_Config));
    file_config->label_head = NULL;

    file_config->ins_head = insert_ins_head();
    file_config->ins_tail = file_config->ins_head;

    file_config->data_head = NULL;
    file_config->data_tail = file_config->data_head;

    file_config->curr_line_num = 1;
    file_config->is_valid = TRUE;
    file_config->DC_counter = INITIAL_DC_VALUE;
    file_config->IC_counter = 100; 
    return file_config;
}

int get_curr_line_number(File_Config* file_config){
    return file_config->curr_line_num;
}

int get_is_valid_file(File_Config* file_config){
    return file_config->is_valid;
}

int get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type) {
    int counter_value;

    switch (symbol_type)
    {
        case EXTERNAL:
            counter_value = 0;
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

int get_DC_counter(File_Config* file_config) {
    return file_config->DC_counter;
}

int get_IC_counter(File_Config* file_config) {
    return file_config->IC_counter;
}

Ins_Node* get_file_ins_head(File_Config* file_config) {
    return file_config->ins_head;
}

Ins_Node* get_file_ins_tail(File_Config* file_config) {
    return file_config->ins_tail;
}

Data_Node* get_data_node_head(File_Config* file_config) {
    return file_config->data_head;
}

Data_Node* get_data_node_tail(File_Config* file_config) {
    return file_config->data_tail;
}

Lable_Node* get_label_node_head(File_Config* file_config) {
    return file_config->label_head;
}

Lable_Node** get_file_label_head_address(File_Config* file_config) {
    return &(file_config->label_head);
}

Data_Node** get_file_data_head_address(File_Config* file_config) {
    return &(file_config->data_head);
}

Data_Node** get_file_data_tail_address(File_Config* file_config) {
    return &(file_config->data_tail);
}

void update_validity_file_config(File_Config** file_config, int validity) {
    if(validity == FALSE && *file_config != NULL)
        (*file_config)->curr_line_num = FALSE;
}

void update_line_num_file(File_Config** file_config) {
    if(*file_config != NULL)
        (*file_config)->curr_line_num++;
}

void update_DC_counter(File_Config** file_config, int num_to_add) {
    if(get_data_node_tail(*file_config) !=NULL) 
        (*file_config)->DC_counter += num_to_add;
}

void update_IC_counter(File_Config** file_config, int num_to_add) {
    if(*file_config != NULL)
        (*file_config)->IC_counter += num_to_add;
}

void update_ins_tail_file(File_Config** file_config, Ins_Node* tail) {
    if(*file_config != NULL)
        (*file_config)->ins_tail = tail;
}

/*Description: Function to free the memory of the File_Config data structure */
/*Input: a pointer to a pointer of the file config to free*/
void free_file_config(File_Config** file_config_ptr) {
    File_Config* file_config;
    if (file_config_ptr == NULL || *file_config_ptr == NULL) {
        return;
    }

    file_config = *file_config_ptr;

    free_lable_list(&(file_config->label_head));
    free_ins_list(&(file_config->ins_head));
    free_data_list(&(file_config->data_head));

    free(file_config);
    /* Set the file_config pointer to NULL to avoid accessing freed memory */
    *file_config_ptr = NULL;
}

/*ASK: is it allways work?*/
void add_extention(char* file_original_name, char* with_ext_name, char* ext){
    int i;
    
    i = 0;
    while (*file_original_name != '\0'){
         with_ext_name[i] = *file_original_name;
         i++;
         file_original_name++;
    }
    with_ext_name[i++] = '.';
    while (*ext != '\0'){
        with_ext_name[i++] = *ext;
        ext++;
    }
    with_ext_name[i] = '\0';
}

int is_entry_file_needed(Lable_Node *lable_head){
    Lable_Node *head;
    head = lable_head;
    while (head != NULL){
        if (get_label_is_entry(head) == TRUE){
            return TRUE;
        }
        head = get_label_next(head);
    }
    return FALSE;
}

int is_ext_file_needed(Lable_Node *lable_head){
    Lable_Node *head;
    head = lable_head;
    while (head != NULL){
        if (get_label_symbol_type(head) == EXTERNAL){
            return TRUE;
        }
        head = get_label_next(head);
    }
    return FALSE;
}

/*TODO: ido - need to close after open? every file?*/
void make_files(File_Config *file_config, char* file_name){
    FILE* ob_file, *ext_file, *ent_file;
    char ob_file_name[MAX_LEN], ext_file_name[MAX_LEN], ent_file_name[MAX_LEN], ob_word[2];
    Ins_Node *ins_head;
    Data_Node *data_head;
    Lable_Node * lable_head;

    ins_head = get_file_ins_head(file_config);
    data_head = get_data_node_head(file_config);

    add_extention(file_name, ob_file_name, "ob");
    add_extention(file_name, ext_file_name, "ext");
    add_extention(file_name, ent_file_name, "ent");
    
    ob_file = fopen(ob_file_name, "w+");
    if (ob_file == NULL) {ERROR_CREATING_FILE(ob_file_name);}

    /*write first line rep the number of IC and DC commands*/
    fprintf(ob_file, "%d %d\n", get_IC_counter(file_config) + 1 , get_DC_counter(file_config));
    
    /* mane object file*/

    while (ins_head != NULL){     /*go over ins nodes*/

        bin_to_base64(ob_word, get_ins_binary_representation(ins_head));
        fprintf(ob_file, "%s\n", ob_word);
        ins_head = get_ins_next(ins_head);
    }
    while (data_head != NULL){     /*go over data nodes*/
        bin_to_base64(ob_word, get_bin_rep_data(data_head)); /*TODO: bin rep? ask Zoe*/
        fprintf(ob_file, "%s\n", ob_word);
        data_head = get_data_node_next(data_head);
    }

    lable_head = get_label_node_head(file_config);
    /* make .ext and .ent files*/
    if (is_entry_file_needed(lable_head)){
        ent_file = fopen(ent_file_name, "w+");
        if (ent_file == NULL) {ERROR_CREATING_FILE(ent_file_name);}

        while (lable_head != NULL){
            if (get_label_is_entry(lable_head) == TRUE){
                fprintf(ent_file, "%s %d\n", get_label_name(lable_head), get_label_counter_value(lable_head));
            }
            lable_head = get_label_next(lable_head);
        }
    }

    lable_head = get_label_node_head(file_config);
    if (is_ext_file_needed(lable_head)){
        ext_file = fopen(ext_file_name, "w+");
        if (ext_file == NULL) {ERROR_CREATING_FILE(ext_file_name);}
        while (lable_head != NULL){
            if (get_label_symbol_type(lable_head) == EXTERNAL){
                fprintf(ext_file, "%s %d\n", get_label_name(lable_head), get_label_counter_value(lable_head));
            }
            lable_head = get_label_next(lable_head);
        }
    }

}

