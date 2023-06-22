#include "first_pass.h"
#include "data_struct.h"



struct Ins_Node {
    int IC; //ASK: the number?of this ins?
    int line; //ASK: the number or the line itself? num of line in the file after macro
    int opcode;
    u param1;
    u param2;
    int error;
    char* err_msg;
    int extra_lines; //ASK: number or the lines? - how many we need
    struct Ins_Node* next;
};

void insertIns_Node(struct Ins_Node** head, int IC, int line_num);
update_error(struct Ins_Node** head, char* line);