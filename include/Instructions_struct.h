

#ifndef _INSTRUCTIONS_HEADER_
#define _INSTRUCTIONS_HEADER_

/*TODO: param type?, change names*/
    typedef union u{
        char* c;
        int d;
        }u;

    typedef struct Ins_Node {
        int IC_count; /*what about extren or data commands?*/
        int line_number; /*num of line in the file after macro*/
        /*Symbol_Type type of command*/
        /*int is there symbol for command*/
        int encoding_type; /*Absolute, External, Relocatable*/
        int opcode; /*MAYBE need other for binary */
        u param1;
        u param2;
        int is_error; /*ASK: what about warning*/
        char* err_msg;
        int num_of_extra_lines; /*ASK: number or the lines? - how many we need*/
        struct Ins_Node* next;
    } Ins_Node;

    Ins_Node* intialiez_ins_head();
    void insertIns_Node(struct Ins_Node** head, int IC, int line_num);
    void add_ins_to_list(struct Ins_Node *ins_head, struct Ins_Node *curr_ins, int IC,int line_num);
    
    int get_Ins_Node_IC_count(Ins_Node* node);
    int get_Ins_Node_line_number(Ins_Node* node);
    int get_Ins_Node_encoding_type(Ins_Node* node);
    int get_Ins_Node_is_error(Ins_Node* node);
    int get_Ins_Node_num_of_lines(Ins_Node* node);
    char* get_Ins_Node_err_msg(Ins_Node* node);

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

#endif

#ifndef _ENUMS_HEADER_
#define _INSTRUCTIONS_ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _LABELS_HEADER_
#define _INSTRUCTIONS_LABELS_HANDLER_HEADER_
    #include "labels.h"
#endif
