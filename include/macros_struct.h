#ifndef _MACROS_STRUCT_HEADER_
#define _MACROS_STRUCT_HEADER_

    typedef struct Macro_Node Macro_Node;

    FILE* make_am_file(char* orig_name);
    void make_am_name(char* file, char* name);
    void insertMacro_Node(struct Macro_Node** head, char* name);
    void update_macro_contect(struct Macro_Node** head, char* line);
    struct Macro_Node* search_macro_list(struct Macro_Node* head, char* name);
    void free_macro_list(Macro_Node** head);
    void print_macro_list(Macro_Node* head);
#endif

#ifdef _MACROS_STRUCT_HEADER_
    #include "line_functions.h"
#endif


