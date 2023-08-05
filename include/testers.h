

#ifndef _LABELS_HEADER_
#define _TESTERS_LABELS_HEADER_
    #include "labels.h"
#endif

#ifndef _WORDS_HEADER_
#define _TESTERS_WORDS_HEADER_
    #include "words_functions.h"
#endif

#ifndef _LINES_HEADER_
#define _TESTERS_LINES_HEADER_
    #include "line_functions.h"
#endif

#ifndef _DATA_HEADER_
#define _TESTERS_DATA_HEADER_
    #include "data_struct.h"
#endif

#ifndef _FILES_FUNCTIONS_HEADER_
#define _TESTERS_FILES_HEADER_
    #include "file_functions.h"
#endif

#ifndef _FIRST_PASS_HEADER_
    #include "first_pass.h"
#endif

#ifndef _TESTERS_HEADER_
#define _TESTERS_HEADER_


    #define NOT_GOOD printf("----------BAD------------\n")
    #define GOOD printf("----------GOOD------------\n")
    #define START_TEST(fun_name) printf("\nSTART TEST: %s\n", fun_name)
    #define END_TEST(fun_name) printf("END TEST: %s\n", fun_name)

    void tester_O_int_I_charP_int(int (*function)(char*, int), char* input, int expected_result, int test_number);
    void tester_O_int_I_charP(int (*function)(char*), char* input, int expected_result, int test_number);   
    void tester_get_next_word(char * str);
    void tester_file_get_int_fileds(File_Config* file_config, int (*function)(File_Config*), int expected_result, int test_number);
    void tester_file_get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type, int expected_result, int test_number);
    void tester_file_set_int_fileds(File_Config* file_config, void (*set_func)(File_Config*, int),int (*get_func)(File_Config*), int expected_result, int test_number);
    
    void test_remove_colon_at_end(char* word, int test_number, const char* expected_result);
    void tester_is_valid_lable(Lable_Node* lable_head, char* word,  int expected_result, int test_number);
    void tester_new_label_node(char* word, int counter_value, Symbol_Type symbol_type, int test_number);
    void tester_set_label_name(Lable_Node* new_lable, char * word, int test_number);
    void tester_set_label_types(Lable_Node* new_lable, Symbol_Type symbol_type, int test_number);
    void tester_label_get_int_fileds(Lable_Node* label, int (*function)(Lable_Node*), int expected_result, int test_number);
    void tester_label_get_label_name(Lable_Node* label, char* word, int expected_result, int test_number);


    /*print functions*/
    /*
    print functions
    void print_Ins_Node(Ins_Node* ins);
    void print_Lable_Node(Lable_Node* label_node);
    */
    void print_Data_Node(Data_Node* data_node);


    /*tests - run tests*/
    void run_tester();
    void run_words_functions_testers();
    void run_is_lable_testers();
    void run_input_testers();
    void run_is_external_or_entry_ins_testers();
    void run_is_external_or_entry_ins_testers();
    void run_is_extern_ins_testers(); 
    void run_empty_line_testers();
    void run_comment_line_testers();
    void run_remove_colon_at_end();

    void run_is_saved_word();

    void tests_get_next_word();

    void run_file_config_tests();
    void run_file_get_tests();
    void run_file_set_tests();

    void run_labels_tests();
    void run_labels_set_tests();
    void run_labels_new_tests();
    void run_labels_get_tests();
    void run_tests_is_symbol_already_exist();
    void run_tests_is_valid_lable();

    void run_first_pass_tests();
    void run_tests_handle_label();


    /*utils testers*/
    int is_Ins_List_equals(Ins_Node* ins_head_a, Ins_Node* ins_head_b);
    int is_Lable_Node_equals(Lable_Node* curr_node_a, Lable_Node* curr_node_b);
    int is_Ins_Node_equals(Ins_Node* curr_node_a, Ins_Node* curr_node_b);
    int is_data_Node_equals(Data_Node* curr_node_a, Data_Node* curr_node_b);
    int is_Ins_Node_err_equals(Ins_Node* curr_node_a, Ins_Node* curr_node_b);

    void tester_is_symbol_already_exist(Lable_Node* lable_head, char * symbol_name, int expected_result, int test_number);

    void print_Ins_Node(Ins_Node* ins);
    void print_file_config(File_Config* file_config);
    void tester_is_symbol_already_exist(Lable_Node* lable_head, char * symbol_name, int expected_result, int test_number);

    void print_Ins_Node(Ins_Node* ins);
    void print_file_config(File_Config* file_config);

    void print_Lable_Node(Lable_Node* label_node);
    void print_Ins_Node(Ins_Node* ins);

    int compare_Lable_Node(Lable_Node* node1, Lable_Node* node2);

    void tester_is_saved_word(char* input, int expected_result, int test_number);
    void tester_handle_label(File_Config* file_config, char* word, Symbol_Type symbol_type, Lable_Node* expted_lable_list, int test_number);
    void tester_is_legal_params(char* input, int expected_result, int test_number);
    void run_is_legal_params();
    void run_get_words();
    void run_tests_handle_extern();
    void run_is_valid_quotes();
    void run_handle_int_store();
    void run_handle_string_store();
    void run_handle_data_ins();
    char** get_lines_valid(int* len);
    char** get_lines_invalid(int* len);
    void tests_get_number();

    void tester_bin_word(char* input, char* expected_input, int test_number);
#endif

