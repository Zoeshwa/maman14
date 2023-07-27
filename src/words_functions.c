#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

int is_visible_chars_only(char * input) {
    char * curr_char;

    curr_char = input;

    while(*curr_char != EOF && *curr_char != '\0'){
        /*TODO: need to fix and understand which is not visible chars*/
        if(*curr_char < 33 || *curr_char > 126) { /*if current char is not visible char*/
            return FALSE;
        }
        *curr_char++;
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

int is_space(char c)
{
 if( c== ' ' || c == '	')
 	return 1;
 return 0;
}

/* checks if a char read is a number */
int is_number_char(char c){
	if (c>47 && c<58)
		return 1;
	return 0;
}


/* gets a pointer to a number or a '-' and reads the next chars to from the number as a double */
int get_number(char* p){
	int d=0;
	int neg = 1;
	
	if (*p == '-'){
		neg = -1;
		p++;
	}
	while (is_number_char(*p)){
		d = d*10 + ((*p)-48);
		p++;
	}
	if (*p == '\0'){ /*end of number */
		d = neg*d;
        return d;
	}
	else {
        printf("not a valid number"); /*sarts as a number but gets somthing that is not a number in the middle*/

    }
	
	return d;
}