#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "first_pass.h"
#define NUM_OF_COM 16



enum{MOV, CMP, ADD, SUB, NOT, CLR, LEA, INC, DEC, JMP, BNE, RED, PRN, JSR, RTS, STOP,SKIP};
enum{NONE, IMM, DIR, REG_DIR, ERR};
command com_conf[] = {
		{"mov" ,2, MOV,{{IMM, DIR, REG_DIR,-1}, {DIR, REG_DIR,-1}}},
		{"cmp" ,2, CMP,{{IMM, DIR, REG_DIR,-1}, {IMM, DIR, REG_DIR,-1}}},
		{"add",2, ADD,{{IMM, DIR, REG_DIR,-1}, {DIR, REG_DIR,-1}}},
		{"sub",2, SUB,{{IMM, DIR, REG_DIR,-1}, {DIR, REG_DIR,-1}}},
		{"not",1, NOT, {{NONE,-1}, {DIR, REG_DIR,-1}}},
		{"clr",1, CLR, {{NONE,-1}, {DIR, REG_DIR,-1}}},
		{"lea",2, LEA, {{DIR,-1}, {DIR, REG_DIR,-1}}},
		{"inc",1, INC, {{NONE,-1}, {DIR, REG_DIR,-1}}},
		{"dec",1, DEC, {{NONE,-1}, {DIR, REG_DIR,-1}}},
		{"jmp",1, JMP, {{NONE,-1}, {DIR, REG_DIR,-1}}},
        {"bne",1, BNE, {{NONE,-1}, {DIR, REG_DIR,-1}}},
        {"red",1, RED, {{NONE,-1}, {DIR, REG_DIR,-1}}},
        {"prn",1, PRN, {{NONE,-1}, {IMM, DIR, REG_DIR,-1}}},
        {"jsr",1, JSR, {{NONE,-1}, {DIR, REG_DIR,-1}}},
        {"rts",0, RTS, {{NONE,-1}, {NONE,-1}}},
        {"stop",0, STOP, {{NONE,-1}, {NONE,-1}}},
        {"skip",0,SKIP, {{NONE,-1}, {NONE,-1}}}
	};



#define MAX_LEN 80 /*TODO: maybe in the header?*/

File_Config* first_pass(FILE* am_file) {
    /*initilazed varabels*/
    File_Config* file_config;
    char input[MAX_LEN];

    file_config = intialiez_file_config();

    /*for each line in the file*/
    while (fgets(input, MAX_LEN, am_file) != NULL){    

        if (empty_line(input) || comment_line(input)){continue;}
        handle_new_line(file_config, input);
        file_config->curr_line_num++;
    }

    /*checks if needs to continue process since it might have an error*/
    if (file_config->is_valid){
        /*TODO:*/
        update_symbol_table_by_IC(file_config);
    }
    return file_config;
}

void handle_new_line(File_Config* file_config, char* line) {
    char * ptr;
    char cur_word[MAX_LEN];
    int is_line_have_symbol; 
    ptr = line;
    /*get the first word*/
    get_next_word(cur_word, ptr);
    ptr = skip_spaces(ptr);

    is_line_have_symbol = is_lable(cur_word); /*label of the line*/    
    
    if(is_data_storage_ins(line)) { /*ins: .data or .string*/
        if(is_line_have_symbol) {
            /*handle insert data symbol for the command*/
            handle_label(file_config, cur_word, DATA);
            
            /*get next words*/
            ptr += strlen(cur_word);
            get_next_word(cur_word, line);
            ptr = skip_spaces(ptr);
        }

        handle_data_ins(file_config, line, ptr);
        return;

    } else if(is_external_or_entry_ins(line)) { /*.entry or .extranal*/
        
        /*insert symbol with type*/
        if(is_line_have_symbol) {
            ptr += strlen(cur_word);
            get_next_word(cur_word, ptr);
            ptr = skip_spaces(ptr);
        }

        if(is_extern_ins(line)) {
            handle_extren_line(file_config, line, ptr);
        }
        return ;

    } else{ /* is instruction*/
        if (is_line_have_symbol) {
            handle_label(file_config, cur_word, CODE);
            ptr += strlen(cur_word);
            get_next_word(cur_word, ptr);
            ptr = skip_spaces(ptr);
        }

        handle_code_line(file_config, ptr);
        return ;
    }
}

/*Description: Given a command line of type extern - handles the line. That is, it performs validation and, if necessary, enters the symbol table with the appropriate values*/
/*Input: file_config for the current file, line to handle, pointer to the line in the params location*/
void handle_extren_line(File_Config* file_config, char* line, char* curr_ptr) {
    char *ptr, **words;
    int  i;

    ptr = curr_ptr;
    ptr = skip_spaces(ptr);

    /*get the params as words array and validate*/
    words = get_words(ptr);
    if(!is_legal_params(ptr)) { /*print error - line num*/
        PRINT_NUM_LINE_ERROR(file_config->curr_line_num);
        file_config->is_valid = FALSE;
    }

    /*add to symbol table each label*/
    for(i = 0; words[i] != NULL; i++) {
        handle_label(file_config, words[i], EXTERNAL);
    }
}

int is_space(char c)
{
 if( c== ' ' || c == '	')
 	return 1;
 return 0;
}

/* checks if the beggining of the input line is a valid command line */
int is_legal_com(char* input,int i, command* commands_list){
	int j;
	for ( j=0; j < strlen(commands_list[i].act); j++)  /* check if its one of the commands */
	{
		if (input[j] != commands_list[i].act[j] || is_space(input[j])){
			return 0;}
	}	
	return 1;
}

/* desc: gets the action from the command read */
command get_action(char* input, command* commands_list)
{
	command com;
	int i;
	for (i=0; i < NUM_OF_COM; i++)
	{
		if (is_legal_com(input,i, commands_list)){
			com = commands_list[i];
			return com;
		}
	}
	printf("Undifined command name\n");
	com = commands_list[SKIP];
	return com;
}

/* checks if a char read is a number */
int is_number_char(char c){
	if (c>47 && c<58)
		return 1;
	return 0;
}

/* gets a pointer to a number or a '-' and reads the next chars to from the number as a double */
int get_number(char* p){
	double d=0;
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
        return IMM;
	}
	else {
        printf("not a valid number"); /*sarts as a number but gets somthing that is not a number in the middle*/

    }
	
	return d;
}

int is_valid_number_param(char *param){
    if(*param == '-'){
        param++;
    }
    while (*param != '\0'){
        if (!is_number_char(*param)){
            return 0;
        }
        param++;
    }
    return 1;
}

int is_valid_lable_param(char *param) {
    int i;

    if (strlen(param) >30){
        return 0;
    }
    /* Check if the first character is an alphabet character */
    if (!isalpha(param[0]))
        return 0;

    /* Check the rest of the characters */
    for ( i = 1; param[i] != '\0'; i++) {
        if (!isalnum(param[i])) {
            return 0;
        }
    }

    return 1;
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


int is_compatible_types(int acual_type, int* expected_type){
    int i;
    for (i=0; expected_type[i] != -1; i++){
        if (expected_type[i] == acual_type){
            return 1;
        }
    }
    return 0;
}

int is_valid_param_types(int com, char** params, int num_of_params, int param_type[2]){
    int i;
    i=0;
    
    /*fill the types of entered params*/
    if (num_of_params == 0){ /*case of no params*/
        while (i<2){
            param_type[i] = NONE;
            i++;
        }
    }
    else if(num_of_params == 1){ /*case of 1 param*/
        param_type[0] = NONE;
        param_type[1] = get_param_type(params[0]);
    }
    else{/*case of 2 params*/
        for(i=0; i < num_of_params;i++){
            param_type[i] = get_param_type(params[i]);
        }
    }
    for (i=0; i<2;i++){/*comparing between acual read types to possible action types*/
        if (!is_compatible_types(param_type[i], com_conf[com].operands[i])){
            printf("param %d is not compatible of type %d\n", i, param_type[i]);            return 0;
            }
        printf("param %d is compatible of type %d\n", i, param_type[i]);  
    } 
    return 1;
}




int is_valid_com(command com,char** params, int param_types[2]){
    int num_of_params,i;
    num_of_params=0;

    for (i=0; params[i] != NULL ; i++){    /*count num of params in array*/
        num_of_params+=1;
    }
    printf("num of params is:%d\n", num_of_params);
    if (num_of_params != com.num_of_params){
        printf("not compatible num of params\n");
        return 0;
    }
    else if(!is_valid_param_types(com.en, params, num_of_params, param_types)){
        /*error - type of params is not compatible (printed inside)*/
        return 0;
    }
    else{
        return 1;
    }

}

int get_reg_num(char* reg){
    return (int)reg[2];
}

int set_operand_value(char* param, int type){
    if (type == REG_DIR){
        return get_reg_num(param);
    }
    else{
        return get_number(param);
    }
}

Ins_Node** add_extra_ins_words(Ins_Node** head, File_Config* file_config, int param_type[2], char** params){
    int i;
    if (param_type[0] == NONE && param_type[1] == NONE){ /*case of command without params*/
        return head;
    }
    else if (param_type[0] == REG_DIR && param_type[1] == REG_DIR){ /*case of two parameters, both registers*/
        file_config->IC_counter += 1;
        head = insert_ins_node(head, file_config); 
        (*head)->type = REG_DIR;
        (*head)->operrands[0] = get_reg_num(params[0]);
        (*head)->operrands[1] = get_reg_num(params[1]);
    }
    else if(param_type[0] == NONE){/*case of command with only one parameter*/
        file_config->IC_counter += 1;
        head = insert_ins_node(head, file_config);
        (*head)->type = get_param_type(params[0]);

        if ((*head)->type == DIR){ /*if parameter is lable - copy it to node*/
            strcpy((*head)->lable,params[0]);
        }
        else{ /* otherwise update dest operrand*/
            (*head)->operrands[1] = set_operand_value(params[0], (*head)->type);
        }
    }
    else{/*case of command with two parameters*/
        for (i=0; i< 2; i++){
            file_config->IC_counter += 1;
            head = insert_ins_node(head, file_config); 
            (*head)->type = get_param_type(params[i]);

            if ((*head)->type == DIR){ /*if parameter is lable - copy it to node*/
                strcpy((*head)->lable,params[0]);
            }
            else{ /* otherwise update dest operrand*/
                (*head)->operrands[i] = set_operand_value(params[0], (*head)->type);
            }
        }
    }
    return head;
}

void handle_code_line(File_Config* file_config, char *ptr) {

    char **params;
    command com;
    int param_type[2];
    Ins_Node** cur_node;
/*test vars */
    int i;
    i=0;

    ptr = skip_spaces(ptr);
    com = get_action(ptr, com_conf); /*gets first word and checks if valid*/
    printf("action is: %s\n", com.act);
    if (com.en == SKIP){
        printf("not a valid command\n");
        return;
    }
    else{
        ptr += strlen(com.act);
        params = get_words(ptr);     /*get all parameters in an array*/
        
        /*test: print words*/
        while(params[i] != NULL){
            i++;
        }
        if (!is_valid_com(com,params, param_type)){/*checks if valid and updates the params_type if it does*/
            com.en = SKIP;
        }
    }
    if (com.en != SKIP){printf("is a vilid com\n");}
    else{printf("is *not* a valid com\n");}

    /*get last node of list*/
    cur_node = &(file_config->ins_tail);
    if ((*cur_node)->line_number == 0){/*case of first node*/
        intialiez_ins_node(cur_node, com, param_type); 
    }
    else{/*case of any other node*/
        file_config->IC_counter += 1;
        cur_node = insert_ins_node(cur_node, file_config); 
        intialiez_ins_node(cur_node, com, param_type); 
    }
    cur_node = add_extra_ins_words(cur_node, file_config, param_type, params);
}






void handle_data_ins(File_Config* file_config, char* line, char* curr_ptr) {
     
        /* TODO: 7 in page 18 - handle data ins*/
        int i, binary_words_counter;
        char **words, *cur_word;
        Data_Type data_type;

        binary_words_counter = 0, i = 0;
        words = get_words(line);

        /*get the the first word (after the lable if if there is one)*/
        cur_word = words[i];
        if(is_lable(cur_word)) {
            cur_word = words[++i];
        }

        /*check which kind of data type it is*/
        if(is_data_word(cur_word)) {
            data_type = DATA;
        } else {
            data_type = STRING;
        }


        /*TODO: update data table*/
        while (strlen(curr_ptr) > 0)
        {

            /*next word*/

            /*TODO: validate data*/

            /*TODO: convert to int*/

            /*add to DATA table TODO: value set
            counter += number_of_oprends;
            add_data_node_to_table(file_config->data_table, value, is_char, counter);
            number_of_oprends++;
            
            */
        }
        

        /*TODO: update ins*/

        /*update DC_counter*/
        set_file_config_DC(file_config, file_config->DC_counter + binary_words_counter);
}

/*Description: givien a word - check if its legal lable and insert to the lable list if needed*/
/*Input: file_config for the current file, word to handle, type of the lable*/
void handle_label(File_Config* file_config, char* word, Symbol_Type symbol_type) { 
    int counter_value;

    /*validate the starting label*/
    if (!(is_valid_lable(file_config->label_head, word))) {
        PRINT_NUM_LINE_ERROR(file_config->curr_line_num);
        /*ASK: we need to continou?*/
        return;
    }
    /*add to symbol table - get the counter and remove colon*/
    counter_value = get_counter_by_type(file_config, symbol_type);
    remove_colon_at_end(word);

    insert_to_symbol_table(&(file_config->label_head), word, counter_value, symbol_type);
}

/*TODO: */
void update_symbol_table_by_IC(File_Config * file_config) {

}

