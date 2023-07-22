#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testers.h"

void run_tester() 
{
    run_labels_tests();
    /*
    run_return_tests();
    run_file_config_tests();
    run_first_pass_tests(); 
    tests_get_next_word();
    */
    run_file_config_print();
  
}

void run_return_tests() {
    run_input_testers();
}

/*strings*/

void run_is_lable_testers() 
{
    int i;
    i = 0;
    START_TEST("run_label_testers");
    tester_O_int_I_charP(is_lable, "hi:", 1, i++);
    tester_O_int_I_charP(is_lable, "hi", 0, i++);
    tester_O_int_I_charP(is_lable, "5i", 0, i++);
    END_TEST("run_label_testers");
}

void run_input_testers() 
{
    
    START_TEST("input_testers");
    run_is_external_or_entry_ins_testers();
    run_is_extern_ins_testers();
    run_empty_line_testers();
    run_comment_line_testers();
    END_TEST("input_testers");
}

void run_is_external_or_entry_ins_testers() 
{
    int i;
    i = 0;
    START_TEST("is_external_or_entry_ins");
    tester_O_int_I_charP(is_external_or_entry_ins, "example input", 0, i++);
    tester_O_int_I_charP(is_external_or_entry_ins, "extern input", 0, i++);
    tester_O_int_I_charP(is_external_or_entry_ins, ". extern input", 0,i++);
    tester_O_int_I_charP(is_external_or_entry_ins, ".data input", 0, i++);
    tester_O_int_I_charP(is_external_or_entry_ins, "entry input", 0, i++);


    tester_O_int_I_charP(is_external_or_entry_ins, ".entry input", 1, i++);
    tester_O_int_I_charP(is_external_or_entry_ins, "LOOP: .extern", 1, i++); /*FAIL*/
    tester_O_int_I_charP(is_external_or_entry_ins, ".extern", 1, i++);
    tester_O_int_I_charP(is_external_or_entry_ins, ".extern LOOP, JH", 1, i++);
    tester_O_int_I_charP(is_external_or_entry_ins, "LOOP:          .extern", 1, i++); /*FAIL*/
    tester_O_int_I_charP(is_external_or_entry_ins, "\t.extern          ", 1, i++);
    tester_O_int_I_charP(is_external_or_entry_ins, ".extern \t LOOP, JH", 1, i++);
    END_TEST("");
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
    END_TEST("");

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
    END_TEST(" ");

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
    END_TEST(" ");

}

void tests_get_next_word() {
    START_TEST("get_next_word");

    tester_get_next_word("entry input");
    tester_get_next_word("LOOP:          .extern");
    tester_get_next_word("LOOP: .extern");
    END_TEST(" ");
}

/*file config*/
void run_file_config_print() {
    File_Config* file_config;
    file_config = intialiez_file_config();
    START_TEST("print_file_config");

    print_file_config(file_config);
    END_TEST("print_file_config");
}

void run_file_config_tests() {
    run_file_get_tests();
    run_file_set_tests();
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
    free_file_config(file_config);
    END_TEST(" ");
}

void run_file_set_tests() {
    File_Config* file_config;
    file_config = intialiez_file_config();
    START_TEST("file_set_tests");
    tester_file_set_int_fileds(file_config, set_file_config_DC,get_DC_counter, 1, 1);
    tester_file_set_int_fileds(file_config, set_file_config_IC, get_IC_counter, 101, 2);
    free_file_config(file_config);
    END_TEST(" ");
}

/*labels*/
void run_labels_tests() {
    run_labels_new_tests();
    run_labels_set_tests();
    run_labels_get_tests();
    run_is_lable_testers();
    run_tests_is_valid_lable();
    /*
    run_tests_is_symbol_already_exist();

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
    free_label_node(&label_node);
    END_TEST("labels_set_tests");
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
    END_TEST("labels_new_tests");
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
    free_label_node(&label_node);
    END_TEST("labels_get_tests");
}

/*
void run_tests_is_symbol_already_exist() {
    Symbol_Table* table;
    int test_number;
    Symbol_Type symbol_type;
    
    START_TEST("run_tests_is_symbol_already_exist");

    test_number = 0;
    table = intialiez_symbol_table();
    
    tester_is_symbol_already_exist(table, "hi:", 0, test_number++);
    tester_is_symbol_already_exist(table, "hi", 0, test_number++);
    tester_is_symbol_already_exist(table, "5i", 0, test_number++);
    tester_is_symbol_already_exist(table, "i555ADMSasjd555:", 0, test_number++);
    tester_is_symbol_already_exist(table, "A555ADMSasjd555:", 0, test_number++);
    tester_is_symbol_already_exist(table, "i555ADMSasjd555i555ADMSasjd555i555ADMSasjd555:", 0, test_number++);
    tester_is_symbol_already_exist(table, "#5i:", 0, test_number++);
    tester_is_symbol_already_exist(table, "a5$i:", 0, test_number++);


    symbol_type = DATA;
    insert_to_symbol_table(table, "hi:", test_number, symbol_type);

    tester_is_symbol_already_exist(table, "hi:", 1, test_number++);
    tester_is_symbol_already_exist(table, "hi", 0, test_number++); 
    tester_is_symbol_already_exist(table, "i555ADMSasjd555:", 0, test_number++);

    insert_to_symbol_table(table, "hi2:", test_number, symbol_type);

    tester_is_symbol_already_exist(table, "hi:", 1, test_number++); 
    tester_is_symbol_already_exist(table, "hi2:", 1, test_number++);
    tester_is_symbol_already_exist(table, "hi", 0, test_number++);
    tester_is_symbol_already_exist(table, "i555ADMSasjd555:", 0, test_number++);

    symbol_type = CODE;
    insert_to_symbol_table(table, "hi3:", test_number, symbol_type);
    insert_to_symbol_table(table, "hi4:", test_number, symbol_type);
    symbol_type = EXTERNALT;
    insert_to_symbol_table(table, "hi5:", test_number, symbol_type);
    insert_to_symbol_table(table, "hi6:", test_number, symbol_type);

    tester_is_symbol_already_exist(table, "hi:", 1, test_number++); 
    tester_is_symbol_already_exist(table, "hi2:", 1, test_number++);
    tester_is_symbol_already_exist(table, "hi3:", 1, test_number++); 
    tester_is_symbol_already_exist(table, "hi4:", 1, test_number++);
    tester_is_symbol_already_exist(table, "hi5:", 1, test_number++); 
    tester_is_symbol_already_exist(table, "hi6:", 1, test_number++);
    
    tester_is_symbol_already_exist(table, "hi", 0, test_number++);
    tester_is_symbol_already_exist(table, "i555ADMSasjd555:", 0, test_number++);

    free_symbol_table(table);
    END_TEST(" ");
}
*/

void run_tests_is_valid_lable() {
    Lable_Node* head;
    int test_number;
    Symbol_Type symbol_type;
    
    START_TEST("run_tests_is_valid_lable");

    test_number = 0;
    head = NULL;
    /*when list empty and only word check*/
    tester_is_valid_lable(head, "hi:", 1, test_number++);
    tester_is_valid_lable(head, "hi", 0, test_number++);
    tester_is_valid_lable(head, "5i", 0, test_number++);
    tester_is_valid_lable(head, "i555ADMSasjd555:", 1, test_number++);
    tester_is_valid_lable(head, "A555ADMSasjd555:", 1, test_number++); 
    tester_is_valid_lable(head, "i555ADMSasjd555i555ADMSasjd555i555ADMSasjd555:", 0, test_number++);
    tester_is_valid_lable(head, "#5i:", 0, test_number++);
    tester_is_valid_lable(head, "a5$i:", 0, test_number++);

    symbol_type = DATA;
    insert_to_symbol_table(&head, "hi:", test_number, symbol_type);

    tester_is_valid_lable(head, "hi:", 0, test_number++);
    tester_is_valid_lable(head, "hi", 0, test_number++);
    tester_is_valid_lable(head, "i555ADMSasjd555:", 1, test_number++);

    insert_to_symbol_table(&head, "hi2:", test_number, symbol_type);

    tester_is_valid_lable(head, "hi:", 0, test_number++);
    tester_is_valid_lable(head, "hi", 0, test_number++);
    tester_is_valid_lable(head, "i555ADMSasjd555:", 1, test_number++);
    tester_is_valid_lable(head, "hi2:", 0, test_number++);
    
    free_lable_list(&head);
    END_TEST("run_tests_is_valid_lable");
}



void run_first_pass_tests(){ 
    /*
    run_tests_handle_label();
    
    */
}



/*
void run_tests_handle_label() {
    File_Config* file_config;
    Ins_Node *expted_node_good, *node;
    Symbol_Table* expted_symbol_table;

    int test_num;
    char good_word1[MAX_LEN], bad_word1[MAX_LEN];
    Symbol_Type symbol_type;
    
    START_TEST("tests_handle_label");

    test_num = 0;
    file_config = intialiez_file_config();
    expted_symbol_table = intialiez_symbol_table();
    node = intialiez_ins_head();
    expted_node_good = intialiez_ins_head();
  
  
    symbol_type = DATA;
    strcpy(good_word1, "hi:");

    set_error_ins(expted_node_good, 0, "");
    set_IC_ins(expted_node_good, file_config->IC_counter);
    set_line_number_ins(expted_node_good, 0);
    expted_node_good->next = NULL;
    
    set_error_ins(node, 0, "");
    set_IC_ins(node, file_config->IC_counter);
    set_line_number_ins(node, 0);
    node->next = NULL;

    expted_symbol_table = intialiez_symbol_table();

    insert_to_symbol_table(expted_symbol_table, good_word1, file_config->DC_counter, symbol_type);
    tester_handle_label(file_config, node, good_word1, symbol_type, expted_node_good, expted_symbol_table, test_num);
    set_error_ins(expted_node_good, 1, ERROR_NOT_VALID_LABEL);
    set_error_ins(node, 0, "");
    tester_handle_label(file_config, node, good_word1, symbol_type, expted_node_good, expted_symbol_table, test_num);
*/
    /*every kind*/
    /*
    set_error_ins(expted_node_good, 0, "");
    set_error_ins(node, 0, "");
    symbol_type = CODE;
    strcpy(good_word1, "hi:");
    insert_to_symbol_table(expted_symbol_table, good_word1, file_config->DC_counter, symbol_type);
    tester_handle_label(file_config, node, good_word1, symbol_type, expted_node_good, expted_symbol_table, test_num);
    
    set_error_ins(expted_node_good, 0, "");
    set_error_ins(node, 0, "");
    symbol_type = EXTERNALT;
    strcpy(good_word1, "hi:");
    insert_to_symbol_table(expted_symbol_table, good_word1, file_config->DC_counter, symbol_type);
    tester_handle_label(file_config, node, good_word1, symbol_type, expted_node_good, expted_symbol_table, test_num);
*/
    /*bad label*/
    /*
    symbol_type = CODE;
    strcpy(bad_word1, good_word1);
    set_error_ins(node, 0, "");
    tester_handle_label(file_config, node, bad_word1, symbol_type, expted_node_good, expted_symbol_table, test_num);
    */ /*not legal label*/ /*
    strcpy(bad_word1, "ssss");
    set_error_ins(node, 0, "");
    tester_handle_label(file_config, node, bad_word1, symbol_type, expted_node_good, expted_symbol_table, test_num);

    if(node!=NULL) {
        free_ins_node(node);
    }
    if(expted_node_good!=NULL) {
        free_ins_node(expted_node_good);
    }
    if(expted_symbol_table!=NULL) {
        free_symbol_table(expted_symbol_table);
    }
    if(file_config!=NULL) {
        free_file_config(file_config);
    }
    END_TEST(" ");
}

*/
