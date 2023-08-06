#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_functions.h"

char* int_to_binary_string(int number, int num_bits) {
    int i;
    char* result = (char*)malloc((num_bits + 1) * sizeof(char));
    int sign_bit = (number < 0) ? 1 : 0;

    /* Adjust the number of bits for negative numbers */
    if (sign_bit) {
        number = (1 << (num_bits - 1)) + (number & ((1 << (num_bits - 1)) - 1));
    }

    for (i = num_bits - 1; i >= 0; i--) {
        result[i] = (number & 1) + '0'; /* Convert bit to '0' or '1' */
        number >>= 1; /* Shift right to get the next bit */
    }

    result[num_bits] = '\0'; /* Null-terminate the string */
    return result;
}

/*TODO TEST ZOE*/
void make_bin_DIR_word(Ins_Node** node, File_Config* file_conf){
    Lable_Node* lable;
    char* bin_adress, *bin_are, *result;
    result = (char*)calloc(13,sizeof(char));

    lable = find_lable(get_label_node_head(file_conf), get_ins_label(*node));
    /*ASK: IDO do we need this? there is a chanch its not valid because its not a label*/
    if (lable == NULL){ /*lable would be declaired later so bin word stays NULL*/
        return;
    }
    
    bin_adress = int_to_binary_string(get_label_counter_value(lable), 10);

    if (get_label_symbol_type(lable) == EXTERNAL){
        bin_are = "01";
    }
    else{
        bin_are = "10";
    }
    strcat(result, bin_adress);
    strcat(result, bin_are);
    result[13] = '\0';
    set_bin_rep_ins_node(node, result);
}


void bin_to_base64(char **arr, const char* binary_word) {
    int i, bin_value;
    char *result;
    static const  char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    result = (char*)calloc(2, sizeof(char));

    bin_value = 0;

    printf("binary_word: %s\n", binary_word);

    if(binary_word == NULL) {
        /*TODO*/
        printf("Error?\n");
        *arr = NULL;
        return;
    }

    for (i = 0; i < 12; i++) {
        bin_value <<= 1;
        if (binary_word[i] == '1') {
            bin_value |= 1;
        }
    }

    result[0] = base64_table[(bin_value >> 6) & 0x3F];
    result[1] = base64_table[bin_value & 0x3F];
    result[2] = '\0';

    printf("SS: %s\n", result);

    strcpy(*arr, result);
    free(result);
}


