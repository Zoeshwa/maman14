
/*ASK: do we need to save pointer to the data?*/
typedef struct Lable_Node {
    char* name;
    /*MAYBE: maybe enum instad?*/
    char counter_type; /* D-DC, I-IC */
    int counter_value;/*value of DC/IC - the address*/
    int type; /* external OR relocatable*/
    struct Lable_Node* next;
}Lable_Node;


/*TODO:*/
typedef struct Symbol_Table {
    Lable_Node* head;
    Lable_Node* tail;
}Symbol_Table;

void insertLable_Node(struct Lable_Node** head, char* name, int DC, char* type, char from);
Symbol_Table* intialiez_symbol_table();