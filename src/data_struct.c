#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct.h"


/*Node in a linked list that store the data to storage in the memory*/
struct Data_Node{
    int value; /* value of the char or the int to store */
    Data_Type data_type; /* string or data */
    int DC_counter;
    char* binary_rep; /*Representation of the value in binary*/
    struct Data_Node* next;
};

/*Description: The function creates a new data node, allocates space in memory and initializes the data*/
/*Input: value - value to save in the node, data_type - type of the value (string or data)*/
/*Output: a pointer to the new node */
Data_Node* create_data_node(int value, Data_Type data_type) {
    Data_Node* new_node = (Data_Node*)malloc(sizeof(Data_Node));
    
    if (new_node == NULL) {
        fprintf(stdout, "Memory allocation failed for Data_Node.\n");
        return NULL;
    }

    /*Place the data in the node*/
    new_node->value = value;
    new_node->data_type = data_type;
    /*Building the binary representation of the value*/
    new_node->binary_rep = int_to_binary_string(value, WORD_LEN_BINARY);    
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

/* Description: Retrieve the binary representation of a Data_Node.*/
/*Input: A pointer to a Data_Node.*/
/*Output: A pointer to the binary representation (char*) stored in the given Data_Node.*/
char* get_bin_rep_data(Data_Node* node) {
    return node->binary_rep;
}

/* Description: Get the next Data_Node in the linked list.*/
/*Input: A pointer to a Data_Node.*/
/*Output: A pointer to the next Data_Node in the linked list, or NULL if the given node is the last node.*/
Data_Node* get_data_node_next(Data_Node* node) {
    return node->next;
}

/*Description: Function to free the entire linked list of Data_Nodes and set the head pointer to NULL*/
/*Input: a pointer to a pointer of the head of the list to free*/
void free_data_list(Data_Node** head) {
    Data_Node* current;
    Data_Node* next_node;

    current = *head;

    /*for each node in the list*/
    while (current != NULL) {
        if(get_bin_rep_data(current) != NULL) {
            free(current->binary_rep);
            current->binary_rep = NULL;
        }
        next_node = get_data_node_next(current);
        free(current);
        current = next_node;
    }
    /* Set the head pointer to NULL after freeing the entire list */
    *head = NULL;
}

/*Description: Updating the addresses in the data image - threading the data to the end of the instructions*/
/*Input: head - a pointer to a pointer of the head of the data_nope list, IC - the num to add to the counters in the data list*/
void update_counters_data_list(Data_Node* head, int IC) {
    Data_Node* ptr;

    ptr = head; /*start with ptr to head of the list*/

    while (ptr != NULL) {
        ptr->DC_counter = ptr->DC_counter + IC - 1;
        ptr = get_data_node_next(ptr);
    }
}


/*DELETE - only for tests*/
int get_data_node_type(Data_Node* node) {
    return node->data_type;
}

int get_data_node_value(Data_Node* node) {
    return node->value;
}

int get_data_node_DC_counter(Data_Node* node) {
    return node->DC_counter;
}
