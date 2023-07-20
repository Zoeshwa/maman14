#ifndef _LABELS_HEADER_
    #include "labels.h"
#endif

#ifndef _INSTRUCTIONS_HEADER_
    #include "Instructions_struct.h"
#endif


#ifndef _Data_HEADER_
    #include "Data_struct.h"
#endif

#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _FILES_FUNCTIONS_HEADER_
#define _FILES_FUNCTIONS_HEADER_
    void make_am_name(char* file, char* name);

    typedef struct File_Config {
        int is_valid;
        int DC_counter;
        int IC_counter;
        Lable_Node* label_head;
        Ins_Node* ins_head;
        Ins_Node* ins_tail;
        Data_Node* data_head;
        Data_Node* data_tail;

    }File_Config;

    File_Config* intialiez_file_config();

    int get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type); 
    int get_DC_counter(File_Config* file_config);
    int get_IC_counter(File_Config* file_config);
    Ins_Node* get_file_ins_head(File_Config* file_config);

    void set_file_config_DC(File_Config* file_config,int DC_counter);
    void set_file_config_IC(File_Config* file_config,int IC_counter);

    void free_file_config(File_Config* file_config);
#endif

