#ifndef _LABELS_HEADER_
    #include "labels.h"
#endif

#ifndef _INSTRUCTIONS_HEADER_
    #include "Instructions_struct.h"
#endif


#ifndef _DATA_HEADER_
    #include "data_struct.h"
#endif

#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _FILES_FUNCTIONS_HEADER_
#define _FILES_FUNCTIONS_HEADER_
    void make_am_name(char* file, char* name);

    typedef struct File_Config {
        int DC_counter;
        int IC_counter;
        struct Symbol_Table* symbol_table;
        struct Ins_Node* ins_head;
        struct Ins_Node* ins_tail;
        struct DATA_Table* data_table;
    }File_Config;

    File_Config* intialiez_file_config();

    int get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type); 
    int get_DC_counter(File_Config* file_config);
    int get_IC_counter(File_Config* file_config);
    Symbol_Table* get_file_symbol_table(File_Config* file_config);
    Ins_Node* get_file_ins_head(File_Config* file_config);
    DATA_Table* get_file_data_table(File_Config* file_config);

    void set_file_config_DC(File_Config* file_config,int DC_counter);
    void set_file_config_IC(File_Config* file_config,int IC_counter);

    void free_file_config(File_Config* file_config);
#endif

