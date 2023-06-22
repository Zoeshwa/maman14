typedef union u{
	char* c;
	int d;
	}u;


struct Ins_Node {
    int error;
    int IC;
    int line;
    int opcode;
    u param1;
    u param2;
    char* err_msg;
    int extra_lines;
    struct Ins_Node* next;
};

struct Lable_Node {
    char* name;
    char from; // D-DC, I-IC
    int line;
    int type;
    struct Lable_Node* next;
};

struct Data_Node {
    char c;
    int d;
    struct Data_Node* next;
};

int update_data_list(struct Data_Node** cur_Data, char* p,char* input, int DC){
    

}

void insertIns_Node(struct Ins_Node** head, int IC, int line_num);
int empty_line(char* line);
int comment_line(char* line);
int is_lable(char* word);
int update_data_list(struct Data_Node** cur_Data, char* p,char* input, int DC);