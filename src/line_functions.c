#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_functions.h"

/*Description: check if a given line is empty*/
/*Input: a string line (pointer to array of chars)*/
/*Output: 1 - true, the line have only space chars, 0- false the line is not empty*/
int empty_line(char* line){
    char* pointer = line;
    pointer = skip_spaces(pointer);

    if (*pointer == '\n' || *pointer == '\0' || *pointer == EOF){
        return TRUE; 
    }
    else{
        return FALSE; 
    }
}

/*Description: check if a given line is a commant line*/
/*Input: a string line (pointer to array of chars)*/
/*Output: 1 - true, the line is a commant, 0- false the line is not a commant*/
int comment_line(char* line){
    char* pointer = line;
    pointer = skip_spaces(pointer); /*ASK: where it is? */
    if (*pointer == ';'){
        return TRUE; 
    }
    else{
        return FALSE;
    }
}

/*Description: gets a pointer and moves it forward untill reaches non white char.*/
/*Input: pointer to string*/
/*Output: Returns a pointer to the first non-white character*/
char* skip_spaces(char* p){
	while (*p == ' ' || *p == '\t'){
		p++;
	}
	return p;
}

/*TODO: check why ptr and return value*/
char* get_next_word(char* word, char* line){
    int i = 0;
    char * ptr;
    ptr = line; 
    ptr = skip_spaces(ptr);
    while(*ptr != '\n' && *ptr != EOF && *ptr != ' ' && *ptr != '\t'){
        word[i] = *ptr;
        i++;
        ptr++;
    }
    word[i] = '\0';
    return word;
}

/*Description: The function extracts from a line the next word in the line and puts it in the word variable.*/
/*Input: word - the varbiale to store the next word, line - pointer to position in line*/
/*Output: Returns the pointer to the line at the position after the word*/
char* get_next_word_no_comma(char* word, char* line){
    int i = 0;
    char * ptr;

    ptr = line;
    /*go to the next not space char*/
    ptr = skip_spaces(ptr);
    while(*ptr != '\n' && *ptr != EOF && *ptr != ' ' && *ptr != '\t' && *ptr != ',' && *ptr != '\0'){
        word[i] = *ptr;
        i++;
        ptr++;
    }
    word[i] = '\0'; /*mark the end of the word*/
    return ptr; /*return the current position in line*/
}

/*Description: The function extracts the words from the line and returns an array of words. The words are without spaces and without commas.*/
/*Input: line - pointer to position in line*/
/*Output: An array of the extracted words*/
char** get_words(char *line) {
    char copy_line[MAX_LEN], *p, **words, curr_word[MAX_LEN], *tmp;
    int i;
    i = 0;
    strcpy(copy_line, line);
    words = (char**)malloc(MAX_LEN * sizeof(char*));
    p = copy_line;
    p = skip_spaces(p);
    if (*p == '\0' && *p == EOF && *p == '\n'){
        words[i] = NULL;
        return words;
    }

    while (*p != '\0' && *p != EOF && *p != '\n')
    {
        if (*p == ','){p++;}
        p = get_next_word_no_comma(curr_word, p);
        if(curr_word[0] != '\0' ) {
            tmp = (char*)malloc((strlen(curr_word)+1) * sizeof(char));
            strcpy(tmp, curr_word);
            words[i++] = tmp;
        }
        p = skip_spaces(p);
    }
    words[i] = NULL;
    return words;
}

int is_legal_params(char *line, int line_num) {
    char copy_line[MAX_LEN], *p;
    int comma_flag;
    strcpy(copy_line, line);

    p = copy_line;
    comma_flag = FALSE;
    p = skip_spaces(p);
    if (empty_line(line)){
        return 1;
    }
    
    /*first not space char is comma*/
    if(*p == ',') {
        ERROR_ILLEGAL_COMMA(line_num);
        return FALSE;
    }
    /*start of the first word*/
    comma_flag = TRUE;
    while (*p != '\0' && *p != EOF && *p != '\n')
    {
        if(*p == ',') {
            if(comma_flag == TRUE) { /*there is more then one comma in a row*/
                ERROR_MULTIPLE_COMMAS(line_num);
                return FALSE;
            } else {
                if(comma_flag == FALSE) {
                    comma_flag = TRUE;
                    p++;
                }
            }
        } else if( *p != '\0' && *p != EOF && *p != '\n') {
            if(comma_flag == FALSE) { /*missing a comma*/
                ERROR_MISSING_COMMA(line_num);
                return FALSE;
            }
            comma_flag = FALSE;
            while (*p != ',' && *p != '\0' && *p != EOF && *p != '\n' && *p != ' ' && *p != '\t')
            {
                p++;
            }
        }
        p = skip_spaces(p);
    }
    if(*p == '\0' || *p == EOF || *p == '\n') {
        /*the final word?*/
        if(comma_flag == TRUE) {
            printf("2\n");
            ERROR_ILLEGAL_COMMA(line_num);
            return FALSE;
        }
    }
    return TRUE;
}

void free_words(char** words) {
    int i, num_words;
    if (words == NULL) {
        return; /*Nothing to free*/
    }

    /*Find the number of words by iterating until a NULL pointer is encountered*/
    num_words = 0;
    while (words[num_words] != NULL) {
        num_words++;
    }


    for (i = 0; i < num_words; i++) {
        if (words[i] != NULL) {
            free(words[i]); /* Free each individual string */
            words[i] = NULL;
        }
    }

    free(words); /* Free the array of char pointers*/
    words = NULL;

}

/*Description: The function returns how many words there are in an array of words*/
/*Input: an array of words*/
/*Output: number of words in the array*/
int get_len_words_array(char ** words) {
    int num_words;
    if (words == NULL) {
        return 0 ;
    }

    num_words = 0;
    while (words[num_words] != NULL) {
        num_words++;
    }
    return num_words;
}

char* skip_next_word(char* line, char *curr_ptr) {
    char* p;

    p = curr_ptr;

    p = skip_spaces(p);
    while (!is_space(*p) && !is_end_line(*p))
    {
        p++;
    }
    p = skip_spaces(p);

	return p;
}

/*DELETE*/
void print_words(char** words, int len) {
    int i;

    printf("\tprint_words:\n");
    for(i = 0; i< len; i++) {
        printf("\twords[%d]=|%s|\n", i, words[i]);
    }
    printf("\tEND print_words\n");

}