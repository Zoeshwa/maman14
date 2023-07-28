#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _Data_HEADER_
#define _Data_HEADER_
    
    typedef struct Data_Node Data_Node;
    
    void add_data_node(Data_Node** head, Data_Node** tail, int value, Data_Type data_type);

    int get_data_node_value(Data_Node* node);
    int get_data_node_type(Data_Node* node);
    int get_data_node_DC_counter(Data_Node* node);
    Data_Node* get_data_node_next(Data_Node* node);
    
    void free_data_list(Data_Node** head);
#endif



