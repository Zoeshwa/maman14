
#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _INSTRUCTIONS_HEADER_
#define _INSTRUCTIONS_HEADER_
#define MAX_LABLE_LEN 31


typedef struct command {
	char* act;
    int num_of_params;
	int en;
    int operands[2][4];

} command;

    typedef struct Ins_Node {
        int type;
        int IC_count; 
        int line_number; 
        int ARE;
        int opcode; 
        int operrands[2];
        char lable[MAX_LABLE_LEN]; /*for when adding extra ins line representing a lable param */
        char bin_rep[12];
        struct Ins_Node* next;
    } Ins_Node;

    void make_bin_ins_word(Ins_Node** head);
    void make_bin_word(Ins_Node** head);

    char* int_to_binary_string(unsigned int number, int num_bits);
   int is_valid_number_param(char *param);
   int is_compatible_types(int acual_type, int* expected_type);
   int is_valid_com(command com,char** params, int param_types[2], int line_num);
   int get_reg_num(char* reg);
   int is_valid_param_types(int com, char** params, int num_of_params, int param_types[2]);
   int is_legal_com_name(char* input, int i, const command* commands_list);

   void free_ins_list(Ins_Node** head_ptr);
   #endif

#ifndef _LABELS_HEADER_
#define _INSTRUCTIONS_LABELS_HANDLER_HEADER_
    #include "labels.h"
#endif


#ifndef _FILES_FUNCTIONS_HEADER_
    #include "file_functions.h"
#endif


