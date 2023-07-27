#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instructions_struct.h"



/*List functions*/

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

void print_ins_node(Ins_Node* head){
    printf("type: %d, IC count: %d,opcode: %d src: %d, dest: %d, is_lable: %s\n", head->type,head->IC_count, head->opcode, head->operrands[0], head->operrands[1], head->lable);
}

void intialiez_ins_node(Ins_Node** head, command com, int param_type[2]) {

    /*TODO: (*head)->ARE*/
    (*head)->opcode = com.en;
    (*head)->operrands[0] = param_type[0];
    (*head)->operrands[1] = param_type[1];
    (*head)->next = NULL;
}


void free_ins_node(Ins_Node* node) {
    /*TODO: FIX
    if(get_Ins_Node_next(node) != NULL) {
        free_ins_node(get_Ins_Node_next(node));
    }
    free(node);
    */
}


/* checks if the beggining of the input line is a valid command line */
int is_legal_com_name(char* input, int i, command* commands_list){
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
