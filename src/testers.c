#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testers.h"

#define NOT_GOOD printf("----------BAD------------\n")
#define GOOD printf("----------GOOD------------\n")
#define START_TEST(fun_name) printf("\nSTART TEST: %s\n", fun_name)

void run_tester() 
{
    START_TEST("run_label_testers");
    run_label_testers();
}


void run_label_testers() 
{
    tester_is_lable("hi:", 1);
    tester_is_valid_lable("hi:", 1);

    tester_is_lable("hi", 0);
    tester_is_valid_lable("hi", 0);

    tester_is_lable("5i:", 1);
    tester_is_valid_lable("5i", 0);

    tester_is_valid_lable("i555ADMSasjd555:", 1);
    tester_is_valid_lable("A555ADMSasjd555:", 1);

    tester_is_valid_lable("i555ADMSasjd555i555ADMSasjd555i555ADMSasjd555:", 0);
    tester_is_valid_lable("#5i:", 0);
    tester_is_valid_lable("a5$i:", 0);

}


int tester_is_lable(char * word, int expacted) 
{
    printf("tester_is_lable(%s, %d): ", word, expacted);
    if(is_lable(word) == expacted) {
        GOOD;
        return 1;
    } else {
        NOT_GOOD;
        return 0;
    }
}

int tester_is_valid_lable(char * word, int expacted) 
{
    printf("tester_is_valid_lable(%s, %d): ", word, expacted);
    if(is_valid_lable(word) == expacted) {
        GOOD;
        return 1;
    } else {
        NOT_GOOD;
        return 0;
    }
}

