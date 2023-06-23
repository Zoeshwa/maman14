
#ifndef _WORDS_HEADER_
#define _WORDS_HEADER_

    #define IS_NUMBER(c) (47< c && c<58)
    #define IS_UPPERCASE_LETTERS(c) (64< c && c<91)
    #define IS_LOWERCASE_LETTERS(c) (96< c && c<123)


    int is_Ins(char* word);
    int is_valid_char(char c);


    /*TODO: maybe move to Labels*/
    #define MAX_LABEL_LEN 31
    #define COLON 58

    int is_lable(char* word);
    int is_scope_ins(char* input);
    int is_extern_word(char* cur_word);
    int is_entry_word(char* cur_word);
    int is_extern_ins(char* input);


#endif

#ifndef _LINES_HEADER_
#define _STR_HEADER_
    #include "line_functions.h"
#endif

#ifndef _ENUMS_HEADER_
#define _WORDS_ENUMS_HEADER_
    #include "enums.h"
#endif
