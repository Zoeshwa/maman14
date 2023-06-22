#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labals.h"



/*TODO: delete - i have instade*/
/* Function to insert a new Lable_Node at the beginning of the list*/
void insertLable_Node(struct Lable_Node** head, char* name, int counter_value, char* type, char counter_type) {
    /* Create a new Lable_Node*/
    struct Lable_Node* newLable_Node = (struct Lable_Node*)malloc(sizeof(struct Lable_Node));

    /* Allocate memory for the name and copy the string*/
    newLable_Node->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newLable_Node->name, name);

    newLable_Node->counter_type = counter_type;
    newLable_Node->type = (char*)malloc((strlen(type) + 1) * sizeof(char));
    strcpy(newLable_Node->type, type);
    newLable_Node->counter_value = counter_value;

    /* If the list is empty, make the new Lable_Node the head of the list*/
    if (*head == NULL) {
        *head = newLable_Node;
    } else {
        /* Otherwise, insert the new Lable_Node at the beginning*/
        newLable_Node->next = *head;
        *head = newLable_Node;
    }
}


Symbol_Table* intialiez_symbol_table() {
    Symbol_Table* symbol_table;
    symbol_table = (Symbol_Table*)malloc(sizeof(Symbol_Table));
    symbol_table->head = NULL;
    symbol_table->tail = symbol_table->head;
    return symbol_table;
}


/*MAYBE: no need of table struct*/
/* Function to insert a new Lable_Node at the beginning of the list*/
void insert_to_symbol_table(Symbol_Table* table, char* word, char* counter_type,  int counter_value, int type) {
    /* Create a new Lable_Node*/
    Lable_Node* new_lable = (Lable_Node*)malloc(sizeof(Lable_Node));

    /* Allocate memory for the name and copy the string*/
    get_label_name(word, new_lable);

    
    new_lable->counter_type = (char*)malloc((strlen(counter_type) + 1) * sizeof(char));
    strcpy(new_lable->counter_type, counter_type);
    new_lable->counter_value = counter_value;
    new_lable->type = type;

    /* If the list is empty, make the new Lable_Node the head of the list*/
    if (table->head == NULL)
    {
        new_lable->next = NULL;
        table->head = new_lable;
        table->tail = new_lable;

    } else {
        /* Otherwise, insert the new Lable_Node at the beginning*/
        new_lable->next = table->head;
        table->head = new_lable;
    }
}

/*TODO: is needed?*/
void get_label_name(char * word, Lable_Node* new_lable) {
    /* Allocate memory for the name and copy the string*/
    new_lable->name = (char*)malloc((strlen(word) + 1) * sizeof(char));
    strcpy(new_lable->name, word);
}

/*TODO and add to valid label*/
int is_symbol_already_exist(Symbol_Table* table, char * symbol_name) {

}