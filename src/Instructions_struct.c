#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instructions_struct.h"


/*Ins_Node struct functions*/

Ins_Node* insert_ins_head() {
    Ins_Node* ins_head;
    printf("in insert_ins_head()\n");
    ins_head = (Ins_Node*)malloc(sizeof(Ins_Node));
    ins_head->line_number = -1;
    ins_head->IC_count = 100;
    ins_head->type = 0;
    ins_head->next = NULL;
    return ins_head;
}

/* Function to insert a new Ins_Node at the end of the list*/
Ins_Node** insert_ins_node(Ins_Node** head, File_Config* file_conf) {
    /* Create a new Ins_Node*/
    Ins_Node* newIns_Node;
    newIns_Node = (Ins_Node*)malloc(sizeof(Ins_Node));

    newIns_Node->type = 0;
    newIns_Node->IC_count = file_conf->IC_counter;
    (*head)->line_number = file_conf->curr_line_num;

    (*head)->next = newIns_Node;
    *head = newIns_Node;
    return head;
}

char* int_to_binary_string(unsigned int number, int num_bits) {
    int i;
    char* result = (char*)malloc((num_bits + 1) * sizeof(char));
    for (i = num_bits; i >= 0; i--) {
    for (i = num_bits - 1; i >= 0; i--) {
            result[i] = (number & 1) + '0'; /* Convert bit to '0' or '1' */
            number >>= 1; /* Shift right to get the next bit */
        }
        result[num_bits] = '\0'; /* Null-terminate the string */
    }
    return result;
    }

    void make_bin_ins_word(Ins_Node** head){
    char *bin_src, *bin_opcode, *bin_dest, *bin_are;

    /*save as string the bin rep of the fields*/
    bin_src = int_to_binary_string((*head)->operrands[0], 3);
    bin_dest = int_to_binary_string((*head)->operrands[1], 3);
    bin_opcode = int_to_binary_string((*head)->opcode, 4);
    bin_are = int_to_binary_string(0, 2);

    printf("src:%d , %s dest:  %d, %s opcode  %d, %s\n", (*head)->operrands[0], bin_src, (*head)->operrands[1], bin_dest, (*head)->opcode, bin_opcode);
    /*make the bin ins word*/
    strcat((*head)->bin_rep, bin_src);
    strcat((*head)->bin_rep, bin_opcode);
    strcat((*head)->bin_rep, bin_dest);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[12] = '\0';

    free(bin_src);
    free(bin_are);
    free(bin_dest);
    free(bin_opcode);

    printf("bin_word is: %s\n", (*head)->bin_rep);


    return;
}

void make_bin_IMM_word(Ins_Node** head, int i){
    char* bin_are, *bin_imm;
    bin_are = int_to_binary_string(0, 2);
    bin_imm = int_to_binary_string((*head)->operrands[i], 10);

    strcat((*head)->bin_rep, bin_imm);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[12] = '\0';

    free(bin_are);
    free(bin_imm);
}

void make_bin_REG_word(Ins_Node** head, int i){
    char *bin_src, *bin_dest, *bin_are;

    /*save as string the bin rep of the fields*/
    bin_src = int_to_binary_string((*head)->operrands[0], 5);
    bin_dest = int_to_binary_string((*head)->operrands[1], 5);
    bin_are = int_to_binary_string(0, 2);
    
    strcat((*head)->bin_rep, bin_src);
    strcat((*head)->bin_rep, bin_dest);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[12] = '\0';

    free(bin_src);
    free(bin_are);
    free(bin_dest);
}

void make_bin_DIR_word(Ins_Node** head, Lable_Node* lable_list){
    Lable_Node* lable;
    char* bin_adress, *bin_are;

    lable = find_lable(lable_list, (*head)->lable);
    bin_adress = int_to_binary_string(lable->counter_value, 10);

    if (get_label_symbol_type(lable) == EXTERNAL){
        bin_are = int_to_binary_string(1, 2);
    }
    else{
        bin_are = int_to_binary_string(2, 2);
    }
    strcat((*head)->bin_rep, bin_adress);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[12] = '\0';
}


void make_bin_extra_word(Ins_Node** head, int param, Lable_Node* lable_head){
    int type;
    type = (*head)->type;
     if (type == IMM){ 
        make_bin_IMM_word(head, (*head)->operrands[param]);
    }    else if (type == REG_DIR){ 
        make_bin_REG_word(head,(*head)->operrands[param]);
    }    else if (type == DIR){ 
        make_bin_DIR_word(head, lable_head);
    }
}



void intialiez_ins_node(Ins_Node** head, command com, int param_type[2]) {

    (*head)->type = NONE;
    (*head)->ARE = NONE;
    (*head)->opcode = com.en;
    (*head)->operrands[0] = param_type[0];
    (*head)->operrands[1] = param_type[1];

    (*head)->next = NULL;
}

void print_ins_node(Ins_Node* head){
    printf("type: %d, IC count: %d,opcode: %d src: %d, dest: %d, is_lable: %s\n", head->type,head->IC_count, head->opcode, head->operrands[0], head->operrands[1], head->lable);
}

/*Description: Function to free a single Ins_Node and set the pointer to NULL*/
/*Input: a pointer to a pointer of the node to free*/
void free_ins_node(Ins_Node** node) {
    Ins_Node* current;

    current = *node;
    if (current != NULL) {
        if(current->lable != NULL )
            free(current->lable);
        if(current->operrands != NULL){
            free(current->operrands);
            free(current->operrands);
        }
        free(*node);  /* Free the Ins_Node itself */
        *node = NULL; /* Set the pointer to NULL after freeing */
    }   
}

/*Description: Function to free the entire linked list of Ins_Node and set the head pointer to NULL*/
/*Input: a pointer to a pointer of the head of the list to free*/
void free_ins_list(Ins_Node** head_ptr) {
    Ins_Node* current;
    Ins_Node* next_node;
    
    if (head_ptr == NULL || *head_ptr == NULL) {
        return;
    }

    current = *head_ptr;
    while (current != NULL) {
        next_node = current->next;
        free_ins_node(&current);  /* Free the current node */
        current = next_node; /* Move to the next node */
    }

    /* Set the head pointer to NULL to avoid accessing freed memory */
    *head_ptr = NULL;
}

/*utils functions*/

/* checks if the beggining of the input line is a valid command line */
int is_legal_com_name(char* input, int i, const command* commands_list){
	int j;
	for ( j=0; j < strlen(commands_list[i].act); j++)  /* check if its one of the commands */
	{
		if (input[j] != commands_list[i].act[j] || is_space(input[j])){
			return 0;}
	}	
	return 1;
}

int is_valid_number_param(char *param){
    if(*param == '-'){
        param++;
    }
    while (*param != '\0'){
        if (!is_number_char(*param)){
            return 0;
        }
        param++;
    }
    return 1;
}

int is_compatible_types(int acual_type, int* expected_type){
    int i;
    for (i=0; expected_type[i] != -1; i++){
        if (expected_type[i] == acual_type){
            return 1;
        }
    }
    return 0;
}

int is_valid_com(command com,char** params, int param_types[2], int line_num){
    int num_of_params,i;
    num_of_params=0;

    for (i=0; params[i] != NULL ; i++){    /*count num of params in array*/
        num_of_params+=1;
    }
    if (num_of_params != com.num_of_params){
        ERROR_NOT_COMPATIBLE_PARAMS(line_num);
        return 0;
    }
    else if(!is_valid_param_types(com.en, params, num_of_params, param_types)){
        /*error - type of params is not compatible (printed inside)*/
        return 0;
    }
    else{
        return 1;
    }
}


int get_reg_num(char* reg){
    return (int)reg[2]-48;
}
