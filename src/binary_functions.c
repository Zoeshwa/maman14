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

void make_bin_ins_word(Ins_Node** head){
    char *bin_src, *bin_opcode, *bin_dest, *bin_are;

    /*save as string the bin rep of the fields*/
    bin_src = int_to_binary_string((*head)->operrands[0], 3);
    bin_dest = int_to_binary_string((*head)->operrands[1], 3);
    bin_opcode = int_to_binary_string((*head)->opcode, 4);
    bin_are = "00";

    /*make the bin ins word*/
    strcat((*head)->bin_rep, bin_src);
    strcat((*head)->bin_rep, bin_opcode);
    strcat((*head)->bin_rep, bin_dest);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[13] = '\0';

    free(bin_src);
    free(bin_dest);
    free(bin_opcode);

    return;
}

void make_bin_IMM_word(Ins_Node** head, int i){
    char* bin_are, *bin_imm;
    bin_are = "00";
    bin_imm = int_to_binary_string(i, 10);
    printf("oprerand is: %d, bin_imm is: %s, bin_are: %s\n", i, bin_imm, bin_are);

    strcat((*head)->bin_rep, bin_imm);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[13] = '\0';

    free(bin_imm);


}

void make_bin_REG_word(Ins_Node** head, int i){
    char *bin_src, *bin_dest, *bin_are;

    /*save as string the bin rep of the fields*/
    bin_src = int_to_binary_string((*head)->operrands[0], 5);
    bin_dest = int_to_binary_string((*head)->operrands[1], 5);
    bin_are = int_to_binary_string(0, 2);
    
    strcat((*head)->bin_rep, bin_src);
    strcat((*head)->bin_rep, bin_dest);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[13] = '\0';

    printf("in reg bin rep is: %s\n", (*head)->bin_rep);

    free(bin_src);
    free(bin_dest);

    printf("in reg bin rep is: %s\n", (*head)->bin_rep);


}

void make_bin_DIR_word(Ins_Node** head, File_Config* file_conf){
    Lable_Node* lable;
    char* bin_adress, *bin_are;

    lable = find_lable(file_conf->label_head, (*head)->lable);
    if (lable == NULL){
        return;
    }
    bin_adress = int_to_binary_string(lable->counter_value, 10);

    if (get_label_symbol_type(lable) == EXTERNAL){
        bin_are = "01";
    }
    else{
        bin_are = "02";
    }
    strcat((*head)->bin_rep, bin_adress);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[13] = '\0';


}


void make_bin_extra_word(Ins_Node** head, int param, File_Config* file_conf){
    int type;
    type = (*head)->type;
    if (type == IMM){ 
        make_bin_IMM_word(head, (*head)->operrands[param]);
        printf("imm_extra_word is: ");
            print_ins_node(*head);


    }else if (type == REG_DIR){ 
        make_bin_REG_word(head,(*head)->operrands[param]);
        printf("reg_extra_word is: ");
                print_ins_node(*head);


    }else if (type == DIR){ 
        make_bin_DIR_word(head, file_conf);
        printf("reg_dir_word is: ");
                print_ins_node(*head);


    }

}

