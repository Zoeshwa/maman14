
#ifndef _Data_HEADER_
#define _Data_HEADER_
    
    /*TODO: think about*/
    /*MAYBE:is valid?*/
    typedef struct Data_Node {
        int value; /*ascii code or int*/
        int is_char; /*MAYBE: ?*/
        int DC_counter; /*MAYBE?*/
        struct Data_Node* next;
    } Data_Node;


    
    int get_Data_node_value(Data_Node* node);
    int get_Data_node_is_char(Data_Node* node);
    int get_Data_node_DC_counter(Data_Node* node);
    Data_Node* get_Data_node_next(Data_Node* node);

    Data_Node* new_data_node(int value, int is_char, int counter);
    void set_Data_node_value(Data_Node* Data_node, int is_char, int value);
    void set_Data_node_DC_counter(Data_Node* Data_node, int DC_counter);
    void set_Data_node_next(Data_Node* Data_node, Data_Node* next);

    void free_Data_node(Data_Node* node);

#endif



