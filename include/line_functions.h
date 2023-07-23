
#ifndef _LINES_HEADER_
#define _LINES_HEADER_

    #define MAX_LEN 80

    int empty_line(char* line);
    int comment_line(char* line);
    char* skip_spaces(char* p);
    char* get_next_word(char* word, char* line);

    void parsing(char** results, int* len, char* p);
    int is_legal_params(char *line);
    char** get_words(char *line);
    char* get_next_word_no_comma(char* word, char* line);

#endif

#ifndef _ENUMS_HEADER_
    #include "enums.h"
#endif