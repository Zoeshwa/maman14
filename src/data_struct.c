#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct.h"

#define INITIAL_DC_VALUE 0

/**/
typedef struct Data_Node{
    int value; /*value of the char or the int to store*/
    Data_Type data_type; /*string or data*/
    int DC_counter;
    struct Data_Node* next;
} Data_Node;


/*Description: The function creates a new data node, allocates space in memory and initializes the data*/
/*Input: value - value to save in the node, data_type - type of the value (string or data)*/
/*Output: a pointer to the new node */
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

/*Description: The function creates a new data node, allocates space in memory and initializes the data*/
/*Input: head & tail of the data list to insert the new node,
value & data_type for the new node to add to the list*/
void add_data_node(Data_Node** head, Data_Node** tail, int value, Data_Type data_type) {
    Data_Node* new_node = create_data_node(value, data_type);
    if (new_node == NULL) {
        printf("Failed to create a new Data_Node.\n");
        return;
    }

    if (*head == NULL) {
        /* Empty list, the new node becomes the head and tail*/
        new_node->DC_counter = INITIAL_DC_VALUE; /*the DC is the initial value*/
        *head = *tail = new_node;
    } else {
        /*Non-empty list, append the new node at the end*/
        new_node->DC_counter = (*tail)->DC_counter + 1; /*Initialize the counter according to the last node in the list*/
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

int get_data_node_type(Data_Node* node) {
    return node->data_type;
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

/*Description: Function to free the entire linked list of Data_Nodes and set the head pointer to NULL*/
/*Input: a pointer to a pointer of the head of the list to free*/
void free_data_list(Data_Node** head) {
    Data_Node* current = *head;
    Data_Node* next_node;

    while (current != NULL) {
        next_node = get_data_node_next(current);
        free(current);
        current = next_node;
    }
    /* Set the head pointer to NULL after freeing the entire list */
    *head = NULL;
}