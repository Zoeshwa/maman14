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

/*print func*/

void print_file_config(File_Config* file_config) {
    if(file_config == NULL) {
        printf("file_config is NULL\n");
        return;
    }
    printf("This is file config print: {\n");
    printf("\tCounters - DC: %d, IC: %d\n\t", get_DC_counter(file_config), get_IC_counter(file_config));
    print_Symbol_table(get_file_symbol_table(file_config));
    printf("\t");
    print_Ins_Node(get_file_ins_head(file_config));
    printf("\t");
    print_DATA_Table(get_file_data_table(file_config));
    printf("}\n");

}





void print_Ins_Node(Ins_Node* ins) {
    if(ins == NULL) {
        printf("ins is NULL\n");
        return;
    }
    printf("This is Ins_Node print: {\n");
    printf("\tline_number: %d, IC_count: %d\n\t",ins->line_number, ins->IC_count);
    printf("}\n");

} 

void print_Lable_Node(Lable_Node* label_node) {
    if(label_node == NULL) {
        printf("Lable_Node=NULL\n");
        return;
    }
    printf("Lable_Node: ");
    printf("\tname: %s, ",label_node->name);
    printf("\tcounter_type: %d,",label_node->counter_type);
    printf("\tcounter_value: %d,",label_node->counter_value);
    printf("\tsymbol_type: %d,",label_node->symbol_type);
    printf("\tis_entry: %d,",label_node->is_entry);
    if(label_node->next  != NULL) {
        printf("\tnext: %s\n", label_node->next->name);
    }else {
        printf("\tnext: NULL\n");
    }
} 

void print_Data_Node(Data_Node* data_node) {
    if(data_node == NULL) {
        printf("Data_Node is NULL\n");
        return;
    }
    printf("\tThis is Data_Node print:{\n");
    printf("\tvalue: %d, ",data_node->value);
    printf("\tis_char: %d, \n",data_node->is_char);
    printf("\tDC_counter: %d, \n",data_node->DC_counter);
    printf("\tnext: %s\n\t", data_node->next->value);
    printf("}\n");

} 

/*files testers*/
void tester_file_get_int_fileds(File_Config* file_config, int (*function)(File_Config*), int expected_result, int test_number){
    int result;
    result = function(file_config);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}

void tester_file_get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type, int expected_result, int test_number){
    int result;
    result = get_counter_by_type(file_config, symbol_type);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}

void tester_file_set_int_fileds(File_Config* file_config, void (*set_func)(File_Config*, int),int (*get_func)(File_Config*), int expected_result, int test_number){
    int result;
    set_func(file_config, expected_result);
    result = get_func(file_config);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}

/*TODO: rest of get and set files*/

/*Labels testers*/
void tester_new_label_node(char* word, int counter_value, Symbol_Type symbol_type, int test_number) {
    Lable_Node* node_result;
    int result;
    node_result = new_label_node(word, counter_value, symbol_type);
    result = 0;
    if(get_label_counter_value(node_result) == counter_value) {
        result = 1;
    } else {
        result = 0;
    }
    if(get_label_symbol_type(node_result) == symbol_type) {
        result = 1;
    } else {
        result = 0;
    }
    if(strcmp(get_label_name(node_result),word) == 0) {
        result = 1;
    } else {
        result = 0;
    }

    if (result == 1) {
        PASS_PRINT(1);
    } else {
        FAIL_PRINT(test_number,1, result);
    }
    free_label_node(node_result);
}

void tester_set_label_name(Lable_Node* new_lable, char * word, int test_number) {
    int result;
    set_label_name(new_lable, word);
    result = strcmp(new_lable->name, word);
    if (result == 0) {
        PASS_PRINT(0);
    } else {
        FAIL_PRINT(test_number, 0, result);
    }
}

void tester_set_label_types(Lable_Node* new_lable, Symbol_Type symbol_type, int test_number) {
    int result;
    Counter_Type counter_type;
    result = 0;
    set_label_types(new_lable, symbol_type);

    if(symbol_type == DATA) {
        counter_type = DC;
    } else {
        counter_type = IC;
    }

    if(symbol_type == new_lable->symbol_type && counter_type == new_lable->counter_type) {
        result = 1;
    } 

    if (result == 1) {
        PASS_PRINT(1);
    } else {
        FAIL_PRINT(test_number, 1, result);
    }
}

void tester_label_get_int_fileds(Lable_Node* label, int (*function)(Lable_Node*), int expected_result, int test_number){
    int result;
    result = function(label);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
} 

void tester_label_get_label_name(Lable_Node* label, char* word, int expected_result, int test_number){
    int result, cmp_result;
    cmp_result = strcmp(get_label_name(label), word);
    if(cmp_result == 0) {
        result = 1;
    } else {
        result = 0;
    }
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}
/*
void tester_is_symbol_already_exist(Symbol_Table* table, char * symbol_name, int expected_result, int test_number) {
    Lable_Node* search_result;
    int result;
    search_result = is_symbol_already_exist(table, symbol_name);

    if(search_result == NULL) {
        result = 0;
    } else {
        result = 1;
    }
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number,expected_result, result);
    }
}
*/
/*

void tester_is_valid_lable(Symbol_Table* table, char* word,  int expected_result, int test_number){ 
    int result;
    result = is_valid_lable(table, word);

    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number,expected_result, result);
    }
}
*/


/*TODO:
    void insert_to_symbol_table(Symbol_Table* table, char* word, int counter_value, Symbol_Type symbol_type) {
    void set_label_next(Lable_Node* new_lable, Symbol_Table* table) {
    Lable_Node* get_label_next(Lable_Node* new_lable) {
Symbol_Type get_label_symbol_type(Lable_Node* new_lable) {
Counter_Type get_label_counter_type(Lable_Node* new_lable) {

*/

/*first pass*/
/*
void tester_handle_label(File_Config* file_config, struct Ins_Node* node, char* word, Symbol_Type symbol_type, Ins_Node* expted_node, Symbol_Table* expted_symbol_table, int test_number) {
    int result;
    result = 1;
    handle_label(file_config, node, word, symbol_type);


    if(is_Ins_Node_err_equals(node, expted_node) == 0) {
        result = 1;
    }
    
    if(is_symbol_table_equals(file_config->symbol_table, expted_symbol_table) == 0) {
        result = 1;
    }

    if (result == 1) {
        PASS_PRINT(1);
    } else {
        FAIL_PRINT(test_number, 1, result);
        print_Symbol_table(file_config->symbol_table);
        print_Ins_Node(node);
    }

}
*/


/*utils */

/*
int is_file_config_equals(File_Config* file_config_a, File_Config* file_config_b) {

    if(get_DC_counter(file_config_a) != get_DC_counter(file_config_b)) {
        return 0;
    }
    
    if(get_IC_counter(file_config_a) != get_IC_counter(file_config_b)) {
        return 0;
    }
    if(is_symbol_table_equals(file_config_a->symbol_table, file_config_b->symbol_table) == 0) {
        return 0;
    }
    if(is_Ins_Node_equals(file_config_a->ins_head, file_config_b->ins_head) == 0) {
        return 0;
    }
    if(is_DATA_Table_equals(file_config_a->data_table, file_config_b->data_table) == 0) {
        return 0;
    }
    return 1;
}
*/

/*
int is_symbol_table_equals(Symbol_Table* symbol_table_a, Symbol_Table* symbol_table_b) {
    Lable_Node* curr_node_a, *curr_node_b;

    curr_node_a = symbol_table_a->head;
    curr_node_b = symbol_table_b->head;

    while (curr_node_a != NULL && curr_node_b != NULL)
    {
        if(is_Lable_Node_equals(curr_node_a, curr_node_b) == 0) {
            return 0;
        }
        curr_node_a = curr_node_a->next;
        curr_node_b = curr_node_b->next;
    }
    if(curr_node_a == NULL && curr_node_b == NULL) {
        return 1;
    } 

    return 0;
}
*/

int is_Ins_List_equals(Ins_Node* ins_head_a, Ins_Node* ins_head_b) {
    Ins_Node* curr_node_a, *curr_node_b;

    curr_node_a = ins_head_a;
    curr_node_b = ins_head_b;

    while (curr_node_a != NULL && curr_node_b != NULL)
    {
        if(is_Ins_Node_equals(curr_node_a, curr_node_b) == 0) {
            return 0;
        }
        curr_node_a = curr_node_a->next;
        curr_node_b = curr_node_b->next;
    }
    if(curr_node_a == NULL && curr_node_b == NULL) {
        return 1;
    } 

    return 0;
}


int is_Lable_Node_equals(Lable_Node* curr_node_a, Lable_Node* curr_node_b) {
    
    if(get_label_counter_value(curr_node_a) != get_label_counter_value(curr_node_b)) {
        return 0;
    }
    
    if(strcmp(get_label_name(curr_node_a),get_label_name(curr_node_b)) != 0) {
        return 0;
    }
    if(get_label_counter_type(curr_node_a) != get_label_counter_type(curr_node_b)) {
        return 0;
    }

    if(get_label_symbol_type(curr_node_a) != get_label_symbol_type(curr_node_b)) {
        return 0;
    }
    /*TODO: more filds*/
    return 1;
}

int is_Ins_Node_equals(Ins_Node* curr_node_a, Ins_Node* curr_node_b) {
            
    if(get_Ins_Node_IC_count(curr_node_a) != get_Ins_Node_IC_count(curr_node_b)) {
        return 0;
    }
    if(get_Ins_Node_line_number(curr_node_a) != get_Ins_Node_line_number(curr_node_b)) {
        return 0;
    }

    if(get_Ins_Node_encoding_type(curr_node_a) != get_Ins_Node_encoding_type(curr_node_b)) {
        return 0;
    }
    
    if(get_Ins_Node_is_error(curr_node_a) != get_Ins_Node_is_error(curr_node_b)) {
        return 0;
    }
    
    if(get_Ins_Node_num_of_lines(curr_node_a) != get_Ins_Node_num_of_lines(curr_node_b)) {
        return 0;
    }
    
    if(strcmp(get_Ins_Node_err_msg(curr_node_a),get_Ins_Node_err_msg(curr_node_b)) != 0) {
        return 0;
    }

    /*TODO: more filds*/
    return 1;
}

int is_Ins_Node_err_equals(Ins_Node* curr_node_a, Ins_Node* curr_node_b) {
               
    if(get_Ins_Node_is_error(curr_node_a) != get_Ins_Node_is_error(curr_node_b)) {
        return 0;
    }

    
    if(strcmp(get_Ins_Node_err_msg(curr_node_a),get_Ins_Node_err_msg(curr_node_b)) != 0) {
        return 0;
    }

    /*TODO: more filds*/
    return 1;
}

int is_data_Node_equals(Data_Node* curr_node_a, Data_Node* curr_node_b) {
    if(get_data_node_value(curr_node_a) != get_data_node_value(curr_node_b)) {
        return 0;
    }
    if(get_data_node_is_char(curr_node_a) != get_data_node_is_char(curr_node_b)) {
        return 0;
    }

    if(get_data_node_DC_counter(curr_node_a) != get_data_node_DC_counter(curr_node_b)) {
        return 0;
    }

    return 1;
}



