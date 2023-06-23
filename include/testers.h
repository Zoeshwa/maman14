/*
#if !defined(_TESTERS_HEADER_)
    #define _TESTERS_HEADER_
    int tester_is_lable(char * word, int expacted);
    int tester_is_valid_lable(char * word, int expacted);
    void run_label_testers();
    void run_tester();

#endif
*/

#ifndef _TESTERS_HEADER_
#define _TESTERS_HEADER_
    void run_tester();
    void run_is_lable_testers();

    int tester_is_lable(char * word, int expacted);
    void tester_O_int_I_charP(int (*function)(char*), char* input, int expected_result, int test_number);   
    void run_input_testers();
    void run_is_scope_ins_testers();
    void run_is_extern_ins_testers(); 
    void run_empty_line_testers();
    void run_comment_line_testers(); 
    void tests_get_next_word();
    void tester_get_next_word(char * str);

#endif

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
