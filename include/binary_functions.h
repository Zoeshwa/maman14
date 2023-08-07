#ifndef _BINARY_INS_HEADER_
#define _BINARY_INS_HEADER_
   #include "Instructions_struct.h"
#endif



#ifndef _BINARY_FILE_HEADER_
#define _BINARY_FILE_HEADER_
   #include "file_functions.h"
   void make_bin_DIR_word(Ins_Node** node, File_Config* file_conf);

#endif

#ifndef _BINARY_HEADER_
#define _BINARY_HEADER_
    
   char* int_to_binary_string(int number, int num_bits);
    void bin_to_base64(char arr[2], const char* binary_word);

#endif


