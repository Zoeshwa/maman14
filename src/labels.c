#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labels.h"



Symbol_Table* intialiez_symbol_table() {
    Symbol_Table* symbol_table;
    symbol_table = (Symbol_Table*)malloc(sizeof(Symbol_Table));
    symbol_table->head = NULL;
    symbol_table->tail = symbol_table->head;
    return symbol_table;
}

/*MAYBE: no need of table struct*/
/* Function to insert a new Lable_Node at the beginning of the list*/
void insert_to_symbol_table(Symbol_Table* table, char* word, int counter_value, Symbol_Type symbol_type) {
    /* Create a new Lable_Node*/
    Lable_Node* new_lable = (Lable_Node*)malloc(sizeof(Lable_Node));
    set_label_name(word, new_lable);
    set_label_types(new_lable, symbol_type);
    new_lable->counter_value = counter_value;
    set_label_next(new_lable, table);
}

/*TODO: is needed?*/
void set_label_name(char * word, Lable_Node* new_lable) {
    /* Allocate memory for the name and copy the string*/
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
 
void set_label_next(Lable_Node* new_lable, Symbol_Table* table) {

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

/*TODO and add to valid label*/
Lable_Node* is_symbol_already_exist(Symbol_Table* table, char * symbol_name) {
    Lable_Node* ptr;

    ptr = table->head;

    while (ptr != NULL)
    {
        if(strcmp(ptr->name, symbol_name)) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}



/*Description: check if a given word is a valid lable*/
/*Input: a string word (pointer to array of chars)*/
/*Output: 1 - true, 0- false*/
int is_valid_lable(Symbol_Table* table, char* word){
    char * ptr;
    int i;

    ptr = word;

    /*MAYBE - skip spaces in the begining?*/

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
    if(is_symbol_already_exist(table, word) == NULL) {
        return 0; /*return false*/
    }

    /*TODO*/
    /*its not a save word*/

    return 1; /*return true*/
}