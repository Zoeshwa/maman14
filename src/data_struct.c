#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct.h"



void add_data_node_to_table(Data_Node* tail, int value, int is_char, int counter) {
    Data_Node* new_node;
    new_node = new_data_node(value, is_char, counter);
    set_data_node_next(tail, new_node);
    tail = new_node; 
}

/*Node functions*/
Data_Node* new_data_node(int value, int is_char, int counter) {
    Data_Node* data_node;
    data_node = (Data_Node*)malloc(sizeof(Data_Node));
    set_data_node_value(data_node, is_char, value);
    set_data_node_DC_counter(data_node, counter);
    data_node->next = NULL;
    return data_node;
}

int get_data_node_value(Data_Node* node) {
    return node->value;
}

int get_data_node_is_char(Data_Node* node) {
    return node->is_char;
}
int get_data_node_DC_counter(Data_Node* node) {
    return node->DC_counter;
}

Data_Node* get_data_node_next(Data_Node* node) {
    return node->next;
}

void set_data_node_value(Data_Node* data_node, int is_char, int value) {
    data_node->value = value;
    data_node->is_char = is_char;
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
