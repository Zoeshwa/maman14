#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "first_pass.h"


#define MAX_LEN 80

int empty_line(char* line){
    char* p = line;
    p = skip_spaces(p);
    if (*p == '\n' || *p == '\0'){
        return 1;
    }
    else{
        return 0;
    }
}

int comment_line(char* line){
    char* p =line;
    p = skip_spaces(p);
    if (*p == ';'){
        return 1;
    }
    else{
        return 0;
    }
}

update_error(struct Ins_Node** head, char* line){
    (head)->err_msg = (char)malloc(strlen(line)*sizeof(char));
    strcpy((*head)->err_msg, line);

}

// Function to insert a new Lable_Node at the beginning of the list
void insertLable_Node(struct Lable_Node** head, char* name, int DC, char* type, char from) {
    // Create a new Lable_Node
    struct Lable_Node* newLable_Node = (struct Lable_Node*)malloc(sizeof(struct Lable_Node));
    // Allocate memory for the name and copy the string
    newLable_Node->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newLable_Node->name, name);
    newLable_Node->from = from;
    newLable_Node->type = (char*)malloc((strlen(type) + 1) * sizeof(char));
    strcpy(newLable_Node->type, type);
    newLable_Node->line = DC;

    // If the list is empty, make the new Lable_Node the head of the list
    if (*head == NULL) {
        *head = newLable_Node;
    } else {
        // Otherwise, insert the new Lable_Node at the beginning
        newLable_Node->next = *head;
        *head = newLable_Node;
    }
}


// Function to insert a new Ins_Node at the beginning of the list
void insertIns_Node(struct Ins_Node** head, int IC, int line_num) {
    // Create a new Ins_Node
    struct Ins_Node* newIns_Node = (struct Ins_Node*)malloc(sizeof(struct Ins_Node));
    // Allocate memory for the name and copy the string
    newIns_Node->error = 0;
    newIns_Node->IC = IC;
    newIns_Node->line = line_num;
    newIns_Node->next = NULL;

    // If the list is empty, make the new Ins_Node the head of the list
    if (*head == NULL) {
        *head = newIns_Node;
    } else {
        // Otherwise, insert the new Ins_Node at the beginning
        newIns_Node->next = *head;
        *head = newIns_Node;
    }
}

int is_Ins(char* word){
    if (word[strlen(word)-1] == ':')
        return 1;
    return 0;
}


int is_valid_char(char c){
    if ((47< c && c<58) || (64< c && c<91) || (96< c && c<123))
        return 1;
    return 0;
}

int is_valid_Ins(char* Ins){
    if (strlen(Ins)>= 31){
        return 0;
    }
    //needs a function that checks its not a saved word
    // missing a function that goes over Ins list to check Ins os not defined twice
    while (is_valid_char(*Ins)){Ins++;}
    if (*Ins == ':'){
        return 1;
    }
    else{
        return 0;
    }
}