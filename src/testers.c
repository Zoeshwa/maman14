#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testers.h"

#define NOT_GOOD printf("----------BAD------------\n")
#define GOOD printf("----------GOOD------------\n")
#define START_TEST(fun_name) printf("\nSTART TEST: %s\n", fun_name)


void run_tester() 
{
    run_is_lable_testers();
    run_input_testers();
}


void run_is_lable_testers() 
{
    int i;
    i = 0;
    START_TEST("run_label_testers");
    tester_O_int_I_charP(is_lable, "hi:", 1, i++);
    tester_O_int_I_charP(is_lable, "hi", 1, i++);
    tester_O_int_I_charP(is_lable, "5i", 1, i++);
}

int tester_is_lable(char * word, int expacted) 
{
    int result;
    printf("tester_is_lable(%s, %d): ", word, expacted);
    result = is_lable(word);
    if(result == expacted) {
        GOOD;
        return 1;
    } else {
        NOT_GOOD;
        return 0;
    }
}

void tester_O_int_I_charP(int (*function)(char*), char* input, int expected_result, int test_number) {
    int result;
    result = function(input);
    if (result == expected_result) {
        printf("V - PASS: Expected result (%d) matches the actual result.\n", expected_result);
    } else {
        printf("X - FAIL: test_num (%d), Expected (%d) - Actual result (%d)\n",test_number, expected_result, result);
    }
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


    char* get_next_word(char* str, char* word, char* ptr);


    char* skip_spaces(char* p);

    void insert_to_symbol_table(Symbol_Table* table, char* word, int counter_value, Symbol_Type symbol_type);
    Symbol_Table* intialiez_symbol_table();
    int is_valid_lable(Symbol_Table* table, char* word);
    Lable_Node* is_symbol_already_exist(Symbol_Table* table, char * symbol_name);
    void set_label_name(char * word, Lable_Node* new_lable);






    void insertIns_Node(struct Ins_Node** head, int IC, int line_num);
    void update_error(struct Ins_Node** head, char* line);
    struct Ins_Node* update_Ins_list(struct Ins_Node* cur_line, char * p, char * input, int IC);
    void add_ins_to_list(struct Ins_Node *ins_head, struct Ins_Node *curr_ins, int IC,int line_num);
    
*/

