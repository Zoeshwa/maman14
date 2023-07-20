#ifndef _MACROS_STRUCT_HEADER_
#define _MACROS_STRUCT_HEADER_


    /* Macro_Node in macro linked list*/
    struct Macro_Node {
        char* name;
        char* content;
        int lines;
        struct Macro_Node* next;
    };


    void insertMacro_Node(struct Macro_Node** head, char* name);
    void update_macro_contect(struct Macro_Node** head, char* line);
    struct Macro_Node* search_macro_list(struct Macro_Node* head, char* name);
#endif

#ifdef _MACROS_STRUCT_HEADER_
    #include "line_functions.h"
#endif


