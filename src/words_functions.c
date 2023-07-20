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
    if (IS_NUMBER(c) || IS_UPPERCASE_LETTERS(c) || IS_LOWERCASE_LETTERS(c))
        return 1;
    return 0;
}


/*Description: check if a given word is a lable - end with ":"*/
/*Input: a string word (pointer to array of chars)*/
/*Output: 1 - true, 0- false*/
int is_lable(char* word) {
    char * ptr;

    ptr = word + strlen(word) - 1; /*go to last char*/
    /*end with : and no spaces before :*/
    if(*ptr != COLON) {
        return 0; /*return false*/
    }
    return 1; /*return true*/
}

int is_external_or_entry_ins(char* input) {
   return (is_type_ins(is_extern_word, input) || is_type_ins(is_entry_word, input));
}

int is_extern_word(char* cur_word) {
    if(strcmp(cur_word, ".extern") == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}


int is_data_storage_ins(char * input) {
    return (is_type_ins(is_data_word, input) || is_type_ins(is_string_word, input));
}

int is_type_storge_string_ins(char * input) {
    return is_type_ins(is_string_word, input);
}

int is_extern_ins(char* input) {
   return is_type_ins(is_extern_word, input);
}

int is_type_ins(int (*function)(char*), char* input) {
    char * ptr;
    char cur_word[MAX_LEN];
    int result; 

    result = 0;
    ptr = input;

    get_next_word(cur_word, ptr);
    ptr = skip_spaces(ptr); 
    
    if(is_lable(cur_word)) {
        ptr =  ptr + strlen(cur_word);
        get_next_word(cur_word, ptr);
    }

    if(function(cur_word)) {
        result = 1;
    }

    return result;
}

int is_entry_word(char* cur_word) {
    if(strcmp(cur_word, ".entry") == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int is_data_word(char* cur_word) {
    if(strcmp(cur_word, ".data") == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int is_string_word(char* cur_word) {
    if(strcmp(cur_word, ".string") == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
