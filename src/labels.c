#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labels.h"





/*MAYBE: no need of table struct*/
/* Function to insert a new Lable_Node at the beginning of the list*/
Lable_Node* s(Lable_Node* head, char* word, int counter_value, Symbol_Type symbol_type) {
    /* Create a new Lable_Node*/
    Lable_Node* new_lable;
    new_lable = new_label_node(word,counter_value,symbol_type);
    set_label_next(new_lable, head);
    return new_lable;
}

void insert_to_symbol_table(Lable_Node** head, char* word, int counter_value, Symbol_Type symbol_type) {
    /* Create a new node */
    Lable_Node* new_node = new_label_node(word,counter_value,symbol_type);
    if (new_node == NULL) {
        printf("Failed to insert node. Memory allocation error.\n");
        return;
    }
    /* Make the new node the new head of the list */
    new_node->next = *head;
    *head = new_node;
}

Lable_Node* new_label_node(char* word, int counter_value, Symbol_Type symbol_type) {
    Lable_Node* new_lable;
    new_lable = (Lable_Node*)malloc(sizeof(Lable_Node));
    set_label_name(new_lable, word);
    set_label_types(new_lable, symbol_type);
    new_lable->counter_value = counter_value;
    new_lable->next = NULL;
    return new_lable;
}

int get_label_counter_value(Lable_Node* new_lable) {
    return new_lable->counter_value;
}

int get_label_is_entry(Lable_Node* new_lable) {
    return new_lable->is_entry;
}

char* get_label_name(Lable_Node* new_lable) {
    return new_lable->name;
}

Counter_Type get_label_counter_type(Lable_Node* new_lable) {
    return new_lable->counter_type;
}

Symbol_Type get_label_symbol_type(Lable_Node* new_lable) {
    return new_lable->symbol_type;
}

Lable_Node* get_label_next(Lable_Node* new_lable) {
    return new_lable->next;
}

/*TODO: is needed?*/
void set_label_name(Lable_Node* new_lable, char * word) {
    /* Allocate memory for the name and copy the string*/
    /*TODO: delete the : char in the end*/
    new_lable->name = (char*)malloc((strlen(word) + 1) * sizeof(char));
    strcpy(new_lable->name, word);
}

void set_label_types(Lable_Node* new_lable, Symbol_Type symbol_type) {
    new_lable->symbol_type = symbol_type;

    if(symbol_type == DATA) {
        new_lable->counter_type = DC;
    }
    if(symbol_type == CODE) {
        new_lable->counter_type = IC;
    }
}
 
void set_label_next(Lable_Node* new_lable, Lable_Node* head) {

    /* If the list is empty, make the new Lable_Node the head of the list*/
    /*
    if (head == NULL)
    {
        head = new_lable;
        head->next = NULL;

    } else {
    
    */
        /* Otherwise, insert the new Lable_Node at the beginning*/
        new_lable->next = head;
    /*}*/
}

/*TODO and add to valid label*/
Lable_Node* is_symbol_already_exist(Lable_Node* head, char * symbol_name) {
    Lable_Node* ptr;

    ptr = head;

    while (ptr != NULL)
    {
        if(strcmp(get_label_name(ptr), symbol_name) == 0) {
            return ptr;
        }
        ptr = get_label_next(ptr);
    }
    return NULL;
}

/*Description: check if a given word is a valid lable*/
/*Input: a string word (pointer to array of chars)*/
/*Output: 1 - true, 0- false*/
int is_valid_lable(Lable_Node* head, char* word){
    char * ptr;
    int i;

    ptr = word;

    /*starts with A-Z/a-z*/
    if(!IS_UPPERCASE_LETTERS(*ptr) && !IS_LOWERCASE_LETTERS(*ptr)) {
        return 0; /*return false*/
    }

    /*have only max len for labels and end with : and no spaces before ":"*/
    if(strlen(word) > MAX_LABEL_LEN || !is_lable(word)) {
        return 0; /*return false*/
    }

    /*all othe chars is valid*/
    for(i = 0; i < strlen(word) - 1; i++) {
        if(!is_valid_char(*ptr)){
            return 0; /*return false*/
        }
        ptr++;
    }


    /*there is no other label like this*/
    if(is_symbol_already_exist(head, word) != NULL) {
        return 0; /*return false*/
    }

    /*TODO: its not a save word*/

    return 1; /*return true*/
}

/*

void free_label_node(Lable_Node* lable_node) {
    printf("free");
    if(lable_node != NULL) {
        free_label_node(get_label_next(lable_node));
        free(lable_node);
        lable_node = NULL;
    }
    if(get_label_next(lable_node) != NULL) {
        free_label_node(get_label_next(lable_node));
    }
    free(lable_node);
}
*/

/* Function to free a single Lable_Node and set the pointer to NULL */
void free_label_node(Lable_Node** node) {
    if (*node != NULL) {
        /* Free the dynamically allocated name */
        free((*node)->name);
        /* Free the Lable_Node itself */
        free(*node);
        /* Set the pointer to NULL after freeing */
        *node = NULL;
    }
}

/* Function to free the entire linked list of Lable_Nodes and set the head pointer to NULL */
void free_lable_list(Lable_Node** head) {
    Lable_Node* current = *head;
    Lable_Node* next_node;

    while (current != NULL) {
        /* Save the reference to the next node */
        next_node = current->next;
        /* Free the current node */
        free_label_node(&current);
        /* Move to the next node */
        current = next_node;
    }
    /* Set the head pointer to NULL after freeing the entire list */
    *head = NULL;
}

