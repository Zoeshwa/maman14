
#ifndef _INSTRUCTIONS_HEADER_
    #include "Instructions_struct.h"
#endif



#ifndef _BINARY_FILE_HEADER_
#define _BINARY_FILE_HEADER_
   #include "file_functions.h"
   void make_bin_extra_word(Ins_Node** head, int param, File_Config* lalbe_head);
   void make_bin_DIR_word(Ins_Node** head, File_Config* file_conf);

#endif

#ifndef _BINARY_HEADER_
#define _BINARY_HEADER_
    
    #define WORD_LEN_BINARY 12

   void make_bin_ins_word(Ins_Node** head);
   void make_bin_REG_word(Ins_Node** head, int i);
   void make_bin_IMM_word(Ins_Node** head, int i);
   char* int_to_binary_string(int number, int num_bits);
    void bin_to_base64(char arr[2], const char* binary_word);

#endif


