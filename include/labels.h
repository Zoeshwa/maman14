
#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _WORDS_HEADER_
    #include "words_functions.h"
#endif

#ifndef _LABELS_HEADER_
#define _LABELS_HEADER_
    
    typedef struct Lable_Node {
        char* name;
        Counter_Type counter_type; /*maybe we need none? may be we dont need?*/
        int counter_value; /*value of DC/IC - the address*/
        Symbol_Type symbol_type; /* external OR relocatable*/
        int is_entry; 
        struct Lable_Node* next;
    } Lable_Node;


    /*TODO:*/
    typedef struct Symbol_Table {
        Lable_Node* head;
        Lable_Node* tail;
    }Symbol_Table;

    Symbol_Table* intialiez_symbol_table();
    void insert_to_symbol_table(Symbol_Table* table, char* word, int counter_value, Symbol_Type symbol_type);
    int is_valid_lable(Symbol_Table* table, char* word);
    
    Lable_Node* new_label_node(char* word, int counter_value, Symbol_Type symbol_type);
    
    int get_label_counter_value(Lable_Node* new_lable);
    int get_label_is_entry(Lable_Node* new_lable);
    char* get_label_name(Lable_Node* new_lable);
    Counter_Type get_label_counter_type(Lable_Node* new_lable);
    Symbol_Type get_label_symbol_type(Lable_Node* new_lable);
    Lable_Node* get_label_next(Lable_Node* new_lable);
    
    void set_label_name(Lable_Node* new_lable, char* word);
    void set_label_types(Lable_Node* new_lable, Symbol_Type symbol_type);
    void set_label_next(Lable_Node* new_lable, Symbol_Table* table);
    Lable_Node* is_symbol_already_exist(Symbol_Table* table, char * symbol_name);

#endif


