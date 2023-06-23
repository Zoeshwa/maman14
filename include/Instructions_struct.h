

#ifndef _INSTRUCTIONS_HEADER_
#define _INSTRUCTIONS_HEADER_

/*TODO: param type?, change names*/
    typedef union u{
        char* c;
        int d;
        }u;

    struct Ins_Node {
        int IC; /*This INS IC*/
        int line_number; /*num of line in the file after macro*/
        int opcode;
        u param1;
        u param2;
        int is_error;
        char* err_msg;
        int num_of_extra_lines; /*ASK: number or the lines? - how many we need*/
        struct Ins_Node* next;
    };

    void insertIns_Node(struct Ins_Node** head, int IC, int line_num);
    void update_error(struct Ins_Node** head, char* line);
    struct Ins_Node* update_Ins_list(struct Ins_Node* cur_line, char * p, char * input, int IC);
    void add_ins_to_list(struct Ins_Node *ins_head, struct Ins_Node *curr_ins, int IC,int line_num);
    
#endif

#ifndef _ENUMS_HEADER_
#define _INSTRUCTIONS_ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _LABELS_HEADER_
#define _INSTRUCTIONS_LABELS_HANDLER_HEADER_
    #include "labels.h"
#endif
