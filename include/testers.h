

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
    #include "words_functions.h"
#endif

#ifndef _DATA_HEADER_
#define _TESTERS_DATA_HEADER_
    #include "data_struct.h"
#endif

#ifndef _FILES_FUNCTIONS_HEADER_
#define _TESTERS_FILES_HEADER_
    #include "file_functions.h"
#endif

#ifndef _TESTERS_HEADER_
#define _TESTERS_HEADER_


    #define NOT_GOOD printf("----------BAD------------\n")
    #define GOOD printf("----------GOOD------------\n")
    #define START_TEST(fun_name) printf("\nSTART TEST: %s\n", fun_name)

    void tester_O_int_I_charP(int (*function)(char*), char* input, int expected_result, int test_number);   
    void tester_get_next_word(char * str);
    void tester_file_get_int_fileds(File_Config* file_config, int (*function)(File_Config*), int expected_result, int test_number);
    void tester_file_get_counter_by_type(File_Config* file_config, Symbol_Type symbol_type, int expected_result, int test_number);


    void print_file_config(File_Config* file_config);
    void print_Symbol_table(Symbol_Table* symbol_table);
    void print_DATA_Table(DATA_Table* data_table);
    void print_Ins_Node(Ins_Node* ins);
    void print_Lable_Node(Lable_Node* label_node);
    void print_Data_Node(Data_Node* data_node);

    /*tests - run tests*/
    void run_tester();
    void run_void_tests();
    void tests_get_next_word();
    void run_return_tests();
    void run_file_config_tests();
    void run_input_testers();
    void run_is_scope_ins_testers();
    void run_is_extern_ins_testers(); 
    void run_empty_line_testers();
    void run_comment_line_testers(); 
    void run_is_lable_testers();

    void run_file_config_tests();
    void run_file_get_tests();


#endif

