#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Instructions_struct.h"

struct Ins_Node {
    int type;
    int IC_count; 
    int line_number; 
    int ARE;
    int opcode; 
    int operrands[2];
    char lable[MAX_LABLE_LEN]; /*for when adding extra ins line representing a lable param */
    char *bin_rep;
    struct Ins_Node* next;
};


/*Ins_Node struct functions*/

Ins_Node* insert_ins_head() {
    Ins_Node* ins_head;
    ins_head = (Ins_Node*)malloc(sizeof(Ins_Node));
    ins_head->line_number = -1;
    ins_head->IC_count = 100;
    ins_head->type = 0;
    ins_head->bin_rep = NULL;
    ins_head->opcode = -1;
    ins_head->next = NULL;
    return ins_head;
}

/* Function to insert a new Ins_Node at the end of the list*/
Ins_Node** insert_ins_node(Ins_Node** head, int IC_counter, int curr_line_num) {
    /* Create a new Ins_Node*/
    Ins_Node* newIns_Node;
    newIns_Node = (Ins_Node*)malloc(sizeof(Ins_Node));
    if (newIns_Node == NULL) {
        /* Failed to allocate memory, handle error */
        return head;
    }

    newIns_Node->type = 0;
    newIns_Node->IC_count = IC_counter;

    (*head)->line_number = curr_line_num;

    (*head)->next = newIns_Node;
    *head = newIns_Node;
    return head;
}

void intialiez_ins_node(Ins_Node** head, Command com, int param_type[2]) {

    (*head)->type = NONE;
    (*head)->ARE = NONE;
    (*head)->opcode = com.en;
    (*head)->operrands[0] = param_type[0];
    (*head)->operrands[1] = param_type[1];
    (*head)->bin_rep = NULL;
    (*head)->next = NULL;
    (*head)->lable[0] = '\0';
    (*head)->bin_rep = NULL;
}

/*get functions*/

int get_ins_node_type(Ins_Node* node){
    return node->type;
}

/* Function to get the IC_count of an Ins_Node */
int get_ins_IC_count(Ins_Node* node) {
    return node->IC_count;
}

/* Function to get the line_number of an Ins_Node */
int get_ins_line_number(Ins_Node* node) {
    return node->line_number;
}

/* Function to get the ARE of an Ins_Node */
int get_ins_ARE(Ins_Node* node) {
    return node->ARE;
}

/* Function to get the opcode of an Ins_Node */
int get_ins_opcode(Ins_Node* node) {
    return node->opcode;
}

/* Function to get the label of an Ins_Node */
char* get_ins_label(struct Ins_Node* node) {
    return node->lable;
}

/* Function to get the binary representation of an Ins_Node */
char* get_ins_binary_representation(struct Ins_Node* node) {
    return node->bin_rep;
}

Ins_Node* get_ins_next(Ins_Node* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->next;
}


/*set*/

void set_ins_type(Ins_Node** node, int type) {
    if (*node != NULL) {
        (*node)->type = type;
    }
}


void set_bin_rep_ins_node(Ins_Node** node, char* bin_ptr) {
    if(*node != NULL)
        (*node)->bin_rep = bin_ptr;
}

void set_ins_operands(Ins_Node** node, int operand1, int operand2) {
    if (*node != NULL) {
        (*node)->operrands[0] = operand1;
        (*node)->operrands[1] = operand2;
    }
}

void set_ins_operand(Ins_Node** node, int operrand_index, int operand_value) {
    if (*node != NULL && operrand_index < 2 && operrand_index >= 0) {
        (*node)->operrands[operrand_index] = operand_value;
    }
}

/*Description: Function to free a single Ins_Node and set the pointer to NULL*/
/*Input: a pointer to a pointer of the node to free*/
void free_ins_node(Ins_Node** node) {
    Ins_Node* current;

    current = *node;
    if (current != NULL) {
        if (current->bin_rep != NULL) {
            free(current->bin_rep);
        }
        free(current); /* Free the memory pointed by the 'current' pointer */
        *node = NULL;  /* Set the pointer to NULL after freeing */
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

    current = *head_ptr; /* Set current to the head of the list */
    while (current != NULL) {
        next_node = current->next; /* Store the next node before freeing the current node */
        free_ins_node(&current);  /* Free the current node by passing a pointer to it */
        current = next_node; /* Move to the next node */
    }

    /* Set the head pointer to NULL to avoid accessing freed memory */
    *head_ptr = NULL;
}

/*utils functions*/

/* checks if the beggining of the input line is a valid command line */
int is_legal_com_name(char* input, int i, const Command* commands_list){
	int j;
	for ( j=0; j < strlen(commands_list[i].act); j++)  /* check if its one of the commands */
	{
		if (input[j] != commands_list[i].act[j] || is_space(input[j])){
			return 0;}
	}	
	return 1;
}



int is_compatible_types(int acual_type, const int* expected_type){
    int i;
    for (i=0; expected_type[i] != -1; i++){
        if (expected_type[i] == acual_type){
            return TRUE;
        }
    }
    return FALSE;
}

int is_valid_com(Command com,char** params, int param_types[2], int line_num){
    int num_of_params,i;
    num_of_params = 0;

    for (i = 0; params[i] != NULL ; i++){    /*count num of params in array*/
        num_of_params+=1;
    }

    if (num_of_params != com.num_of_params){
        ERROR_NOT_COMPATIBLE_PARAMS(line_num);
        return FALSE;
    } else if(!is_valid_param_types(com.en, params, num_of_params, param_types)){
        ERROR_NOT_VALID_PARAMS(line_num);
        return FALSE;
    }
    else{
        return TRUE;
    }
}

int get_reg_num(char* reg){
    return (int)reg[2]-48;
}

int set_operand_value(char* param, Ins_Node** head){
    if ((*head)->type == DIR) { /*if parameter is lable - copy it to node*/
        strcpy((*head)->lable,param);
        return 0;
    } else if ((*head)->type == REG_DIR){
        return get_reg_num(param);
    }
    else{
        return get_number(param);
    }

}

/*bin functions*/
void make_bin_ins_word(Ins_Node** head){
    char *bin_src, *bin_opcode, *bin_dest, *bin_are;

    (*head)->bin_rep = (char*)calloc(WORD_LEN_BINARY+1,sizeof(char));

    /*save as string the bin rep of the fields*/
    bin_src = int_to_binary_string((*head)->operrands[0], 3);
    bin_dest = int_to_binary_string((*head)->operrands[1], 3);
    bin_opcode = int_to_binary_string((*head)->opcode, 4);
    bin_are = "00";

    /*make the bin ins word*/
    strcat((*head)->bin_rep, bin_src);
    strcat((*head)->bin_rep, bin_opcode);
    strcat((*head)->bin_rep, bin_dest);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[13] = '\0';


    if(bin_src != NULL)
        free(bin_src);
    if(bin_dest != NULL)
        free(bin_dest);
    if(bin_opcode != NULL)
        free(bin_opcode);
}

void make_bin_IMM_word(Ins_Node** head, int i){
    char* bin_are, *bin_imm;
    bin_are = "00";
    bin_imm = int_to_binary_string(i, 10);

    printf("oprerand is: %d, bin_imm is: %s, bin_are: %s\n", i, bin_imm, bin_are);

    strcat((*head)->bin_rep, bin_imm);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[13] = '\0';

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
    (*head)->bin_rep[13] = '\0';


    free(bin_src);
    free(bin_dest);

}


void make_bin_extra_word(Ins_Node** head, int param){
    int type;
    (*head)->bin_rep = (char*)calloc(13,sizeof(char));
    
    type = (*head)->type;
    if (type == IMM){ 
        make_bin_IMM_word(head, (*head)->operrands[param]);


    }else if (type == REG_DIR){ 
        make_bin_REG_word(head,(*head)->operrands[param]);

    }

}



/* desc: gets the action from the command read */
Command get_action(char* input, const Command* commands_list)
{
	Command com;
	int i;
	for (i=0; i < NUM_OF_COM; i++)
	{
		if (is_legal_com_name(input,i, commands_list)){
			com = commands_list[i];
			return com;
		}
	}
	com = commands_list[SKIP];
	return com;
}

/*DELETE*/
void print_Ins_Node(Ins_Node* head) {
    if(head == NULL) {
        printf("node = NULL\n");
        return;
    }
    printf("INS_NODE: \t");
    printf("type: %d, \tIC count: %d,", head->type,head->IC_count);

    if( head->bin_rep != NULL)
        printf("\tbin: %s",  head->bin_rep);
    else
        printf("\tbin: NULL");
    if(head->lable != NULL) {
        printf("\tis_lable: %s,", head->lable);
    } else {
        printf("\tis_lable: NULL,");
    }

    printf("\topcode: %d,\tsrc: %d,\t dest: %d,", head->opcode, head->operrands[0], head->operrands[1]);

    if(head->next  != NULL) {
        printf("\tnext: \n");
        print_Ins_Node(head->next);
    }else {
        printf("\tnext: NULL\n");
    }
} 

/*DELETE*/
void print_ins_node(Ins_Node* head){
    printf(" type: %d, IC count: %d,opcode: %d src: %d, dest: %d, is_lable: %s, bin: %s\n\n", head->type,head->IC_count, head->opcode, head->operrands[0], head->operrands[1], head->lable, head->bin_rep);
}