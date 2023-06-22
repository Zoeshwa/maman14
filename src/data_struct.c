#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct.h"


//TODO: think about
struct Data_Node {
    char c; //ASK why not the U? do we need also type maybe?
    int d;
    struct Data_Node* next;
};
