#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_functions.h"

/*A data structure for an input file that contains information useful in building the code and converting it to binary*/
struct File_Config {
    int curr_line_num; /*the current line number in process*/
    int is_valid; /*validity status*/
    int DC_counter; /*The next address for a row of data storage type */
    int IC_counter; /*The next address in memory for the command type line*/
    Lable_Node* label_head; /*Head of the lable list*/
    Ins_Node* ins_head; /*Head of the ins list*/
    Ins_Node* ins_tail; /*tail of the ins list*/
    Data_Node* data_head; /*Head of the data list*/
    Data_Node* data_tail; /*tail of the data list*/
};

/* Description: initialization and create File_Config*/
/*Output: A pointer to the new File_Config.*/
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
    file_config->IC_counter = INITIAL_IC_VALUE; 
    return file_config;
}

/* Description: Get the current line number from the File_Config structure.*/
/*Input: A pointer to a File_Config structure.*/
/*Output: The current line number stored in the File_Config structure.*/
int get_curr_line_number(File_Config* file_config){
    return file_config->curr_line_num;
}

/* Description: Get the validity status of a file from the File_Config structure.*/
/*Input: A pointer to a File_Config structure.*/
/*Output: The validity status (0 or 1) stored in the File_Config structure.*/
int get_is_valid_file(File_Config* file_config){
    return file_config->is_valid;
}

/* Description: Get the counter value (The next available address) based on the given symbol type from the File_Config structure.*/
/*Input: A pointer to a File_Config structure, and a Symbol_Type enum value.*/
/*Output: The counter value corresponding to the given symbol type from the File_Config structure. if symbol_type not valid -1*/
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
        
        default: /*symbol_type not valid*/
            counter_value = -1;
            break;
    }

    return counter_value;
}

/* Description: Get the current value of the DC counter from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: The current value of the DC counter stored in the File_Config structure.
*/
int get_DC_counter(File_Config* file_config) {
    return file_config->DC_counter;
}

/* Description: Get the current value of the IC counter from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: The current value of the IC counter stored in the File_Config structure.
*/
int get_IC_counter(File_Config* file_config) {
    return file_config->IC_counter;
}

/* Description: Get the head of the instruction nodes linked list from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: A pointer to the head of the instruction nodes linked list.
*/
Ins_Node* get_file_ins_head(File_Config* file_config) {
    return file_config->ins_head;
}

/* Description: Get the tail of the instruction nodes linked list from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: A pointer to the tail of the instruction nodes linked list.
*/
Ins_Node* get_file_ins_tail(File_Config* file_config) {
    return file_config->ins_tail;
}

/* Description: Get the head of the data nodes linked list from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: A pointer to the head of the data nodes linked list.
*/
Data_Node* get_data_node_head(File_Config* file_config) {
    return file_config->data_head;
}

/* Description: Get the tail of the data nodes linked list from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: A pointer to the tail of the data nodes linked list.
*/
Data_Node* get_data_node_tail(File_Config* file_config) {
    return file_config->data_tail;
}

/* Description: Get the head of the label nodes linked list from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: A pointer to the head of the label nodes linked list.
*/
Lable_Node* get_label_node_head(File_Config* file_config) {
    return file_config->label_head;
}

/* Description: Get the address of the head of the label nodes linked list from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: A pointer to the address of the head of the label nodes linked list.
*/
Lable_Node** get_file_label_head_address(File_Config* file_config) {
    return &(file_config->label_head);
}

/* Description: Get the address of the head of the data nodes linked list from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: A pointer to the address of the head of the data nodes linked list.
*/
Data_Node** get_file_data_head_address(File_Config* file_config) {
    return &(file_config->data_head);
}

/* Description: Get the address of the tail of the data nodes linked list from the File_Config structure.
   Input: A pointer to a File_Config structure.
   Output: A pointer to the address of the tail of the data nodes linked list.
*/
Data_Node** get_file_data_tail_address(File_Config* file_config) {
    return &(file_config->data_tail);
}


/* Description: Update the validity status of a File_Config structure to false if needed (once file is not valid cant make him valid).
   Input: A double pointer to a File_Config structure and an integer value representing validity.
*/
void update_validity_file_config(File_Config** file_config, int validity) {
    if(validity == FALSE && *file_config != NULL)
        (*file_config)->is_valid = FALSE;
}

/* Description: Update the current line number to next line number of a File_Config structure.
   Input: A double pointer to a File_Config structure.
*/
void update_line_num_file(File_Config** file_config) {
    if(*file_config != NULL)
        (*file_config)->curr_line_num++;
}

/* Description: Update the DC counter of a File_Config structure.
   Input: A double pointer to a File_Config structure and an integer value to add to the DC counter.
*/
void update_DC_counter(File_Config** file_config, int num_to_add) {
    if(get_data_node_tail(*file_config) !=NULL) 
        (*file_config)->DC_counter += num_to_add;
}

/* Description: Update the IC counter of a File_Config structure.
   Input: A double pointer to a File_Config structure and an integer value to add to the IC counter.
*/
void update_IC_counter(File_Config** file_config, int num_to_add) {
    if(*file_config != NULL)
        (*file_config)->IC_counter += num_to_add;
}

/* Description: Update the instruction tail pointer of a File_Config structure.
   Input: A double pointer to a File_Config structure and a pointer to an Ins_Node representing the new tail.
*/
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
    *file_config_ptr = NULL;  /* Set the file_config pointer to NULL to avoid accessing freed memory */
}

/*Description: Add the desired extension to the file name */
/*Input: file_original_name - the original name of the file without extension, with_ext_name - where to store the result, ext - the wanted extension*/
void add_extention(char* file_original_name, char* with_ext_name, char* ext){
    int i;
    
    i = 0;

    /*copy the file name to the result word*/
    while (*file_original_name != '\0'){
         with_ext_name[i] = *file_original_name;
         i++;
         file_original_name++;
    }

    with_ext_name[i++] = '.'; /*add a dot after the file name*/

    /*copy the wanted extension*/
    while (*ext != '\0'){
        with_ext_name[i++] = *ext;
        ext++;
    }
    with_ext_name[i] = '\0';
}

/* Description: The function checks whether it is required to generate an ent file for the input. 
    If there is an entry label it is required to produce, otherwise it is not required to produce
   Input: A pointer to the lable_head in the File_Config structure.
   Output: 1 if the ent file needed, 0 if not
*/
int is_entry_file_needed(Lable_Node *lable_head){
    Lable_Node *head;

    head = lable_head;
    while (head != NULL){ /*check for every label in the file*/
        if (get_label_is_entry(head) == TRUE){ /*if one label is entry return true (1)*/
            return TRUE;
        }
        head = get_label_next(head);
    }
    return FALSE; /*there is not one entry label so return false (0)*/
}

/* Description: The function checks whether it is required to generate an ext file for the input. 
    If there is an extern label it is required to produce, otherwise it is not required to produce
   Input: A pointer to the lable_head in the File_Config structure.
   Output: 1 if the ext file needed, 0 if not
*/
int is_ext_file_needed(Lable_Node *lable_head){
    Lable_Node *head;
    head = lable_head;
    while (head != NULL){  /*check for every label in the file*/
        if (get_label_symbol_type(head) == EXTERNAL){ /*if one label is extern return true (1)*/
            return TRUE;
        }
        head = get_label_next(head);
    }
    return FALSE; /*there is not one extern label so return false (0)*/
}

/* Description: The function produces the required output files for a given file.
    The function will generate an ob file as well as ent/ext files if required
   Input: A pointer to the file_config and the file original name.
*/void make_files(File_Config *file_config, char* file_name){
    FILE* ob_file, *ext_file, *ent_file;
    char *ob_file_name, *ext_file_name, *ent_file_name, ob_word[2];
    Ins_Node *ins_head;
    Data_Node *data_head;
    Lable_Node * lable_head;

    /*get the names for the files to create*/
    ob_file_name = (char*) calloc(MAX_LEN, sizeof(char));
    ext_file_name = (char*) calloc(MAX_LEN, sizeof(char));
    ent_file_name = (char*) calloc(MAX_LEN, sizeof(char));
    add_extention(file_name, ob_file_name, "ob");
    add_extention(file_name, ext_file_name, "ext");
    add_extention(file_name, ent_file_name, "ent");

    /*open the ob file*/
    ob_file = fopen(ob_file_name, "w+");
    if (ob_file == NULL) {ERROR_CREATING_FILE(ob_file_name);}

    /*write first line rep the number of IC and DC commands*/
    fprintf(ob_file, "%d %d\n", get_IC_counter(file_config) + 1 , get_DC_counter(file_config));
    
    ins_head = get_file_ins_head(file_config);
    data_head = get_data_node_head(file_config);
    while (ins_head != NULL && get_ins_line_number(ins_head) != -1){ /*go over ins nodes*/
        bin_to_base64(ob_word, get_ins_binary_representation(ins_head));
        fprintf(ob_file, "%s\n", ob_word);
        ins_head = get_ins_next(ins_head);
    }

    while (data_head != NULL){     /*go over data nodes*/
        bin_to_base64(ob_word, get_bin_rep_data(data_head));
        fprintf(ob_file, "%s\n", ob_word);
        data_head = get_data_node_next(data_head);
    }

    /* make .ent file*/
    lable_head = get_label_node_head(file_config);
    if (is_entry_file_needed(lable_head)){
        ent_file = fopen(ent_file_name, "w+");
        if (ent_file == NULL) {ERROR_CREATING_FILE(ent_file_name);}

        while (lable_head != NULL){
            if (get_label_is_entry(lable_head) == TRUE){ /*for every entry lable*/
                fprintf(ent_file, "%s %d\n", get_label_name(lable_head), get_label_counter_value(lable_head));
            }
            lable_head = get_label_next(lable_head);
        }
    }

    /* make .ext file*/
    lable_head = get_label_node_head(file_config);

    if (is_ext_file_needed(lable_head)){
        ext_file = fopen(ext_file_name, "w+");
        if (ext_file == NULL) {ERROR_CREATING_FILE(ext_file_name);}
        while (lable_head != NULL){
            if (get_label_symbol_type(lable_head) == EXTERNAL){ /*for every extern label*/
                /*Write the occurrences of this label*/
                ins_head = get_file_ins_head(file_config);
                while(ins_head != NULL){
                    if (strcmp(get_label_name(lable_head), get_ins_label(ins_head)) == 0){
                        fprintf(ext_file, "%s %d\n", get_label_name(lable_head), get_ins_IC_count(ins_head));
                    }
                    ins_head = get_ins_next(ins_head);
                }
            }
            lable_head = get_label_next(lable_head);
        }
    }

    free(ent_file_name);
    free(ext_file_name);
    free(ob_file_name);
}

