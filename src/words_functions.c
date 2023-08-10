#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string_functions.h"


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

int get_sign_value(char curr_char) {

    if (curr_char == '-')
        return -1;
    if (curr_char == '+')
        return 1;

    printf("ERROR - this word dont have a sign like expected\n");
    return 0;
}

/*TODO: move to words*/
int is_valid_lable_param(char *param) {
    int i;

    if (strlen(param) >30){
        return FALSE;
    }
    /* Check if the first character is an alphabet character */
    if (!isalpha(param[0]))
        return FALSE;

    /* Check the rest of the characters */
    for ( i = 1; param[i] != '\0'; i++) {
        if (!isalnum(param[i])) {
            return FALSE;
        }
    }

    return TRUE;
}


int get_param_type(char* param){
    /*see if get words ends with \0*/

    if (*param == '@'){ /*start of a register*/
        param++;
        if (*param == 'r'){
            param++;
            if (*param < 56 && *param > 47) /*is a number between 0 to 7*/
            {
                param++;
                if (*param == '\0'){
                    return REG_DIR;
                }
            } 
        }
        printf("not a valid reg\n");
    }
    else if(is_valid_number_param(param)){       
        return IMM;
    }
    else if(is_valid_lable_param(param)){
        return DIR;
    }
    return ERR;
}

/*TODO: zoe already exist*/
int is_valid_number_param(char *param){
    if(*param == '-'){
        param++;
    }
    while (*param != '\0'){
        if (!isdigit(*param)){
            return 0;
        }
        param++;
    }
    return 1;
}

/*ask ido*/
int is_Ins(char* word){
    if (word[strlen(word)-1] == ':')
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

void remove_colon_at_end(char* word) {
    size_t len = strlen(word);
    /* Check if the last character is ":" */
    if (len > 0 && word[len - 1] == ':') {
        /* Set the last character to the null terminator "\0" */
        word[len - 1] = '\0';

    }
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
        "PSW",
        "PC",
        "data",
        "string",
        "extern", 
        "entry"
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


/*TODO: DELETE delete this and use isdigit instade*/
/* checks if a char read is a number 
int is_number_char(char c){
    if(isdigit(c)) {
    	return TRUE;
    }
	return FALSE;
}*/

/* gets a pointer to a number or a '-' and reads the next chars to from the number as a double */
int get_number(char* p){
	int num, sign, is_valid;
    num = 0;
	sign = 1;
    is_valid = TRUE;

	if(!isdigit(*p)) {
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

	while (isdigit(*p) && is_valid == TRUE){
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

int is_valid_int_param(char *curr_word ,int curr_line_num) {
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
