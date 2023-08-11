#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string_functions.h"

/* Description: Checks if a character is a space kind (space or tab).
   Input: The character to be checked.
   Output: Returns 1 if the character is a space or tab, otherwise returns 0.
*/
int is_space(char c) {
 if( c== ' ' || c == '\t')
 	return TRUE;
 return FALSE;
}

/* Description: Checks if a character is the end of a line, EOF, or null terminator.
   Input: The character to be checked.
   Output: Returns 1 if the character is '\n', EOF, or '\0', otherwise returns 0.
*/
int is_end_line(char c) {
 if( c== '\n' || c == EOF || c == '\0')
 	return TRUE;
 return FALSE;
}

/* Description: Returns the sign value of a character ('+' or '-'). It is assumed that a signal is sent which is a sign
   Input: The character to be checked.
   Output: Returns 1 for '+' sign, -1 for '-' sign, and 0 for any other character wich is error.
    If the character is not '+' or '-', an error message is printed.
*/
int get_sign_value(char curr_char) {

    if (curr_char == '-')
        return -1;
    if (curr_char == '+')
        return 1;

    printf("ERROR - this word dont have a sign like expected\n");
    return 0;
}

/* Description: Validates whether a parameter is a valid label word based on certain criteria.
   Input: The parameter to be validated.
   Output: Returns 1 if the parameter is a valid label, otherwise returns 0.
           A valid label must meet the following conditions:
           - Its length is at most 31 characters.
           - The first character is an alphabet character.
           - The rest of the characters are either alphabet characters or digits.
*/
int is_valid_lable_param(char *param) {
    int i;

    if (strlen(param) > MAX_LABLE_LEN){
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
    }
    else if(is_valid_number_param(param)){ 
        return IMM;
    }
    else if(is_valid_lable_param(param)){
        return DIR;
    }
    return ERR;
}

/* Description: Checks whether a given parameter is a valid numeric parameter.
   Input: The parameter to be checked.
   Output: Returns 1 if the parameter is a valid numeric parameter, otherwise returns 0.
           A valid numeric parameter may start with '+' or '-' followed by digits only (no dot).
*/
int is_valid_number_param(char *param){
    if(*param == '-' || *param == '+'){
        param++;
    }

    while (*param != '\0'){
        if (!isdigit(*param)){
            return FALSE;
        }
        param++;
    }
    return TRUE;
}


/* Description: Checks whether a given string consists only of visible characters.
   Input: The string to be checked.
   Output: Returns 1 if the string contains only visible characters, otherwise returns 0.
           Visible characters include printable characters and non-printable characters are considered not visible.
*/
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

/* Description: Checks whether the given input represents an external or entry instruction.
   Input: The input string to be checked.
   Output: Returns 1 if the input is an external or entry instruction, otherwise returns 0.
           An external instruction is identified by the ".extern" keyword and an entry instruction is identified by the ".entry" keyword.
*/
int is_external_or_entry_ins(char* input) {
   return (is_type_ins(is_extern_word, input) || is_type_ins(is_entry_word, input));
}

/* Description: Checks whether the given current word matches the ".extern" keyword.
   Input: The current word to be checked.
   Output: Returns 1 if the current word is equal to the ".extern" keyword, otherwise returns 0.
*/
int is_extern_word(char* cur_word) {
    if(strcmp(cur_word, ".extern") == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}


/* Description: Checks whether the given input represents a data storage instruction.
   Input: The input string to be checked.
   Output: Returns TRUE if the input is a data storage instruction, otherwise returns FALSE.
           A data storage instruction is identified by the ".data" keyword or the ".string" keyword.
*/
int is_data_storage_ins(char * input) {
    return (is_type_ins(is_data_word, input) || is_type_ins(is_word_equals_string, input));
}

/* Description: Checks whether the given input represents a string storage instruction.
   Input: The input string to be checked.
   Output: Returns TRUE if the input is a string storage instruction, otherwise returns FALSE.
           A string storage instruction is identified by the ".string" keyword.
*/
int is_type_storge_string_ins(char * input) {
    return is_type_ins(is_word_equals_string, input);
}

/* Description: Checks whether the given input represents an external instruction.
   Input: The input string to be checked.
   Output: Returns TRUE if the input is an external instruction, otherwise returns FALSE.
           An external instruction is identified by the ".extern" keyword.
*/
int is_extern_ins(char* input) {
   return is_type_ins(is_extern_word, input);
}


/* Description: Checks whether the given current word matches the ".entry" keyword.
   Input: The current word to be checked.
   Output: Returns 1 if the current word is equal to the ".entry" keyword, otherwise returns 0.
*/
int is_entry_word(char* cur_word) {
    if(strcmp(cur_word, ".entry") == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* Description: Checks whether the given current word matches the ".data" keyword.
   Input: The current word to be checked.
   Output: Returns 1 if the current word is equal to the ".data" keyword, otherwise returns 0.
*/
int is_data_word(char* cur_word) {
    if(strcmp(cur_word, ".data") == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}


/* Description: Checks whether the given current word matches the ".string" keyword.
   Input: The current word to be checked.
   Output: Returns 1 if the current word is equal to the ".string" keyword, otherwise returns 0.
*/
int is_word_equals_string(char* cur_word) {
    if(strcmp(cur_word, ".string") == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* Description: Checks whether the given string parameter is a valid string containing visible characters and properly enclosed within double quotes.
   Input: The string parameter to be checked, and the line number for error reporting.
   Output: Returns 1 if the string parameter is a valid string, otherwise returns 0.
           An error message is also generated if the string parameter contains invalid characters or improperly enclosed quotes.
*/
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

/* Description: Removes a trailing colon (":") from the given word.
   Input: The word from which the trailing colon should be removed.
   Output: The word with the trailing colon removed, if present.
*/
void remove_colon_at_end(char* word) {
    size_t len = strlen(word);
    /* Check if the last character is ":" */
    if (len > 0 && word[len - 1] == ':') {
        /* Set the last character to the null terminator "\0" */
        word[len - 1] = '\0';

    }
}

/* Description: Checks whether the given input matches a specific instruction type determined by the provided function.
   Input: A function pointer that takes a string as input and returns an integer (used to check the instruction type), 
          and the input string to be checked.
   Output: Returns 1 if the input matches the specified instruction type, otherwise returns 0.
*/
int is_type_ins(int (*function)(char*), char* input) {
    char * ptr;
    char cur_word[MAX_LEN + 1];
    int result; 

    result = FALSE;
    ptr = input;

    get_next_word(cur_word, ptr);
    ptr = skip_spaces(ptr); 
    
    if(is_lable(cur_word)) {
        ptr =  ptr + strlen(cur_word);
        get_next_word(cur_word, ptr);
    }

    if(function(cur_word)) {
        result = TRUE;
    }

    return result;
}

/* Description: Retrieves the array of predefined saved words and the number of elements in the array.
   Input: Pointers to store the array of saved words and the number of saved words.
   Output: Updates the pointers with the array of saved words and the corresponding number of elements.
*/
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

/* Description: Checks if a given word is a saved word by comparing it to the predefined list of saved words.
   Input: The word to be checked.
   Output: Returns TRUE if the word is a saved word, otherwise returns FALSE.
*/int is_saved_word(const char* word) {
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

/* Description: Reads the characters from a pointer to a number or sign char and converts them to an integer. The given word is assumed to be a number
   Input: A pointer to the characters forming the number.
   Output: Returns the integer value of the read number.
*/
int get_number(char* p){
	int num, sign, is_valid;
    num = 0;
	sign = 1;
    is_valid = TRUE;

	if(!isdigit(*p)) {
        sign = get_sign_value(*p);
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

/* Description: Checks if a given string represents a valid integer parameter.
   Input: The string to be checked and the current line number for error reporting.
   Output: Returns TRUE if the string is a valid integer parameter, otherwise returns FALSE.
*/
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
