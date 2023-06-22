


/*TODO: typeof struct?*/


/*TODO: param type?, change names*/
typedef union u{
	char* c;
	int d;
	}u;



struct Ins_Node {
    int IC; /*ASK: the number?of this ins?*/
    int line; /*ASK: the number or the line itself? num of line in the file after macro*/
    int opcode;
    u param1;
    u param2;
    int error;
    char* err_msg;
    int extra_lines; /*ASK: number or the lines? - how many we need*/
    struct Ins_Node* next;
};

void insertIns_Node(struct Ins_Node** head, int IC, int line_num);
void update_error(struct Ins_Node** head, char* line);
struct Ins_Node* update_Ins_list(struct Ins_Node* cur_line, char * p, char * input, int IC);
