
#ifndef _LABELS_HEADER_
    #include "labels.h"
#endif

#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _Data_HEADER_
    #include "Data_struct.h"
#endif


#ifndef _INSTRUCTIONS_HEADER_
    #include "Instructions_struct.h"
#endif


#ifndef _FILES_FUNCTIONS_HEADER_
#define _FILES_FUNCTIONS_HEADER_
    
    typedef struct File_Config File_Config;

    File_Config* intialiez_file_config();

    int get_curr_line_number(File_Config* file_config);
    int get_is_valid_file(File_Config* file_config);
    int get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type); 
    int get_DC_counter(File_Config* file_config);
    int get_IC_counter(File_Config* file_config);
    Ins_Node* get_file_ins_head(File_Config* file_config);
    Ins_Node* get_file_ins_tail(File_Config* file_config);
    Data_Node* get_data_node_head(File_Config* file_config);
    Data_Node* get_data_node_tail(File_Config* file_config);
    Lable_Node* get_label_node_head(File_Config* file_config);
    Lable_Node** get_file_label_head_address(File_Config* file_config);
    Data_Node** get_file_data_head_address(File_Config* file_config);
    Data_Node** get_file_data_tail_address(File_Config* file_config);

    void update_validity_file_config(File_Config** file_config, int validity);
    void update_line_num_file(File_Config** file_config);
    void update_DC_counter(File_Config** file_config, int num_to_add);
    void update_IC_counter(File_Config** file_config, int num_to_add);
    void update_ins_tail_file(File_Config** file_config, Ins_Node* tail);

    void free_file_config(File_Config** file_config_ptr);

    void add_extention(char* file_original_name, char* with_ext_name, char* ext);
    int is_entry_file_needed(Lable_Node *lable_head);
    int is_ext_file_needed(Lable_Node *lable_head);
    void make_files(File_Config *file_config, char* file_name);
#endif

