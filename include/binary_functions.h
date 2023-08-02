
#ifndef _LABELS_HEADER_
    #include "labels.h"
#endif

#ifndef _INSTRUCTIONS_HEADER_
    #include "Instructions_struct.h"
#endif

#ifndef _FILES_FUNCTIONS_HEADER_
    #include "file_functions.h"
#endif

#ifndef _BINARY_HEADER_
#define _BINARY_HEADER_
    
   void make_bin_extra_word(Ins_Node** head, int param, File_Config* lalbe_head);
   void make_bin_ins_word(Ins_Node** head);
   void make_bin_DIR_word(Ins_Node** head, File_Config* file_conf);
   void make_bin_REG_word(Ins_Node** head, int i);
   void make_bin_IMM_word(Ins_Node** head, int i);
   char* int_to_binary_string(int number, int num_bits);

#endif

/*ido*/

