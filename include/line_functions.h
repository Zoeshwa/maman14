
#ifndef _LINES_HEADER_
#define _LINES_HEADER_

    #define MAX_LEN 80

    int empty_line(char* line);
    int comment_line(char* line);
    char* skip_spaces(char* p);
    char* get_next_word_old(char* str, char* word, char* ptr);
    char* get_next_word(char* word, char* line);
#endif
