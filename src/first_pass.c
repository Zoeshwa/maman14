#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "first_pass.h"



static const Command com_conf[] = {
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

File_Config* first_pass(char* am_file_name) {
    /*initilazed varabels*/
    File_Config* file_config;
    char input[MAX_LEN];
    FILE* am_file;

    printf("\t---------START FIRST PASS-----------\n");
    file_config = intialiez_file_config();
    am_file = fopen(am_file_name, "r");
    if (am_file == NULL) {ERROR_READING_FILE("am_file_name");}


    /*for each line in the file*/
    while (fgets(input, MAX_LEN, am_file) != NULL){    
        printf("\tline %d: %s\n", get_curr_line_number(file_config), input);

        if (empty_line(input) || comment_line(input)){
            update_line_num_file(&file_config);
            continue;
        }
        
        handle_new_line(file_config, input);
        update_line_num_file(&file_config);
    }

    /*checks if needs to continue process since it might have an error*/
    if (get_is_valid_file(file_config)){
        /*update counters*/
        update_counters_label_list(get_label_node_head(file_config), get_IC_counter(file_config));
        update_counters_data_list(get_data_node_head(file_config), get_IC_counter(file_config));
    }
    printf("\t---------END FIRST PASS-----------\n");
    fclose(am_file);

    return file_config;
}

void handle_new_line(File_Config* file_config, char* line) {
    char * ptr;
    char cur_word[MAX_LEN];
    int is_line_have_symbol; 
    
    ptr = line;

    /*get the first word - assuming that wehave at least one space between label and the rest of the line*/
    get_next_word(cur_word, ptr);
    ptr = skip_spaces(ptr);

    is_line_have_symbol = is_lable(cur_word); /*label of the line*/    
    
    if(is_data_storage_ins(line)) { /*ins: .data or .string*/
        if(is_line_have_symbol) {
            /*skip the label word*/
            ptr = skip_next_word(line, ptr);
            
            /*handle insert data symbol for the command*/
            handle_label(file_config, cur_word, DATA);
        }

        /*skip the string/data word*/
        ptr = skip_next_word(line, ptr);

        handle_data_ins(file_config, line, ptr);
        return;

    } else if(is_external_or_entry_ins(line)) { /*.entry or .extranal*/
        /*insert symbol with type*/
        if(is_line_have_symbol) {
            /*skip label word*/
            ptr = skip_next_word(line, ptr);
        }
        /*skip the extern/entry word*/
        ptr = skip_next_word(line, ptr);

        if(is_extern_ins(line)) {
            handle_extren_line(file_config, line, ptr);
        }
        return ;

    } else{ /* is instruction*/
        if (is_line_have_symbol) {
            handle_label(file_config, cur_word, CODE);
            ptr = skip_next_word(line, ptr);

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
    if(!is_legal_params(ptr, get_curr_line_number(file_config))) {
        update_validity_file_config(&file_config, FALSE);
    }

    /*add to symbol table each label*/
    for(i = 0; words[i] != NULL; i++) {
        handle_label(file_config, words[i], EXTERNAL);
    }

    free_words(words);
}


int is_valid_param_types(int com, char** params, int num_of_params, int param_type[2]){
    int i;
    i = 0;
    
    /*fill the types of entered params*/
    if (num_of_params == 0){ /*case of no params*/
        while (i < 2){
            param_type[i] = NONE;
            i++;
        }
    }
    else if(num_of_params == TRUE){ /*case of 1 param*/
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
            return FALSE;
            }
    } 
    return 1;
}

Ins_Node** add_extra_ins_words(Ins_Node** head, File_Config* file_config, int param_type[2], char** params){
    int i, j;
    char* bin_word;
    
    j = 0;

    if (param_type[0] == REG_DIR && param_type[1] == REG_DIR){ /*case of two parameters, both registers*/
        head = insert_ins_node(head,  get_IC_counter(file_config), get_curr_line_number(file_config)); 
        update_IC_counter(&file_config, 1);
        set_ins_type(head, REG_DIR);
        set_ins_operand(head, 0, get_reg_num(params[0]));
        set_ins_operand(head, 1, get_reg_num(params[1]));

        bin_word = (char*)calloc(13,sizeof(char));
        set_bin_rep_ins_node(head, bin_word);
        make_bin_REG_word(head, 0); 

    } else {    
        for (i = 0; i < 2; i++){
            if(param_type[i] == NONE){ /* if no params or 1 param set the src and dest accordinly with 0*/
                set_ins_operand(head, i, 0);
            } else if (param_type[i]){/*otherwise another node should be added with values of params*/
                head = insert_ins_node(head,  get_IC_counter(file_config), get_curr_line_number(file_config)); 
                
                update_IC_counter(&file_config, 1);
                set_ins_type(head, get_param_type(params[j]));
                
                if (i == 0) {
                    set_ins_operand(head, 0, set_operand_value(params[j++], head));
                    set_ins_operand(head, 1, NONE);
                } else {
                    set_ins_operand(head, 0, NONE);
                    set_ins_operand(head, 1, set_operand_value(params[j++], head));
                }
                make_bin_extra_word(head, i);
            }
        }
    
    }
    return head;
}




void handle_code_line(File_Config* file_config, char *ptr) {

    char **params;
    Command com;
    int param_type[2];
    Ins_Node **cur_node, *ins_tail;

    ins_tail = get_file_ins_tail(file_config); 

    ptr = skip_spaces(ptr);
    com = get_action(ptr, com_conf); /*gets first word and checks if valid*/
    if (com.en == SKIP){
        ERROR_NOT_VALID_COMMAND_NAME(get_curr_line_number(file_config));
        update_validity_file_config(&file_config, FALSE);
        return;
    }

    ptr += strlen(com.act);
    if (!is_legal_params(ptr, get_curr_line_number(file_config))){ /*checks the syntax and correctness of the parameters*/
        com.en = SKIP;
        update_validity_file_config(&file_config, FALSE);
        return;
    }



    params = get_words(ptr);     /*get all parameters in an array*/

    if (!is_valid_com(com, params, param_type, get_curr_line_number(file_config))){/*checks if the entered params are compatible with the command's requirements*/
        com.en = SKIP;
        update_validity_file_config(&file_config, FALSE);
        return;
    }


    /*get last node of list*/
    cur_node = &ins_tail;

    /*initialize first node*/
    if (get_ins_line_number(*cur_node)== -1){
        intialiez_ins_node(cur_node, com, param_type);
        make_bin_ins_word(cur_node);  
        update_IC_counter(&file_config, 1);  
    }
    else{/*initialize any other node*/
        cur_node = insert_ins_node(cur_node, get_IC_counter(file_config), get_curr_line_number(file_config)); 
        intialiez_ins_node(cur_node, com, param_type); 
        update_IC_counter(&file_config, 1);
        make_bin_ins_word(cur_node); 
    }
    cur_node = add_extra_ins_words(cur_node, file_config, param_type, params); /*updates the IC list according to number of extra words needed*/
    update_ins_tail_file(&file_config, *cur_node);
    free_words(params);
}

/*Description: The function handles the command line that stores arguments in memory.
It performs validation on the line according to the command type and calls the functions that insert the arguments into the data list*/
/*Input: file_config for the current file, A line in which there is a prompt for memory allocation (string/data),
 a pointer to the current position in the line (after the label if its have and after the command word)*/
void handle_data_ins(File_Config* file_config, char* line, char *curr_ptr) {
    int i, binary_words_counter, len, curr_line_num;
    char **words, *cur_word;

    curr_line_num = get_curr_line_number(file_config);
    binary_words_counter = 0, i = 0;
    /*get array of the words in the line*/
    words = get_words(line);
    len = get_len_words_array(words);
    
    if(len < 2) { 
        ERROR_MISSING_ARGUMENTS(curr_line_num);
        update_validity_file_config(&file_config, FALSE);
        return;
    }

    /*get the the first word*/
    cur_word = words[i];
    if(is_lable(cur_word)) { /*if the first word is a label*/
        cur_word = words[++i]; /*get the command word*/
        if(2 >= len) { /*only 2 words include the label - not good*/
            ERROR_MISSING_ARGUMENTS(curr_line_num);
            update_validity_file_config(&file_config, FALSE);
            return;
        }
    }
    
    /*check the commas between params and update validity of the file*/
    update_validity_file_config(&file_config, is_legal_params(curr_ptr, curr_line_num));

    ++i; /*index of current words is the first param*/

    /*check which kind of data type it is*/
    if(is_data_word(cur_word)) {
        binary_words_counter = handle_data_int_store(file_config, words, len, i);
    } else {
        binary_words_counter = handle_data_string_store(file_config, words, len, i);
    }

    /*update DC_counter*/
    update_DC_counter(&file_config, binary_words_counter);
    free_words(words);
}

/*Description: The function validates the arguments of the data command and inserts them, if they are valid, into the data list*/
/*Input: file_config for the current file, words - An array of the words in the current line, len - the array length, curr_index - index to the first parameter*/
/*Output: number of the parmaters that added to the list*/
int handle_data_int_store(File_Config* file_config, char **words, int len, int curr_index) {
    char *curr_word;
    int curr_line_num, num_of_params, curr_number;
    Data_Node **data_head, **data_tail;
    
    num_of_params = 0;
    curr_line_num = get_curr_line_number(file_config);
    data_head = get_file_data_head_address(file_config);
    data_tail = get_file_data_tail_address(file_config); 

    /*for each param*/
    for(; curr_index < len; curr_index++) {
        curr_word = words[curr_index];
        /*validate the param*/
        if(!is_valid_int_param(curr_word, curr_line_num)) {
            update_validity_file_config(&file_config, FALSE);
            continue;
        }
        /*add to data list as a node if its valid*/
        curr_number = get_number(curr_word);
        add_data_node(data_head, data_tail, curr_number, DATA);
        num_of_params++;
    }

    return num_of_params;
}

/*Description: The function validates the argument of the string command and inserts it, if its valid, into the data list*/
/*Input: file_config for the current file, words - An array of the words in the current line, len - the array length, curr_index - index to the first parameter*/
/*Output: number of the chars that added to the list*/
int handle_data_string_store(File_Config* file_config, char **words, int len, int curr_index) {
    char *curr_word, *curr_char;
    int curr_line_num, num_of_chars, i;
    Data_Node **data_head, **data_tail;
    

    data_head = get_file_data_head_address(file_config);
    data_tail = get_file_data_tail_address(file_config); 
    curr_line_num = get_curr_line_number(file_config);
    num_of_chars = 0;

    if(curr_index + 1 > len ) { /*if there is more then one param its not valid*/
        ERROR_MULTIPLE_ARGUMENTS(curr_line_num);
        update_validity_file_config(&file_config, FALSE);
    }

    curr_word = words[curr_index]; /*get the param to handle*/
    
    /*if the param is not valid - not added to the data list*/
    if(!is_valid_string_param(curr_word, curr_line_num)){
        update_validity_file_config(&file_config, FALSE);
        return num_of_chars;
    }
    
    /*insert each char of the word to the data list exsept the '"'*/
    curr_char = curr_word;
    for(i = 0; i < strlen(curr_word); i++, curr_char++) {
        /*skip the quotes in the sides of the word*/
        if((i == 0 || i == (strlen(curr_word) - 1)) && (*curr_char == '\"')) {
            continue;
        }
        add_data_node(data_head ,data_tail,*curr_char, STRING);
        num_of_chars++;
    }

    /*insert the end of the string char*/
    add_data_node(data_head ,data_tail,'\0', STRING);
    num_of_chars++;

    return num_of_chars;
}

/*Description: givien a word - check if its legal lable and insert to the lable list if needed*/
/*Input: file_config for the current file, word to handle, type of the lable*/
void handle_label(File_Config* file_config, char* word, Symbol_Type symbol_type) { 
    int counter_value;
    Lable_Node **label_head;

    label_head = get_file_label_head_address(file_config);
    

    /*validate the starting label*/
    if (!(is_valid_lable(*label_head, word, get_curr_line_number(file_config)))) {
        /*ASK: we need to continou?*/
        return;
    }
    /*add to symbol table - get the counter and remove colon*/
    counter_value = get_counter_by_type(file_config, symbol_type);
    remove_colon_at_end(word);

    insert_to_symbol_table(label_head, word, counter_value, symbol_type);
}


