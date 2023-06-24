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



void print_file_config(File_Config* file_config) {
    if(file_config == NULL) {
        printf("file_config is NULL");
        return;
    }
    printf("This is file config print\n");
    printf("Counters - DC: %d, IC: %d\n", get_DC_counter(file_config), get_IC_counter(file_config));
    print_Symbol_table(get_file_symbol_table(file_config));
    print_Ins_Node(get_file_ins_head(file_config));
    print_DATA_Table(get_file_data_table(file_config));
}


void print_Symbol_table(Symbol_Table* symbol_table) {
    if(symbol_table == NULL) {
        printf("symbol_table is NULL");
        return;
    }
    printf("This is Symbol_Table print:\n");
    printf("print head:\n");
    print_Lable_Node(symbol_table->head);
    printf("print tail:\n");
    print_Lable_Node(symbol_table->tail);
}

void print_DATA_Table(DATA_Table* data_table) {
    if(data_table == NULL) {
        printf("data_table is NULL");
        return;
    }
    printf("This is DATA_Table print:\n");
    printf("print head:\n");
    print_Data_Node(data_table->head);
    printf("print tail:\n");
    print_Data_Node(data_table->tail);
}

void print_Ins_Node(Ins_Node* ins) {
        if(ins == NULL) {
        printf("ins is NULL");
        return;
    }
    printf("This is Ins_Node print:\n");
    printf("line_number: %d, IC_count: %d\n",ins->line_number, ins->IC_count);
    /*TODO*/
} 

void print_Lable_Node(Lable_Node* label_node) {
    if(label_node == NULL) {
        printf("Lable_Node is NULL");
        return;
    }
    printf("This is Lable_Node print:\n");
    printf("name: %s, ",label_node->name);
    printf("counter_type: %d, \n",label_node->counter_type);
    printf("counter_value: %d, \n",label_node->counter_value);
    printf("symbol_type: %d, ",label_node->symbol_type);
    printf("is_entry: %d\n",label_node->is_entry);

    printf("next: %s\n", label_node->next->name);
} 

void print_Data_Node(Data_Node* data_node) {
    if(data_node == NULL) {
        printf("Lable_Node is NULL");
        return;
    }
    printf("This is Lable_Node print:\n");
    printf("value: %d, ",data_node->value);
    printf("is_char: %d, \n",data_node->is_char);
    printf("DC_counter: %d, \n",data_node->DC_counter);
    printf("next: %s\n", data_node->next->value);
} 

/*
int tester_is_valid_lable(char * word, int expacted) 
{
    int result;

    printf("tester_is_valid_lable(%s, %d): ", word, expacted);
    result = is_valid_lable(word);
    if(result == expacted) {
        GOOD;
        return 1;
    } else {
        NOT_GOOD;
        return 0;
    }
}
*/


/*

    
*/

