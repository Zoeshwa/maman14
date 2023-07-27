#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Instructions_struct.h"
#include "file_functions.h"



/*List functions*/

Ins_Node* insert_ins_head() {
    Ins_Node* ins_head;
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


/*


TODO: delete? if the storage lines dont have a node then its not nesseccery
void update_extern_ins(Ins_Node* curr_ins, int num_of_lines) {
    set_encoding_type_ins(curr_ins, 1);
    set_ins_num_of_extra_lines(curr_ins, num_of_lines);
    TODO: what else to update? opcode? params?

}


void free_ins_node(Ins_Node* node) {
    TODO: FIX
    if(get_Ins_Node_next(node) != NULL) {
        free_ins_node(get_Ins_Node_next(node));
    }
    free(node);
}

*/
