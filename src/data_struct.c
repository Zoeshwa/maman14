#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct.h"


/*TODO: think about*/
struct Data_Node {
    char c; /*ASK why not the U? do we need also type maybe?*/
    int d;
    struct Data_Node* next;
};
/*
TODO
update_data_list ( ){
                    if (Data_head = NULL){ //first line
                        insertIns_Node(&Data_head, DC);
                        cur_Data = Data_head;
                    }
                    else{ // any other line
                        DC +=1;
                        insertIns_Node(&cur_Data, DC);
                    }

}*/