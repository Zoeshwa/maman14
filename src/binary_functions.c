#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_functions.h"

/*Description: A function converts a number to a string representing the number in binary*/
/*Input: number - numeric value to convert, num_bits - number of bits to produce the binary word*/
/*Output: A string representing the number in binary */
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

/*Description: A function that defines the binary word of the given node in the instruction image - in this case DIR type nodes*/
/*Input: node - ins_node pointer of the word to convert, file_conf - File_Config pointer*/
void make_bin_DIR_word(Ins_Node** node, File_Config* file_conf){
    Lable_Node* lable;
    char* bin_adress, *bin_are, *binary_word;
    
    binary_word = (char*)calloc(13,sizeof(char));

    lable = find_lable(get_label_node_head(file_conf), get_ins_label(*node));
    if (lable == NULL){ /*lable would be declaired later so bin word stays NULL*/
        return;
    }
    
    bin_adress = int_to_binary_string(get_label_counter_value(lable), 10);

    /*get the ARE filed*/
    if (get_label_symbol_type(lable) == EXTERNAL){
        bin_are = "01";
    }
    else{
        bin_are = "10";
    }

    /*Concatenate the fields into one binary word*/
    strcat(binary_word, bin_adress);
    strcat(binary_word, bin_are);
    binary_word[13] = '\0';
    
    set_bin_rep_ins_node(node, binary_word);
}

const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* Description: Convert a binary word to a base64-encoded representation. 
   Converts a 12-bit binary word to a 2-character base64-encoded string. 
   This function maps 12 bits of binary input into 8 bits of base64-encoded output. */
/* Input: arr - A character array of at least size 2 to store the resulting base64-encoded characters.
   binary_word - A null-terminated string containing the 12-bit binary word to be encoded. The string must contain only '0' and '1' characters representing the binary digits. */
/* Output: The base64-encoded representation of the input binary word is stored in the 'arr' array, which will contain 2 characters. */
void bin_to_base64(char arr[2], const char* binary_word) {
    int i, bin_value;
    
    bin_value = 0;

    /* Convert the 12-bit binary word to an integer value */
    for (i = 0; i < 12; i++) {
        bin_value <<= 1;
        if (binary_word[i] == '1') {
            bin_value |= 1;
        }
    }

    /* Convert the integer value to base64-encoded characters using a lookup table */
    arr[0] = base64_table[(bin_value >> 6) & 0x3F];
    arr[1] = base64_table[bin_value & 0x3F];
    arr[2] = '\0';
}
