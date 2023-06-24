#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct.h"


/*TODO*/
DATA_Table* intialiez_data_table() {
    DATA_Table* data_table;
    data_table = (DATA_Table*)malloc(sizeof(DATA_Table));
    data_table->head = NULL;
    data_table->tail = data_table->head;
    return data_table;
}

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


/*
int update_data_list(struct Data_Node** cur_Data, char* p,char* input, int DC){
    return 0;
}
*/

