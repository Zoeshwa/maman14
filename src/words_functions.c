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



/*Description: check if a given word is a valid lable*/
/*Input: a string word (pointer to array of chars)*/
/*Output: 1 - true, 0- false*/
int is_valid_lable(char* word){
    char * ptr;
    int i;

    ptr = word;

    /*MAYBE - skip spaces in the begining?*/

    /*starts with A-Z/a-z*/
    if(!IS_UPPERCASE_LETTERS(*ptr) && !IS_LOWERCASE_LETTERS(*ptr)) {
        return 0; /*return false*/
    }

    /*have only max len for labels and end with : and no spaces before ":"*/
    if(strlen(word) > MAX_LABEL_LEN || !is_lable(word)) {
        return 0; /*return false*/
    }

    /*all othe chars is valid*/
    for(i = 0; i < strlen(word) - 1; i++) {
        if(!is_valid_char(*ptr)){
            return 0; /*return false*/
        }
        ptr++;
    }


    /*TODO*/
    /*there is no other label like this*/

    /*its not a save word*/

    return 1; /*return true*/
}