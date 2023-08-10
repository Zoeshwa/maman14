
#ifndef _STRING_HEADER_
#define _STRING_HEADER_
    
    #define ZERO_IN_ASCII 48
    #define QUOTES '\"'
    #define COLON 58

    #define IS_UPPERCASE_LETTERS(c) (64< c && c<91)
    #define IS_LOWERCASE_LETTERS(c) (96< c && c<123)
    
    int empty_line(char* line);
    int comment_line(char* line);
    char* skip_spaces(char* p);
    char* get_next_word(char* word, char* line);

    int is_legal_params(char *line, int line_num);
    char** get_words(char *line);
    char* get_next_word_no_comma(char* word, char* line);
    void free_words(char** words);
    int get_len_words_array(char ** words);
    char* skip_next_word(char* line, char *curr_ptr);

    int is_valid_quotes(char* word);
    int is_valid_int_param(char *curr_word,int curr_line_num);

    int is_external_or_entry_ins(char* input);
    int is_extern_ins(char* input);
    int is_data_storage_ins(char * input);
    int is_type_ins(int (*function)(char*), char* input);
    int is_extern_word(char* cur_word);
    int is_entry_word(char* cur_word);
    int is_word_equals_string(char* cur_word);
    int is_data_word(char* cur_word);
    int is_lable(char* word);
    int is_type_storge_string_ins(char * input);

    void remove_colon_at_end(char* word);
    void get_saved_words(const char*** saved_words, int* num_saved_words);
    int is_saved_word(const char* word);
    int is_visible_chars_only(char * input);
    int is_valid_lable_param(char *param);
    int get_param_type(char* param);
    int is_valid_number_param(char *param);


    int is_space(char c);
    int get_number(char* p);
    int is_valid_string_param(char * word, int line_number);
    int is_end_line(char c);
    int get_sign_value(char curr_char);

#endif


#ifndef _STRING_UTILS_MACRO_HEADER_
#define _STRING_UTILS_MACRO_HEADER_
    char* skip_spaces(char* p);
    char* get_next_word(char* word, char* line);

#endif

#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif