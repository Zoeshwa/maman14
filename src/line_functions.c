#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "line_functions.h"


/*Description: check if a given line is empty*/
/*Input: a string line (pointer to array of chars)*/
/*Output: 1 - true, the line have only space chars, 0- false the line is not empty*/
int empty_line(char* line){
    char* pointer = line;
    pointer = skip_spaces(pointer);
    if (*pointer == '\n' || *pointer == '\0'){ /*TODO/ASK: add EOF?*/
        return 1; /*return true*/
    }
    else{
        return 0; /*return false*/
    }
}

/*Description: check if a given line is a commant line*/
/*Input: a string line (pointer to array of chars)*/
/*Output: 1 - true, the line is a commant, 0- false the line is not a commant*/
int comment_line(char* line){
    char* pointer = line;
    pointer = skip_spaces(pointer); /*ASK: where it is? */
    if (*pointer == ';'){
        return 1; /*true*/
    }
    else{
        return 0; /*false*/
    }
}

/* gets a pointer and moves it forward untill reaches non white char */
char* skip_spaces(char* p){
	while (*p == ' ' || *p == '	'){
		p++;
	}
	return p;
}

/*TODO: check why ptr and return value*/
/*OLD V*/
char* get_next_word_old(char* str, char* word, char* ptr){
    int i=0;
    ptr = skip_spaces(ptr);
    while(*ptr != '\n' && *ptr != EOF && *ptr != ' ' && *ptr != '\t'){
        word[i] = *ptr;
        i++;
        ptr++;
    }
    word[i] = '\0';
    return word;
}

char* get_next_word(char* word, char* line){
    int i=0;
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

