
#ifndef _LINES_HEADER_
#define _LINES_HEADER_

    #define MAX_LEN 80

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

    /*DELETE*/
    void print_words(char** words, int len);

#endif

#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif

#ifndef _WORDS_HEADER_
    #include "words_functions.h"
#endif