#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct.h"

#define INITIAL_DC_VALUE 0
    typedef struct Data_Node {
        int value; /*value of the char or the int to store*/
        Data_Type data_type;
        int DC_counter; /*ASK? good if there is no lable before*/
        struct Data_Node* next;
    } Data_Node;

/*
void add_data_node_to_table(Data_Node* tail, int value, int is_char, int counter) {
    Data_Node* new_node;
    new_node = new_data_node(value, is_char, counter);
    set_data_node_next(tail, new_node);
    tail = new_node; 
}
*/

Data_Node* create_data_node(int value, Data_Type data_type) {
    Data_Node* new_node = (Data_Node*)malloc(sizeof(Data_Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed for Data_Node.\n");
        return NULL;
    }

    new_node->value = value;
    new_node->data_type = data_type;
    new_node->next = NULL;

    return new_node;
}

void add_data_node(Data_Node** head, Data_Node** tail, int value, Data_Type data_type) {
    Data_Node* new_node = create_data_node(value, data_type);
    if (new_node == NULL) {
        printf("Failed to create a new Data_Node.\n");
        return;
    }

    if (*head == NULL) {
        /* Empty list, the new node becomes the head and tail*/
        new_node->DC_counter = INITIAL_DC_VALUE;
        *head = *tail = new_node;
    } else {
        /* Non-empty list, append the new node at the end*/
        new_node->DC_counter = (*tail)->DC_counter + 1;
        (*tail)->next = new_node;
        *tail = new_node;
    }
}


int get_data_node_value(Data_Node* node) {
    return node->value;
}

int get_data_node_DC_counter(Data_Node* node) {
    return node->DC_counter;
}

Data_Node* get_data_node_next(Data_Node* node) {
    return node->next;
}

/*TODO*/
void set_data_node_value(Data_Node* data_node, int is_char, int value) {
    /*
    data_node->value = value;
    data_node->is_char = is_char;

*/
}

void set_data_node_DC_counter(Data_Node* data_node, int DC_counter) {
    data_node->DC_counter = DC_counter;
}

void set_data_node_next(Data_Node* data_node, Data_Node* next) {
    data_node->next = next;
}


void free_data_node(Data_Node* node) {
    if(get_data_node_next(node) != NULL) {
        free_data_node(get_data_node_next(node));
    }
    free(node);
}
