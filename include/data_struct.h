#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _Data_HEADER_
#define _Data_HEADER_
    
    /*TODO: think about*/
    /*MAYBE:is valid?*/
    typedef struct Data_Node {
        int *value; /*array of ascii code or int for storage*/
        int num_of_elements; 
        Data_Type data_type; /*MAYBE: ?*/
        int DC_counter; /*MAYBE? good if there is no lable before*/
        struct Data_Node* next;
    } Data_Node;

    int get_data_node_value(Data_Node* node);
    int get_data_node_DC_counter(Data_Node* node);
    Data_Node* get_data_node_next(Data_Node* node);

    Data_Node* new_data_node(int value, int is_char, int counter);
    void set_data_node_value(Data_Node* Data_node, int is_char, int value);
    void set_data_node_DC_counter(Data_Node* Data_node, int DC_counter);
    void set_data_node_next(Data_Node* Data_node, Data_Node* next);

    void free_data_node(Data_Node* node);

#endif



