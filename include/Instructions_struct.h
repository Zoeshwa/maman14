
#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif


#ifndef _BINARY_HEADER_
    #include "binary_functions.h"    
#endif


#ifndef _INSTRUCTIONS_HEADER_
#define _INSTRUCTIONS_HEADER_
#define MAX_LABLE_LEN 31
#define NUM_OF_COM 16


    typedef struct Command Command;

    struct Command {
        char* act;
        int num_of_params;
        int en;
        int operands[2][4];
    };

    typedef struct Ins_Node Ins_Node;
    
    Ins_Node** insert_ins_node(Ins_Node** head, int IC_counter, int curr_line_num);
    void intialiez_ins_node(Ins_Node** head, Command com, int param_type[2]);
    Ins_Node* insert_ins_head();
    void print_ins_node(Ins_Node* head);

   int is_compatible_types(int acual_type, const int* expected_type);
   int is_valid_com(Command com,char** params, int param_types[2], int line_num);
   int get_reg_num(char* reg);
   int is_valid_param_types(int com, char** params, int num_of_params, int param_types[2]);
   int is_legal_com_name(char* input, int i, const Command* commands_list);
    void set_bin_rep_ins_node(Ins_Node** node, char* bin_ptr);
   void free_ins_list(Ins_Node** head_ptr);

    int get_ins_node_type(Ins_Node* node);
    int get_ins_IC_count(Ins_Node* node);
    int get_ins_line_number(Ins_Node* node);
    int get_ins_ARE(Ins_Node* node);
    int get_ins_opcode(Ins_Node* node);
    char* get_ins_label(Ins_Node* node);
    char* get_ins_binary_representation(Ins_Node* node);
    Ins_Node* get_ins_next(Ins_Node* node);

    int set_operand_value(char* param, Ins_Node** head);
    void set_ins_type(Ins_Node** node, int type);
    void set_ins_operands(Ins_Node** node, int operand1, int operand2);
    void set_ins_operand(Ins_Node** node, int operrand_index, int operand_value);

    void make_bin_extra_word(Ins_Node** head, int param);
    void make_bin_REG_word(Ins_Node** head, int i);
    void make_bin_IMM_word(Ins_Node** head, int i);
    void make_bin_ins_word(Ins_Node** head);


    const Command* get_command_conf_array();
    Command get_action(char* input, const Command* commands_list);
   #endif

#ifndef _LABELS_HEADER_
#define _INSTRUCTIONS_LABELS_HANDLER_HEADER_
    #include "labels.h"
#endif





