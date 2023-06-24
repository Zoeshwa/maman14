#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testers.h"

#define PASS_PRINT(expected_result) printf("V - PASS: Expected result (%d) matches the actual result.\n", expected_result)
#define FAIL_PRINT(test_number, expected_result, result) printf("X - FAIL: test_num (%d), Expected (%d) - Actual result (%d)\n",test_number, expected_result, result)


void tester_O_int_I_charP(int (*function)(char*), char* input, int expected_result, int test_number) {
    int result;
    result = function(input);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}

void tester_get_next_word(char * str) {
    char * ptr;
    char cur_word[MAX_LEN];

    ptr = str;
    
    while (strlen(ptr) > 0) 
    {
        printf("This is str:|%s|\n", ptr);
        get_next_word(cur_word, ptr);
        ptr= skip_spaces(ptr);
        ptr =  ptr + strlen(cur_word);
        printf("cur_word:|%s|\n", cur_word);
    }
}



void print_file_config(File_Config* file_config) {

}

/*
int tester_is_valid_lable(char * word, int expacted) 
{
    int result;

    printf("tester_is_valid_lable(%s, %d): ", word, expacted);
    result = is_valid_lable(word);
    if(result == expacted) {
        GOOD;
        return 1;
    } else {
        NOT_GOOD;
        return 0;
    }
}
*/


/*

    
*/

