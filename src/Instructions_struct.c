#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instructions_struct.h"



/* Function to insert a new Ins_Node at the beginning of the list*/
void insertIns_Node(struct Ins_Node** head, int IC, int line_num) {
    /* Create a new Ins_Node*/
    struct Ins_Node* newIns_Node = (struct Ins_Node*)malloc(sizeof(struct Ins_Node));
    /* Allocate memory for the name and copy the string*/
    newIns_Node->error = 0;
    newIns_Node->IC = IC;
    newIns_Node->line = line_num;
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



/*TODO: remark*/
/*ASK: where is the void? return type i domt understand the ** to head. the line param is the new msg?*/
void update_error(struct Ins_Node** head, char* line){
    (*head)->err_msg = (char)malloc(strlen(line)*sizeof(char));
    strcpy((*head)->err_msg, line);
}
/*TODO:*/
struct Ins_Node* update_Ins_list(struct Ins_Node* cur_line, char * p, char * input, int IC){
    return NULL;
}

