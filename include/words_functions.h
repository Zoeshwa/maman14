
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

    int is_external_or_entry_ins(char* input);
    int is_extern_ins(char* input);
    int is_data_storage_ins(char * input);
    int is_type_ins(int (*function)(char*), char* input);
    int is_extern_word(char* cur_word);
    int is_entry_word(char* cur_word);
    int is_string_word(char* cur_word);
    int is_data_word(char* cur_word);
    int is_lable(char* word);
    int is_type_storge_string_ins(char * input);

    void remove_colon_at_end(char* word);
    void get_saved_words(const char*** saved_words, int* num_saved_words);
    int is_saved_word(const char* word);
    int is_visible_chars_only(char * input);

    int is_space(char c);
    int is_number_char(char c);
    int get_number(char* p);

#endif

#ifndef _LINES_HEADER_
#define _STR_HEADER_
    #include "line_functions.h"
#endif

#ifndef _ENUMS_HEADER_
#define _WORDS_ENUMS_HEADER_
    #include "enums.h"
#endif
