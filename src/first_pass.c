#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "first_pass.h"

#define MAX_LEN 80 //TODO: maybe in the header?


    

//TODO:
int is_valid_Ins(char* Ins){
    if (strlen(Ins)>= 31){
        return 0;
    }
    //needs a function that checks its not a saved word
    // missing a function that goes over Ins list to check Ins os not defined twice
    while (is_valid_char(*Ins)){Ins++;}
    if (*Ins == ':'){
        return 1;
    }
    else{
        return 0;
    }
}