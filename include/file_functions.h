#ifndef _FILES_FUNCTIONS_HEADER_
#define _FILES_FUNCTIONS_HEADER_
    void make_am_name(char* file, char* name);

    typedef struct File_Config {
        int DC_counter;
        int IC_counter;
        Symbol_Table* symbol_table;
        Ins_Node* ins_head;
        DATA_Table* data_table;
    }File_Config;

    File_Config* intialiez_file_config();
    int get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type); 

#endif


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

