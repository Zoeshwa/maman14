#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labals.h"



//ASK: do we need to save pointer to the data?
struct Lable_Node {
    char* name;
    char from; // D-DC, I-IC //ASK: maybe enum instad?
    int line; //ASK: the number? value od DC/IC
    int type; // type - entry etc...
    struct Lable_Node* next;
};

//TODO: change name
//ASK
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