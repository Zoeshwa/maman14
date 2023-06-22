#if !defined(_TESTERS_HEADER_)
    #define _TESTERS_HEADER_
    int tester_is_lable(char * word, int expacted);
    int tester_is_valid_lable(char * word, int expacted);
    void run_label_testers();
    void run_tester();
#else
    #include "main.h"
#endif