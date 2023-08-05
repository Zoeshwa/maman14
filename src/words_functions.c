#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "words_functions.h"

#define ZERO_IN_ASCII 48

int is_Ins(char* word){
    if (word[strlen(word)-1] == ':')
        return TRUE;
    return FALSE;
}

int is_space(char c)
{
 if( c== ' ' || c == '\t')
 	return TRUE;
 return FALSE;
}

int is_end_line(char c)
{
 if( c== '\n' || c == EOF || c == '\0')
 	return TRUE;
 return FALSE;
}

/*Description: check if a given char is a number or a letter*/
/*Input: a char to check*/
/*Output: true if the char is a number or a letter, else - false*/
int is_letter_or_num_char(char c){
    /*TODO: use isalpha for a-z, A-Z*/
    if (isdigit(c) || IS_UPPERCASE_LETTERS(c) || IS_LOWERCASE_LETTERS(c))
        return TRUE;
    return FALSE;
}

int is_visible_chars_only(char * input) {
    char * curr_char;

    curr_char = input;
    /*Check all characters in a string*/
    while(*curr_char != EOF && *curr_char != '\0'){
        if(!isprint(*curr_char)) { /*if current char is not visible char*/
            return FALSE;
        }
        curr_char++;
    }
    return TRUE; 
}

/*Description: The function checks if the string is surrounded by quotation marks*/
/*Input: a string to check*/
/*Output: true  = 1,  false = 0*/
int is_valid_quotes(char* word) {
    char* curr_char;

    curr_char = word;

    if(*curr_char != QUOTES) {
        return FALSE;
    }

    curr_char++;
    
    while(*curr_char != EOF && *curr_char != '\0'){
        curr_char++;
    }

    if(*(curr_char - 1) != QUOTES) {
        return FALSE;
    }
    return TRUE; 
}

int is_valid_string_param(char * word, int line_number) {
    int is_valid;
    is_valid = TRUE;

    if(!is_visible_chars_only(word)){
        ERROR_INVALID_CHARS(line_number);
        is_valid = FALSE;
    }

    if(!is_valid_quotes(word)) {
        ERROR_INVALID_QUOTES(line_number);
        is_valid = FALSE;
    }

    return is_valid;
}

/*Description: check if a given word is a lable - end with ":"*/
/*Input: a string word (pointer to array of chars)*/
/*Output: 1 - true, 0- false*/
int is_lable(char* word) {
    char * ptr;

    ptr = word + strlen(word) - 1; /*go to last char*/
    /*end with : and no spaces before :*/
    if(*ptr != COLON) {
        return FALSE;
    }
    return TRUE;
}

void remove_colon_at_end(char* word) {
    size_t len = strlen(word);
    /* Check if the last character is ":" */
    if (len > 0 && word[len - 1] == ':') {
        /* Set the last character to the null terminator "\0" */
        word[len - 1] = '\0';

    }
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
    return (is_type_ins(is_data_word, input) || is_type_ins(is_word_equals_string, input));
}

int is_type_storge_string_ins(char * input) {
    return is_type_ins(is_word_equals_string, input);
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

int is_word_equals_string(char* cur_word) {
    if(strcmp(cur_word, ".string") == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*TODO*/
/* Function to get the array of saved words and the number of elements in the array */
void get_saved_words(const char*** saved_words, int* num_saved_words) {
    /* Simulated implementation - replace this with the actual implementation to get saved words */
    static const char* saved_words_array[] = {
        /*storage commands*/
        ".data",
        ".string",
        ".entry",
        ".extern",
        /*commands*/
        "mov",
        "cmp",
        "add",
        "sub",
        "not",
        "clr",
        "lea",
        "inc",
        "dec",
        "jmp",
        "bne",
        "red",
        "prn",
        "jsr",
        "rts",
        "stop",
        /*registers*/
        "r0",
        "r1",
        "r2",
        "r3",
        "r4",
        "r5",
        "r6",
        "r7",
        /*TODO: check if really save word*/
        "PSW",
        "PC",
        "data",
        "string",
    };
    *saved_words = saved_words_array;
    *num_saved_words = sizeof(saved_words_array) / sizeof(saved_words_array[0]);
}

/* Function to check if a word is a saved word */
int is_saved_word(const char* word) {
    const char** saved_words;
    int num_saved_words, i;

    /* Get the array of saved words and the number of elements */
    get_saved_words(&saved_words, &num_saved_words);

    for (i = 0; i < num_saved_words; i++) {
        if (strcmp(word, saved_words[i]) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

int get_sign_value(char curr_char) {

    if (curr_char == '-')
        return -1;
    if (curr_char == '+')
        return 1;

    printf("ERROR - this word dont have a sign like expected\n");
    return 0;
}

/*TODO: DELETE delete this and use isdigit instade*/
/* checks if a char read is a number */
int is_number_char(char c){
    if(isdigit(c)) {
    	return TRUE;
    }
	return FALSE;
}

/* gets a pointer to a number or a '-' and reads the next chars to from the number as a double */
int get_number(char* p){
	int num, sign, is_valid;
    num = 0;
	sign = 1;
    is_valid = TRUE;

	if(!is_number_char(*p)) {
        sign = get_sign_value(*p);
        /* DELETE
            if (*p == '-'){
                sign = -1;
            } else if(*p != '+') {
                is_valid = FALSE;
            }
        */
        p++;
    }

    /*nhjh*/

	while (is_number_char(*p) && is_valid == TRUE){
		num = num * 10 + ((*p) - ZERO_IN_ASCII);
		p++;
	}

	if (is_end_line(*p)){ /*end of number */
		num = sign * num;
	} else {
        printf("not a valid number"); /*sarts as a number but gets somthing that is not a number in the middle*/
    }
	
	return num;
}

int is_valid_int_param(char *curr_word,int curr_line_num) {
    char *p;
    int sign;

    p = curr_word;
    sign = 1;

    if(!isdigit(*p)) {
        sign = get_sign_value(*p);
        p++;
    }

    while (isdigit(*p) && sign != 0){
		p++;
	}

    if (is_end_line(*p)){ /*end of number */
        return TRUE;
	} else {
        ERROR_INVALID_NUM(curr_line_num);
        return FALSE;
    }
}
