
#ifndef _DATA_HEADER_
#define _DATA_HEADER_
    /*TODO: think about*/
    typedef struct Data_Node {
        char c; /*ASK why not the U? do we need also type maybe?*/
        int d;
        struct Data_Node* next;
    } Data_Node;

    typedef struct DATA_Table {
        Data_Node* head;
        Data_Node* tail;
    }DATA_Table;

    DATA_Table* intialiez_data_table();
    
#endif



