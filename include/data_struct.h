
#ifndef _DATA_HEADER_
#define _DATA_HEADER_
    
    /*TODO: think about*/
    /*MAYBE:is valid?*/
    typedef struct Data_Node {
        int value; /*ascii code or int*/
        int is_char; /*MAYBE: ?*/
        int DC_counter; /*MAYBE?*/
        struct Data_Node* next;
    } Data_Node;

    typedef struct DATA_Table {
        Data_Node* head;
        Data_Node* tail;
    }DATA_Table;

    DATA_Table* intialiez_data_table();
    void add_data_node_to_table(DATA_Table* table, int value, int is_char, int counter);
    
    int get_data_node_value(Data_Node* node);
    int get_data_node_is_char(Data_Node* node);
    int get_data_node_DC_counter(Data_Node* node);
    Data_Node* get_data_node_next(Data_Node* node);

    Data_Node* new_data_node(int value, int is_char, int counter);
    void set_data_node_value(Data_Node* data_node, int is_char, int value);
    void set_data_node_DC_counter(Data_Node* data_node, int DC_counter);
    void set_data_node_next(Data_Node* data_node, Data_Node* next);


#endif



