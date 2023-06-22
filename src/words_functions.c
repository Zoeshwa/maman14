#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "words_functions.h"


int is_Ins(char* word){
    if (word[strlen(word)-1] == ':')
        return 1;
    return 0;
}

int is_valid_char(char c){
    if ((47< c && c<58) || (64< c && c<91) || (96< c && c<123))
        return 1;
    return 0;
}