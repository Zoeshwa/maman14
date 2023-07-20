#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "line_functions.h"

#define MAX_LENGTH 80


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


/*TODO: ido parse*/

char* skip_spaces(char* p){
	while (*p == ' ' || *p == '	'){
		p++;
	}
	return p;
}

char** parsing(char* p){
    char tmp_element[MAX_LENGTH], **splited, *element;
    int comma_flag, s_index, tmp_index;
    comma_flag=0, s_index=0, tmp_index=0;

    splited = (char**)malloc(MAX_LENGTH * sizeof(char*)); /*alocating for ellements array */
    p = skip_spaces(p);
    if (*p == ',') { /* first comma in illegal*/
        printf("illegal comma\n");
        comma_flag=1;
        p++;
    }
    p = skip_spaces(p);
    while (*p != '\n' && *p != '\0'){ /*till end of line*/
        printf("cur is:%c\n", *p);
        if (*p == ',' && comma_flag){ /*second or more commas in a row*/
            printf("more than one consecutive commas\n");
        }
        else if (*p == ','){ /*comma after element, save the element in the array*/
            tmp_element[tmp_index] = '\0';
            comma_flag=1;
            char* element = (char*)malloc((strlen(tmp_element)+1) * sizeof(char));
            strcpy(element, tmp_element);
            splited[s_index++] = element; 
            tmp_index=0;
            printf("splited[%d] is: %s\n", s_index-1, splited[s_index-1]);
        }
        else{
            tmp_element[tmp_index++] = *p; /*middle of an element read*/
        }
        p=skip_spaces(p);
        p++;
    }
    splited[s_index] = NULL;
    return splited;

}

int ido_main_for_pars(int argc, char* argv[]) {

    FILE* src_file;
    char** parsed;
    char  input[MAX_LENGTH], *file_name;
    int i;
    file_name = argv[1];
    src_file = fopen(file_name, "r");
    while (fgets(input, MAX_LENGTH, src_file) != NULL) {
        printf("input is: %s", input);
        parsed = parsing(input);
        for(i=0; parsed[i] != NULL;i++){
            printf("next word is: %s\n", parsed[i]);
        }

    }









    return 0;
}