
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
#define MAX_LABLE_LEN 31

    typedef struct File_Config {
        int curr_line_num;
        int is_valid;
        int DC_counter;
        int IC_counter;
        Lable_Node* label_head;
        Ins_Node* ins_head;
        Ins_Node* ins_tail;
        Data_Node* data_head;
        Data_Node* data_tail;
    }File_Config;
    
    void intialiez_ins_node(Ins_Node** head, command com, int param_type[2]);
    Ins_Node** insert_ins_node(Ins_Node** head, File_Config* file_conf);
    Ins_Node* insert_ins_head();
    void print_ins_node(Ins_Node* head);



    File_Config* intialiez_file_config();

    int get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type); 
    int get_DC_counter(File_Config* file_config);
    int get_IC_counter(File_Config* file_config);
    Ins_Node* get_file_ins_head(File_Config* file_config);
    Data_Node* get_data_node_tail(File_Config* file_config);
    int get_curr_line_number(File_Config* file_config);

    void set_file_config_DC(File_Config* file_config,int DC_counter);
    void set_file_config_IC(File_Config* file_config,int IC_counter);
    void update_validity_file_config(File_Config** file_config, int validity);
    void update_DC_counter(File_Config** file_config, int num_to_add);

    void free_file_config(File_Config** file_config_ptr);
#endif

