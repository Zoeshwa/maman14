#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _BINARY_HEADER_
    #include "binary_functions.h"
#endif


#ifndef _Data_HEADER_
#define _Data_HEADER_
    
    #define INITIAL_DC_VALUE 1

    typedef struct Data_Node Data_Node;
    
    void add_data_node(Data_Node** head, Data_Node** tail, int value, Data_Type data_type);

    Data_Node* get_data_node_next(Data_Node* node);
    char* get_bin_rep_data(Data_Node* node);    
    void free_data_list(Data_Node** head);
    void update_counters_data_list(Data_Node* head, int IC);

    /*DELETE - only for tests*/
    int get_data_node_value(Data_Node* node);
    int get_data_node_type(Data_Node* node);
    int get_data_node_DC_counter(Data_Node* node);
#endif



