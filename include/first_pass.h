

#ifndef _LABELS_HEADER_
#define _FIRST_PASS_LABELS_HEADER_
    #include "labels.h"
#endif


#ifndef _INSTRUCTIONS_HEADER_
    #include "Instructions_struct.h"
#endif


#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _FILES_FUNCTIONS_HEADER_
    #include "file_functions.h"
#endif

#ifndef _FIRST_PASS_HEADER_
#define _FIRST_PASS_HEADER_

    void first_pass();
    void handle_extren_line(File_Config* file_config, struct Ins_Node* curr_ins, char* line, char* curr_ptr);
    void handle_code_line(File_Config* file_config, struct Ins_Node* curr_ins, char* line, char* curr_ptr);
    void handle_data_ins(File_Config* file_config, struct Ins_Node* curr_ins, char* line, char* curr_ptr);
    void handle_label(File_Config* file_config, struct Ins_Node* curr_ins, char* word, Symbol_Type symbol_type);

#endif

