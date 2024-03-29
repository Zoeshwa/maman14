#include "string_functions.h"
#include "enums.h"


typedef struct Macro_Node Macro_Node;

int make_am_file(char* orig_name);
void add_extention(char* file_original_name, char* with_ext_name, char* ext);
void insertMacro_Node(struct Macro_Node** head, char* name);
void update_macro_contect(struct Macro_Node** head, char* line);
struct Macro_Node* search_macro_list(struct Macro_Node* head, char* name);
void free_macro_list(Macro_Node** head);
void print_macro_list(Macro_Node* head);



#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

