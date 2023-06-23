#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instructions_struct.h"


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

void set_error_ins(struct Ins_Node* ins_to_update, int is_error, char* error_msg) {
    ins_to_update->is_error = is_error;
    update_error(&ins_to_update, "not a valid lable\n");
}


/*ASK: where is the void? return type i domt understand the ** to head. the line param is the new msg?*/
void update_error(struct Ins_Node** head, char* error_msg){
    (*head)->err_msg = (char*)malloc(strlen(error_msg)*sizeof(char));
    strcpy((*head)->err_msg, error_msg);
}
/*TODO:*/
struct Ins_Node* update_Ins_list(struct Ins_Node* cur_line, char * p, char * input, int IC){
    return NULL;
}

/*TODO:*/
int is_valid_Ins(char* Ins){
    /*
    if (strlen(Ins)>= 31){
        return 0;
    }
    */
    /*needs a function that checks its not a saved word*/
    /* missing a function that goes over Ins list to check Ins os not defined twice*/
    /*
    while (is_valid_char(*Ins)) {Ins++;}
    if (*Ins == ':'){
        return 1;
    }
    else{
        return 0;
    }
    */ return 0;
}

/*zoe*/
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