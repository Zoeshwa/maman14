
#ifndef _INSTRUCTIONS_HEADER_
#define _INSTRUCTIONS_HEADER_
#define MAX_LABLE_LEN 31



/*
    int get_Ins_Node_IC_count(Ins_Node* node);
    int get_Ins_Node_line_number(Ins_Node* node);
    int get_Ins_Node_encoding_type(Ins_Node* node);
    int get_Ins_Node_is_error(Ins_Node* node);
    int get_Ins_Node_num_of_lines(Ins_Node* node);
    char* get_Ins_Node_err_msg(Ins_Node* node);
    Ins_Node* get_Ins_Node_next(Ins_Node* node);
    
    void set_IC_ins(Ins_Node* ins_to_update, int IC_count);
    void set_line_number_ins(Ins_Node* ins_to_update, int line_number);
    void set_encoding_type_ins(Ins_Node* ins_to_update, int encoding_type);
    void set_opcode_ins(Ins_Node* ins_to_update, int opcode);
    void set_ins_params();
    void set_ins_num_of_extra_lines(Ins_Node* ins_to_update, int num_of_extra_lines);
    void set_error_ins(struct Ins_Node* ins_to_update, int is_error, char* error_msg);    
    void set_next_ins(Ins_Node* ins_to_update, Ins_Node* next);
 
    void update_error(struct Ins_Node** head, char* line);
    void update_extern_ins(Ins_Node* curr_ins, int num_of_lines);

    void free_ins_node(Ins_Node* node);
    */
   #endif

#ifndef _ENUMS_HEADER_
#define _INSTRUCTIONS_ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _LABELS_HEADER_
#define _INSTRUCTIONS_LABELS_HANDLER_HEADER_
    #include "labels.h"
#endif
