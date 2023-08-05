#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testers.h"

#define PASS_PRINT(expected_result) printf("V - PASS: Expected result (%d) matches the actual result.\n", expected_result)
#define FAIL_PRINT(test_number, expected_result, result) printf("X - FAIL: test_num (%d), Expected (%d) - Actual result (%d)\n",test_number, expected_result, result)



void tester_O_int_I_char(int (*function)(char), char input, int expected_result, int test_number) {
    int result;
    result = function(input);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}

void tester_O_int_I_charP_int(int (*function)(char*, int), char* input, int expected_result, int test_number) {
    int result;
    result = function(input, test_number);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}

void tester_O_int_I_charP(int (*function)(char*), char* input, int expected_result, int test_number) {
    int result;
    result = function(input);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}

void tester_is_saved_word(char* input, int expected_result, int test_number) {
    int result;
    result = is_saved_word(input);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}

/*void tester_bin_word(Ins_Node** input, char* expected_input, int test_number) {
    char* result, test_result;
    make_bin_ins_word(input);
    test_result = strcmp((*input)->bin_rep, expected_input);
    if (test_result == 0) {
        PASS_PRINT(test_result);
    } else {
        FAIL_PRINT(test_number, test_result, result);
    }
}*/

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

void test_remove_colon_at_end(char* word, int test_number, const char* expected_result) {
    char *copy_word;
    copy_word = (char*)malloc(strlen(word) + 1);
    strcpy(copy_word, word); 

    remove_colon_at_end(word);
    if (strcmp(word, expected_result) == 0) {
        printf("V - PASS: Expected result (%s) matches the actual result.\n", expected_result);
    } else {
        printf("X - FAIL: test_num (%d), Expected (%s) - Actual result (%s)\n",test_number, expected_result, word);
    }
}

/*print func*/

void print_file_config(File_Config* file_config) {
    if(file_config == NULL) {
        printf("file_config is NULL\n");
        return;
    }
    printf("FILE_CONFIG:\n");
    printf("\t DC: %d, IC: %d, curr_line_num:%d, is_valid:%d \n", get_DC_counter(file_config), get_IC_counter(file_config), get_curr_line_number(file_config), get_is_valid_file(file_config));
    printf("\n");
    print_Ins_Node(get_file_ins_head(file_config));
    printf("\n");
    print_Lable_Node(get_label_node_head(file_config));
    printf("\n");
    print_Data_Node(get_data_node_head(file_config));
    printf("\n");

}

void print_Lable_Node(Lable_Node* label_node) {
    if(label_node == NULL) {
        printf("Lable_Node=NULL\n");
        return;
    }
    printf("Lable_Node: ");
    printf("\tname: %s, ",get_label_name(label_node));
    printf("\tcounter_value: %d,",get_label_counter_value(label_node));
    printf("\tsymbol_type: %d,",get_label_symbol_type(label_node));
    printf("\tis_entry: %d,",get_label_is_entry(label_node));
    if(get_label_next(label_node) != NULL) {
        printf("\tnext: \n");
        print_Lable_Node(get_label_next(label_node));
    }else {
        printf("\tnext: NULL\n");
    }
} 

void print_Data_Node(Data_Node* data_node) {
    if(data_node == NULL) {
        printf("Data_Node is NULL\n");
        return;
    }

    printf("DATA NODE:");
    if(get_data_node_type(data_node) == STRING) {
        printf("\tvalue: %c, ", get_data_node_value(data_node));
        printf("\ttype: STRING, ");
    } else {
        printf("\tvalue: %d, ", get_data_node_value(data_node));
        printf("\ttype: DATA, ");
    }
    printf("\tbin: %s,\tDC_counter: %d \n", get_bin_rep_data(data_node), get_data_node_DC_counter(data_node));
    print_Data_Node(get_data_node_next(data_node));
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
    free_label_node(&node_result);
}

void tester_set_label_name(Lable_Node* new_lable, char * word, int test_number) {
    int result;
    set_label_name(new_lable, word);
    result = strcmp(get_label_name(new_lable), word);
    if (result == 0) {
        PASS_PRINT(0);
    } else {
        FAIL_PRINT(test_number, 0, result);
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


void tester_is_symbol_already_exist(Lable_Node* lable_head, char * symbol_name, int expected_result, int test_number) {
    Lable_Node* search_result;
    int result;
    search_result = find_lable(lable_head, symbol_name);

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

void tester_is_valid_lable(Lable_Node* lable_head, char* word,  int expected_result, int test_number){ 
    int result;
    char *tmp;
    tmp = (char*)malloc((strlen(word)+1)*sizeof(char));
    strcpy(tmp, word);
    
    result = is_valid_lable(lable_head, tmp, test_number);

    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number,expected_result, result);
    }

    free(tmp);
}

/*first pass*/

void tester_handle_label(File_Config* file_config, char* word, Symbol_Type symbol_type, Lable_Node* expted_lable_list, int test_number) {
    int result;
    result = 1;
    
    handle_label(file_config, word, symbol_type);

    if(compare_Lable_Node(get_label_node_head(file_config), expted_lable_list) == 0) {
        result = 1;
    }

    if (result == 1) {
        PASS_PRINT(1);
    } else {
        FAIL_PRINT(test_number, 1, result);
    }

}


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

/* Function to compare two Lable_Node */
int compare_Lable_Node(Lable_Node* node1, Lable_Node* node2) {
    if (node1 == NULL && node2 == NULL) {
        return TRUE; 
    } else if (node1 == NULL || node2 == NULL) {
        return FALSE; 
    }

    if (strcmp(get_label_name(node1), get_label_name(node2)) == 0
        /* Add comparisons for other fields as needed */
        && compare_Lable_Node(get_label_next(node1), get_label_next(node2))) {
        return 1; 
    }

    return 0; 
}

int is_Ins_List_equals(Ins_Node* ins_head_a, Ins_Node* ins_head_b) {
    Ins_Node* curr_node_a, *curr_node_b;

    curr_node_a = ins_head_a;
    curr_node_b = ins_head_b;

    while (curr_node_a != NULL && curr_node_b != NULL)
    {
        if(is_Ins_Node_equals(curr_node_a, curr_node_b) == 0) {
            return 0;
        }
        curr_node_a = get_ins_next(curr_node_a);
        curr_node_b = get_ins_next(curr_node_b);
    }
    if(curr_node_a == NULL && curr_node_b == NULL) {
        return 1;
    } 

    return 0;
}

int is_Ins_Node_equals(Ins_Node* curr_node_a, Ins_Node* curr_node_b) {


    /*TODO: more filds*/
    return 1;
}


int is_data_Node_equals(Data_Node* curr_node_a, Data_Node* curr_node_b) {
    


    if(get_data_node_DC_counter(curr_node_a) != get_data_node_DC_counter(curr_node_b)) {
        return 0;
    }

    return 1;
}


void tester_is_legal_params(char* input, int expected_result, int test_number) {
    int result;
    result = is_legal_params(input, test_number);
    if (result == expected_result) {
        PASS_PRINT(expected_result);
    } else {
        FAIL_PRINT(test_number, expected_result, result);
    }
}



/*words testers*/



