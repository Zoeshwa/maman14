#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testers.h"

void run_tester() 
{
    
    run_tests_handle_extern();
    
    /*
    run_get_words();
    
    run_is_legal_params();
    run_is_saved_word();
    run_first_pass_tests(); 
    run_labels_tests();
    run_file_config_print();
    run_input_testers();

    run_file_config_tests();
    tests_get_next_word();
    */
  
}

/*strings*/
void run_is_saved_word(){
    START_TEST("run_is_saved_word");
    tester_is_saved_word("mov", 1, 1);
    tester_is_saved_word("while", 0, 2);
    tester_is_saved_word("jmp", 1, 3);
    tester_is_saved_word("r0", 1, 4);
    tester_is_saved_word("data", 1, 5);
    tester_is_saved_word("Mov", 0, 6);
    tester_is_saved_word("move", 0, 7);
    END_TEST("run_is_saved_word");

}

void run_remove_colon_at_end() {
    char word1[] = "Hello:";
    char word2[] = "NoColon";
    char word3[] = "Multiple::";
    char word4[] = ":";
    char word5[] = "LOOP:";
    
    START_TEST("run_remove_colon_at_end");
    test_remove_colon_at_end(word1, 1, "Hello");
    test_remove_colon_at_end(word2, 2, "NoColon");
    test_remove_colon_at_end(word3, 3, "Multiple:");
    test_remove_colon_at_end(word4, 4, "");
    test_remove_colon_at_end(word5, 5, "LOOP");

    END_TEST("run_remove_colon_at_end");
  
}

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
    run_is_external_or_entry_ins_testers();
    run_is_extern_ins_testers();
    run_empty_line_testers();
    run_comment_line_testers();
    run_remove_colon_at_end();
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
    END_TEST("is_extern_ins");

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
    run_tests_is_symbol_already_exist();
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
    symbol_type = EXTERNAL;
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

    symbol_type = EXTERNAL;
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

void run_tests_is_symbol_already_exist() {
    Lable_Node* head;
    int test_number;
    Symbol_Type symbol_type;
    
    START_TEST("run_tests_is_symbol_already_exist");

    test_number = 0;
    head = NULL;
    
    tester_is_symbol_already_exist(head, "hi:", 0, test_number++);
    tester_is_symbol_already_exist(head, "hi", 0, test_number++);
    tester_is_symbol_already_exist(head, "5i", 0, test_number++);
    tester_is_symbol_already_exist(head, "i555ADMSasjd555:", 0, test_number++);
    tester_is_symbol_already_exist(head, "A555ADMSasjd555:", 0, test_number++);
    tester_is_symbol_already_exist(head, "i555ADMSasjd555i555ADMSasjd555i555ADMSasjd555:", 0, test_number++);
    tester_is_symbol_already_exist(head, "#5i:", 0, test_number++);
    tester_is_symbol_already_exist(head, "a5$i:", 0, test_number++);

    symbol_type = DATA;
    insert_to_symbol_table(&head, "hi:", test_number, symbol_type);

    tester_is_symbol_already_exist(head, "hi:", 1, test_number++);
    tester_is_symbol_already_exist(head, "hi", 0, test_number++); 
    tester_is_symbol_already_exist(head, "i555ADMSasjd555:", 0, test_number++);

    insert_to_symbol_table(&head, "hi2:", test_number, symbol_type);

    tester_is_symbol_already_exist(head, "hi:", 1, test_number++); 
    tester_is_symbol_already_exist(head, "hi2:", 1, test_number++);
    tester_is_symbol_already_exist(head, "hi", 0, test_number++);
    tester_is_symbol_already_exist(head, "i555ADMSasjd555:", 0, test_number++);

    symbol_type = CODE;
    insert_to_symbol_table(&head, "hi3:", test_number, symbol_type);
    insert_to_symbol_table(&head, "hi4:", test_number, symbol_type);
    symbol_type = EXTERNAL;
    insert_to_symbol_table(&head, "hi5:", test_number, symbol_type);
    insert_to_symbol_table(&head, "hi6:", test_number, symbol_type);

    tester_is_symbol_already_exist(head, "hi:", 1, test_number++); 
    tester_is_symbol_already_exist(head, "hi2:", 1, test_number++);
    tester_is_symbol_already_exist(head, "hi3:", 1, test_number++); 
    tester_is_symbol_already_exist(head, "hi4:", 1, test_number++);
    tester_is_symbol_already_exist(head, "hi5:", 1, test_number++); 
    tester_is_symbol_already_exist(head, "hi6:", 1, test_number++);
    
    tester_is_symbol_already_exist(head, "hi", 0, test_number++);
    tester_is_symbol_already_exist(head, "i555ADMSasjd555:", 0, test_number++);

    free_lable_list(&head);
    END_TEST("run_tests_is_symbol_already_exist");
}

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
    run_tests_handle_label();
}

void run_tests_handle_label() {
    File_Config* file_config;
    Lable_Node* expted_lable_head;
    int test_num;
    char good_word1[MAX_LEN], bad_word1[MAX_LEN];
    Symbol_Type symbol_type;

    START_TEST("tests_handle_label");
    test_num = 0;

    file_config = intialiez_file_config();
    expted_lable_head = NULL;

  
    symbol_type = DATA;
    strcpy(good_word1, "hi:");
    strcpy(bad_word1, "hi");

    /*bad word should not exist*/
    tester_handle_label(file_config, bad_word1, symbol_type, expted_lable_head, test_num++);
    
    /*good word - should be added*/
    insert_to_symbol_table(&(expted_lable_head), "hi", file_config->DC_counter, symbol_type);
    tester_handle_label(file_config, good_word1, symbol_type, expted_lable_head, test_num++);
    /*should not add twice*/
    tester_handle_label(file_config, good_word1, symbol_type,expted_lable_head, test_num++);

    symbol_type = CODE;
    strcpy(good_word1, "LOOP:");
    insert_to_symbol_table(&(expted_lable_head), "LOOP", file_config->DC_counter, symbol_type);
    tester_handle_label(file_config, good_word1, symbol_type,expted_lable_head, test_num++);
    /*should not add twice*/
    tester_handle_label(file_config, good_word1, symbol_type,expted_lable_head, test_num++);
    /*should not add twice even if have diffrent type*/
    symbol_type = EXTERNAL;
    tester_handle_label(file_config, good_word1, symbol_type,expted_lable_head, test_num++);


    symbol_type = EXTERNAL;
    strcpy(good_word1, "sdjkU:");
    insert_to_symbol_table(&(expted_lable_head), "sdjkU", file_config->DC_counter, symbol_type);
    tester_handle_label(file_config, good_word1, symbol_type,expted_lable_head, test_num++);

    symbol_type = CODE;
    strcpy(bad_word1, good_word1);
    tester_handle_label(file_config, bad_word1, symbol_type,expted_lable_head, test_num++);
    strcpy(bad_word1, "ssss");
    tester_handle_label(file_config, bad_word1, symbol_type,expted_lable_head, test_num++);
    strcpy(bad_word1, "33:");
    tester_handle_label(file_config, bad_word1, symbol_type,expted_lable_head, test_num++);
    
    free_lable_list(&expted_lable_head);
    free_file_config(file_config);

    END_TEST("tests_handle_label");
}

/*

void run_parsing() {
    char** parsed;
    int i;

    parsed = (char**)malloc(MAX_LEN * sizeof(char*)); 

    parsing(parsed, "LOOP: jmp L1, skj , sss");
    printf("results:\n");
    for(i = 0; parsed[i] != NULL ;i++){
        printf("|%s| \n", parsed[i]);
    }
    

    for(i = 0; parsed[i] != NULL ;i++) {
        free(parsed[i]);
        parsed[i] = NULL;
    }

    free(parsed);

       
       
       char** parsed;
        int i, len;
        parsed = (char**)malloc(MAX_LEN * sizeof(char*)); 

        parsing(parsed, &len , "LOOP: jmp L1, skj , sss");
        printf("results:\n");
        for(i = 0; i < len ;i++){
            printf("|%s| \n", parsed[i]);
        }

    
}
*/


void run_tests_handle_extern(){

    File_Config * file_config;
    char line1[MAX_LEN], line2[MAX_LEN], line3[MAX_LEN];
    file_config = intialiez_file_config();

    strcpy(line1, ".extern HI, BEY, YES\n");
    strcpy(line2, ".extern YOSSI\n");
    strcpy(line3, ".extern ZOE, , IDO, YES\n");
    
    file_config->curr_line_num++;
    printf("TEST: line1+7= %s\n", line1+7);
    handle_extren_line(file_config, line1, line1+7);
/*
    file_config->curr_line_num++;
    printf("line2+7= %s\n", line2+7);
    handle_extren_line(file_config, line2, line2+7);
    file_config->curr_line_num++;
    printf("line3+7= %s\n", line3+7);
    handle_extren_line(file_config, line3, line2+7);

*/

    print_file_config(file_config);
    free_file_config(file_config);
}

void run_get_words() {
    char** words;
    int i;
    char* line;
    line = (char*)calloc(MAX_LEN, sizeof(char));
    strcpy(line, "hello, world , , this, is a test, 1234\n");
    /*
    char* line1 = "hello, world this, is a test, 1234  , \n";
    char* line2 = "  , hello, world this, is a test, 1234\n";
    char* line3 = "hello, world , , this, is a test, 1234\n";
    char* line4 = "hello, world , ,  , his, is a test, 1234\n";
    char* line5 = "hello, world   his, is a test, 1234\n";
    char* line6 = "hello\n";
    
    */
    START_TEST("run_get_words");

 
    words = get_words(line);
    if (words) {
        for (i = 0; words[i] != NULL; i++) {
            if (words[i] != NULL) {
                printf("|%s|\n", words[i]);
                free(words[i]);
            }
        }
        free(words);
    } else {
        printf("Array is not valid.\n");
    }

    END_TEST("run_get_words");

}

void run_is_legal_params() {
    char* line = "hello, world ,this, is ,a ,test, 1234\n";
    char* line1 = "hello, world this, is a test, 1234  , \n";
    char* line2 = "  , hello, world this, is a test, 1234\n";
    char* line3 = "hello, world , , this, is a test, 1234\n";
    char* line4 = "hello, world , ,  , his, is a test, 1234\n";
    char* line5 = "hello, world   his, is a test, 1234\n";
    char* line6 = "hello\n";
    char* line7 = " HI, BEY, YES\n";
    int test_num;
    test_num = 0;
    START_TEST("run_is_legal_params");
    tester_is_legal_params(line, 1, test_num++);
    tester_is_legal_params(line6, 1, test_num++);
    tester_is_legal_params(line1, 0, test_num++);
    tester_is_legal_params(line2, 0, test_num++);
    tester_is_legal_params(line3, 0, test_num++);
    tester_is_legal_params(line4, 0, test_num++);
    tester_is_legal_params(line5, 0, test_num++);
    tester_is_legal_params(line7, 0, test_num++);
/*
    free(line);
    free(line1);
    free(line2);
    free(line3);
    free(line4);
    free(line5);
    free(line6);
    */
    END_TEST("run_is_legal_params");
}
/*TODO*/
void run_is_visible_chars_only() {
    tester_O_int_I_charP(is_visible_chars_only, "hiekejkdfjwek", 1, 0);
    tester_O_int_I_charP(is_visible_chars_only, "hiekejkdfjwek", 1, 0);

}