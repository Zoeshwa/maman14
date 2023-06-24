#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testers.h"



void run_tester() 
{
    run_is_lable_testers();
    run_input_testers();
 /*
    tests_get_next_word();
 */
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
    tester_get_next_word("entry input");
    tester_get_next_word("LOOP:          .extern");
    tester_get_next_word("LOOP: .extern");
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
