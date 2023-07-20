#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros_struct.h"

#define MAX_LEN 80


/* Function to insert a new Macro_Node at the beginning of the list*/
void insertMacro_Node(struct Macro_Node** head, char* name) {
    /* TODO: not use?
    int lines;
    lines = 0;
    */

    /* Create a new Macro_Node*/
    struct Macro_Node* newMacro_Node = (struct Macro_Node*)malloc(sizeof(struct Macro_Node));
    /* Allocate memory for the name and copy the string*/
    newMacro_Node->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newMacro_Node->name, name);
    newMacro_Node->content = (char*)malloc(MAX_LEN*sizeof(char));
    newMacro_Node->next = NULL;

    /* If the list is empty, make the new Macro_Node the head of the list*/
    if (*head == NULL) {
        *head = newMacro_Node;
    } else {
        /* Otherwise, insert the new Macro_Node at the beginning*/
        newMacro_Node->next = *head;
        *head = newMacro_Node;
    }
}


void update_macro_contect(struct Macro_Node** head, char* line){
    (*head)->lines += 1;
    (*head)->content = (char*)realloc((*head)->content, MAX_LEN*(*head)->lines*sizeof(char));
    /*first insertion of content*/
    if ((*head)->lines == 1){(*head)->content[0] = '\0';}
    line = skip_spaces(line);
    strcat( (*head)->content, line);
    printf("macro contect is: %s\n", (*head)->content );
}

struct Macro_Node* search_macro_list(struct Macro_Node* head, char* name) {
    struct Macro_Node* current = head;

    /* Traverse the list and search for the target value*/
    while (current != NULL) {
        if (strcmp(current->name,name) == 0) {
            printf("found in macro list. macro %s\n", current->name);
            return current;  /* Found the value, return the Macro_Node*/
        }
        current = current->next;
    }
    printf("not in macro list\n");
    return NULL;  /* Value not found, return NULL*/
}

