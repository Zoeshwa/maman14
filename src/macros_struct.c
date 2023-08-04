#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros_struct.h"

#define MAX_LEN 80

/* Macro_Node in macro linked list*/
struct Macro_Node {
    char* name;
    char* content;
    int lines;
    struct Macro_Node* next;
};

void make_am_file(char* orig_name){
    FILE* am_file, *src_file;
    char *p;
    char cur_word[MAX_LEN], input[MAX_LEN], file_name[MAX_LEN];
    int mcro;
    struct Macro_Node* head, *head_ptr;
    
    mcro = 0;
    head = NULL;
    head_ptr = NULL;

    /*open an am file*/
    add_extention(orig_name, cur_word, "am");
    add_extention(orig_name, file_name, "as"); /*creates the files acual name*/
    am_file = fopen(cur_word,"w+");
    src_file = fopen(file_name, "r");
    if (am_file == NULL) {printf("Error creating am file");}
    if (src_file == NULL) {printf("Error creating reading file");}

    /*start reading line by line*/
    while (fgets(input, MAX_LEN, src_file) != NULL) {
        p = input;
        p = skip_spaces(p);
        get_next_word(cur_word, p);
        if (mcro == 1){
            /*checking end of macro def*/
            if (strcmp(cur_word,"endmcro") ==0){
                mcro=0;
            }
            /* if we are inside a macro, insert the lines to macro content*/
            else{
                update_macro_contect(&head, input);
            }
            continue;
        }

        head_ptr = search_macro_list(head, cur_word);
        if (head_ptr != NULL){
            if (fwrite(head_ptr->content, 1, strlen(head_ptr->content), am_file)<0) {printf("errorr writing to file\n");}
        }

        /* beginning of macro def*/
        else if(strcmp(cur_word,"mcro") == 0){
            p += strlen(cur_word);
            p = skip_spaces(p);
            get_next_word(cur_word,p);
            insertMacro_Node(&head, cur_word);
            mcro=1;
        }
        /* regular line*/
        else{
            if (fwrite(input, 1, strlen(input), am_file)<0){
                printf("errorr writing to file\n");
            }
        }
    }
    fclose(am_file);

    print_macro_list(head);
    free_macro_list(&head);
}

/* Function to insert a new Macro_Node at the beginning of the list*/
void insertMacro_Node(struct Macro_Node** head, char* name) {

    /* Create a new Macro_Node*/
    struct Macro_Node* newMacro_Node = (struct Macro_Node*)malloc(sizeof(struct Macro_Node));
    /* Allocate memory for the name and copy the string*/
    newMacro_Node->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newMacro_Node->name, name);
    newMacro_Node->content = (char*)malloc(MAX_LEN*sizeof(char));
    newMacro_Node->lines = 0;
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
    if (((*head)->lines) == 1){
        (*head)->content[0] = '\0';
    }
    line = skip_spaces(line);
    strcat( (*head)->content, line);
}

struct Macro_Node* search_macro_list(struct Macro_Node* head, char* name) {
    struct Macro_Node* current = head;

    /* Traverse the list and search for the target value*/
    while (current != NULL) {
        if (strcmp(current->name,name) == 0) {
            return current;  /* Found the value, return the Macro_Node*/
        }
        current = current->next;
    }
    return NULL;  /* Value not found, return NULL*/
}

void free_macro_list(Macro_Node** head) {
    while (*head != NULL) {
        Macro_Node* temp = *head;
        *head = (*head)->next;

        /* Free the dynamically allocated memory for name and content */
        if(temp->name != NULL)
            free(temp->name);
        if(temp->content != NULL)
            free(temp->content);

        /* Free the node itself */
        free(temp);

        /* Set the pointer to NULL */
        temp = NULL;
    }
}

/*DELETE*/
void print_macro_list(Macro_Node* head) {
    printf("MACRO_LIST:\n");

    while (head != NULL) {
        printf("MACRO_NODE:\t");

        printf("Name: %s\t", head->name);
        printf("Content: %s\t", head->content);
        printf("Lines: %d\n", head->lines);

        head = head->next;
    }
}

