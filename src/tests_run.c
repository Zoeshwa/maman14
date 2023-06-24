#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testers.h"

void run_tester() 
{
    run_return_tests();
    /*
    run_void_tests();
    */
}

void run_return_tests() {
     /*
        run_is_lable_testers();
        run_input_testers();
        run_file_get_tests();
        run_file_set_tests();
    */
   run_labels_tests();
}

void run_void_tests() {
    /*
        tests_get_next_word();
    */
    run_file_config_tests();
}


void run_is_lable_testers() 
{
    int i;
    i = 0;
    START_TEST("run_label_testers");
    tester_O_int_I_charP(is_lable, "hi:", 1, i++);
    tester_O_int_I_charP(is_lable, "hi", 0, i++);
    tester_O_int_I_charP(is_lable, "5i", 0, i++);
}

void run_input_testers() 
{
    
    START_TEST("input_testers");
    run_is_scope_ins_testers();
    run_is_extern_ins_testers();
    run_empty_line_testers();
    run_comment_line_testers();

}

void run_is_scope_ins_testers() 
{
    int i;
    i = 0;
    START_TEST("is_scope_ins");
    tester_O_int_I_charP(is_scope_ins, "example input", 0, i++);
    tester_O_int_I_charP(is_scope_ins, "extern input", 0, i++);
    tester_O_int_I_charP(is_scope_ins, ". extern input", 0,i++);
    tester_O_int_I_charP(is_scope_ins, ".data input", 0, i++);
    tester_O_int_I_charP(is_scope_ins, "entry input", 0, i++);


    tester_O_int_I_charP(is_scope_ins, ".entry input", 1, i++);
    tester_O_int_I_charP(is_scope_ins, "LOOP: .extern", 1, i++); /*FAIL*/
    tester_O_int_I_charP(is_scope_ins, ".extern", 1, i++);
    tester_O_int_I_charP(is_scope_ins, ".extern LOOP, JH", 1, i++);
    tester_O_int_I_charP(is_scope_ins, "LOOP:          .extern", 1, i++); /*FAIL*/
    tester_O_int_I_charP(is_scope_ins, "\t.extern          ", 1, i++);
    tester_O_int_I_charP(is_scope_ins, ".extern \t LOOP, JH", 1, i++);
    
}

void run_is_extern_ins_testers() 
{
    int i;
    i = 0;
    START_TEST("is_extern_ins");
    tester_O_int_I_charP(is_extern_ins, "example input", 0, i++);
    tester_O_int_I_charP(is_extern_ins, "extern input", 0, i++);
    tester_O_int_I_charP(is_extern_ins, ". extern input", 0, i++);
    tester_O_int_I_charP(is_extern_ins, ".data input", 0, i++);
    tester_O_int_I_charP(is_extern_ins, ".entry input", 0, i++);

    tester_O_int_I_charP(is_extern_ins, "LOOP: .extern", 1, i++); /*FAIL*/
    tester_O_int_I_charP(is_extern_ins, ".extern", 1, i++);
    tester_O_int_I_charP(is_extern_ins, ".extern LOOP, JH", 1, i++);
    tester_O_int_I_charP(is_extern_ins, "LOOP:          .extern", 1, i++); /*FAIL*/
    tester_O_int_I_charP(is_extern_ins, "\t.extern          ", 1, i++);
    tester_O_int_I_charP(is_extern_ins, ".extern \t LOOP, JH", 1, i++);
    
}

void run_empty_line_testers() 
{
    int i;
    i = 0;
    START_TEST("empty_line");
    tester_O_int_I_charP(empty_line, "example input", 0, i++);
    tester_O_int_I_charP(empty_line, "         example input", 0, i++);
    tester_O_int_I_charP(empty_line, "         7       $    ", 0, i++);
    tester_O_int_I_charP(empty_line, "         ", 1, i++);
    tester_O_int_I_charP(empty_line, "", 1, i++);
    tester_O_int_I_charP(empty_line, "\n", 1, i++);
    tester_O_int_I_charP(empty_line, "\t", 1, i++);
}

void run_comment_line_testers() 
{
    int i;
    i = 0;
    START_TEST("comment_line");
    tester_O_int_I_charP(comment_line, "example input", 0, i++);
    tester_O_int_I_charP(comment_line, "         example input", 0, i++);
    tester_O_int_I_charP(comment_line, "         7       $    ", 0, i++);
    tester_O_int_I_charP(comment_line, "         ", 0, i++);
    tester_O_int_I_charP(comment_line, "", 0, i++);
    tester_O_int_I_charP(comment_line, "\n", 0, i++);
    tester_O_int_I_charP(comment_line, "\t", 0, i++);
    tester_O_int_I_charP(comment_line, ".data input", 0, i++);
    tester_O_int_I_charP(comment_line, ".entry input", 0, i++);
    tester_O_int_I_charP(comment_line, "LOOP: .extern", 0, i++);
    tester_O_int_I_charP(comment_line, ".extern", 0, i++);

    tester_O_int_I_charP(comment_line, ";.extern", 1, i++);
    tester_O_int_I_charP(comment_line, ";", 1, i++);
    tester_O_int_I_charP(comment_line, "     ;   xtern", 1, i++);
}


void tests_get_next_word() {
    START_TEST("get_next_word");

    tester_get_next_word("entry input");
    tester_get_next_word("LOOP:          .extern");
    tester_get_next_word("LOOP: .extern");
}

/*file config*/
void run_file_config_tests() {
    File_Config* file_config;
    file_config = intialiez_file_config();
    START_TEST("print_file_config");

    print_file_config(file_config);
}

void run_file_get_tests() {
    File_Config* file_config;
    Symbol_Type symbol_type;
    file_config = intialiez_file_config();
    START_TEST("file_get_tests");
    tester_file_get_int_fileds(file_config, get_DC_counter, 0, 1);
    tester_file_get_int_fileds(file_config, get_IC_counter, 100, 2);
    symbol_type = DATA;
    tester_file_get_counter_by_type(file_config, symbol_type, 0, 3);
    symbol_type = CODE;
    tester_file_get_counter_by_type(file_config, symbol_type, 100, 4);
}

void run_file_set_tests() {
    File_Config* file_config;
    file_config = intialiez_file_config();
    START_TEST("file_set_tests");
    tester_file_set_int_fileds(file_config, set_file_config_DC,get_DC_counter, 1, 1);
    tester_file_set_int_fileds(file_config, set_file_config_IC, get_IC_counter, 101, 2);
}

/*labels*/

void run_labels_tests() {
    run_labels_new_tests();
    run_labels_set_tests();
    run_labels_get_tests();
    /*
    run_tests_is_symbol_already_exist();
    run_tests_is_valid_lable();
    */
}

void run_labels_set_tests() {
    Lable_Node* label_node;
    Symbol_Type symbol_type;
    int test_number;
    START_TEST("labels_set_tests");

    symbol_type = DATA;
    test_number = 0;

    label_node = new_label_node("hi", 0, symbol_type);

    tester_set_label_name(label_node, "hi", test_number);

    tester_set_label_types(label_node, symbol_type, test_number++);
    symbol_type = CODE;
    tester_set_label_types(label_node, symbol_type, test_number++);
    symbol_type = EXTERNALT;
    tester_set_label_types(label_node, symbol_type, test_number++);
    free_label_node(label_node);
}

void run_labels_new_tests() {
    Symbol_Type symbol_type;
    int test_number;

    START_TEST("labels_new_tests");

    test_number = 0;

    symbol_type = DATA;
    tester_new_label_node("hi", 15, symbol_type, test_number);

    symbol_type = CODE;
    tester_new_label_node("hicode", 7, symbol_type, test_number++);

    symbol_type = EXTERNALT;
    tester_new_label_node("hiEXTERNALT", 5, symbol_type, test_number++);
}

void run_labels_get_tests() {
    Lable_Node* label_node;
    Symbol_Type symbol_type;
    int test_number;
    START_TEST("labels_get_tests");

    symbol_type = DATA;
    test_number = 0;
    label_node = new_label_node("hi", 0, symbol_type);

    tester_label_get_label_name(label_node, "hi", 1, test_number++);
    tester_label_get_label_name(label_node, "dddd", 0, test_number++);

    tester_label_get_int_fileds(label_node, get_label_counter_value, 0, test_number++);
    /* TODO:
        tester_label_get_int_fileds(label_node, get_label_is_entry, ,test_number)
    */
}


void run_tests_is_symbol_already_exist() {
    /*TODO:*/

}

void run_tests_is_valid_lable() {
    /*
        tester_is_valid_lable("hi:", 1);
        tester_is_valid_lable("hi", 0);
        tester_is_valid_lable("5i", 0);
        tester_is_valid_lable("i555ADMSasjd555:", 1);
        tester_is_valid_lable("A555ADMSasjd555:", 1);
        tester_is_valid_lable("i555ADMSasjd555i555ADMSasjd555i555ADMSasjd555:", 0);
        tester_is_valid_lable("#5i:", 0);
        tester_is_valid_lable("a5$i:", 0);
    */
    
}
