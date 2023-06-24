#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instructions_struct.h"



/*List functions*/

/*MAYBE: delete*/
Ins_Node* intialiez_ins_head() {
    Ins_Node* ins_head;
    ins_head = (Ins_Node*)malloc(sizeof(Ins_Node));
    return ins_head;
}


/* Function to insert a new Ins_Node at the beginning of the list*/
void insertIns_Node(struct Ins_Node** head, int IC, int line_num) {
    /* Create a new Ins_Node*/
    struct Ins_Node* newIns_Node = (struct Ins_Node*)malloc(sizeof(struct Ins_Node));
    /* Allocate memory for the name and copy the string*/
    newIns_Node->is_error = 0;
    newIns_Node->IC_count = IC;
    newIns_Node->line_number = line_num;
    newIns_Node->next = NULL;

    /* If the list is empty, make the new Ins_Node the head of the list*/
    if (*head == NULL) {
        *head = newIns_Node;
    } else {
        /* Otherwise, insert the new Ins_Node at the beginning*/
        newIns_Node->next = *head;
        *head = newIns_Node;
    }
}

/*TODO:*/
void add_ins_to_list(struct Ins_Node *ins_head, struct Ins_Node *curr_ins, int IC,int line_num) {
    if (ins_head == NULL) { /*first ins*/
        insertIns_Node(&ins_head, IC, line_num);
        curr_ins = ins_head;
    }
    else { /* any other ins*/
        IC += 1;
        insertIns_Node(&curr_ins, IC, line_num);
    }
}


/*Node functions*/

void set_IC_ins(Ins_Node* ins_to_update, int IC_count) {
    ins_to_update->IC_count = IC_count;
}

void set_line_number_ins(Ins_Node* ins_to_update, int line_number) {
    ins_to_update->line_number = line_number;
}

void set_encoding_type_ins(Ins_Node* ins_to_update, int encoding_type) {
    ins_to_update->encoding_type = encoding_type;
}

void set_opcode_ins(Ins_Node* ins_to_update, int opcode) {
    ins_to_update->opcode = opcode;
}

/*TODO: set params*/
void set_ins_params() {

}

void set_ins_num_of_extra_lines(Ins_Node* ins_to_update, int num_of_extra_lines) {
    ins_to_update->num_of_extra_lines = num_of_extra_lines;
}

void set_error_ins(Ins_Node* ins_to_update, int is_error, char* error_msg) {
    ins_to_update->is_error = is_error;
    update_error(&ins_to_update, "not a valid lable\n");
}

/*ASK: where is the void? return type i domt understand the ** to head. the line param is the new msg?*/
void update_error(struct Ins_Node** head, char* error_msg){
    (*head)->err_msg = (char*)malloc(strlen(error_msg)*sizeof(char));
    strcpy((*head)->err_msg, error_msg);
}


void set_next_ins(Ins_Node* ins_to_update, Ins_Node* next) {
    ins_to_update->next = next;
}

void update_extern_ins(Ins_Node* curr_ins, int num_of_lines) {
    set_encoding_type_ins(curr_ins, 1);
    set_ins_num_of_extra_lines(curr_ins, num_of_lines);
    /*TODO: what else to update? opcode? params?*/

}

