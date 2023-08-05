
#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _STRING_HEADER_
    #include "string_functions.h"
#endif

#ifndef _LABELS_HEADER_
#define _LABELS_HEADER_
    
    typedef struct Lable_Node Lable_Node;

    Lable_Node* new_label_node(char* word, int counter_value, Symbol_Type symbol_type);
    void insert_to_symbol_table(Lable_Node** head, char* word, int counter_value, Symbol_Type symbol_type);
    
    int get_label_counter_value(Lable_Node* new_lable);
    int get_label_is_entry(Lable_Node* new_lable);
    char* get_label_name(Lable_Node* new_lable);
    Symbol_Type get_label_symbol_type(Lable_Node* new_lable);
    Lable_Node* get_label_next(Lable_Node* new_lable);
    
    int is_valid_lable(Lable_Node* head, char* word, int line_num);
    Lable_Node* find_lable(Lable_Node* head, char * symbol_name);
    int mark_entry_label(Lable_Node* head, char * label_word, int line_num);
    void update_counters_label_list(Lable_Node* head, int IC);
    void set_label_name(Lable_Node* new_lable, char * word);
    
    void free_lable_list(Lable_Node** head);
    void free_label_node(Lable_Node** node);
#endif


