#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
int runProg(int argc, char* argv[]){
    int ctr;

    /* for every file read from terminal*/
    /*
    for (ctr=1; ctr < argc; ctr++){
*/
        /*first pass phase*/



        /*macro phase vars*/
        /*
        FILE* am_file, *src_file;
        char *p, *file_name;
        char cur_word[MAX_LEN], input[MAX_LEN];
        int mcro=0;

        /*open an am file*/
        /*
        make_am_name(argv[ctr], cur_word);
        file_name = argv[ctr];
        am_file = fopen(cur_word,"w+");
        src_file = fopen(file_name, "r");
        if (am_file == NULL) {printf("Error creating am file");}
        if (src_file == NULL) {printf("Error creating reading file");}
        struct Macro_Node* head = NULL;
        struct Macro_Node* head_ptr = NULL;
*/

        /*start reading line by line*/
        /*
        while (fgets(input, MAX_LEN, src_file) != NULL){
            printf("input is: %s\n", input);
            p = input;
            get_next_word(input,cur_word, p);
            printf("cur_word is: %s\n", cur_word);
            if (mcro == 1){
                /*checking end of macro def*/
                /*
                if (strcmp(cur_word,"endmcro") ==0){
                    printf("end of macro def\n");
                    mcro=0;
                }
                /* if we are inside a macro, insert the lines to macro content*/
                /*
                else{
                    printf("updating macro contect\n");
                    update_macro_contect(&head, input);
                }
                continue;
            }
            head_ptr = search_macro_list(head, cur_word);
            if (head_ptr != NULL){
                printf("found in macro list, writing content to file\n");
                fwrite(head_ptr->content, 1, strlen(head_ptr->content), am_file);
            }
            */
            /* beginning of macro def*/
            /*
            else if(strcmp(cur_word,"mcro") == 0){
                printf("its a macro def\n");
                p = skip_spaces(p);
                p += strlen(cur_word);
                get_next_word(input,cur_word, p);
                printf("macro name is: %s\n", cur_word);
                insertMacro_Node(&head, cur_word);
                mcro=1;
            }
            /* regular line*/
            /*
            else{
                printf("regular line\n");
                fwrite(input, 1, strlen(input), am_file);
            }

        }

        int IC, DC, line_num;
        struct Ins_Node *ins_head, *curr_ins;
        struct Data_Node *Data_head, *cur_Data;       
        struct Lable_Node* Lables_head;

        line_num = 1;
        IC = 100;
        DC = 0;
        ins_head = NULL;
        curr_ins = NULL;
        Data_head = NULL;
        cur_Data = Data_head;
        Lables_head = NULL;
*/
        /*first pass*/
        /*
        while (fgets(input, MAX_LEN, am_file) != NULL){        
            
            p = input;
            char* lable;
            lable = NULL;
            
            if (empty_line(input) || comment_line(input)){continue;}
*/
            /*otherwise lines should be added*/
            /*
            if (ins_head == NULL) { /*first line*/
            /*
                insertIns_Node(&ins_head, IC, line_num);
                curr_ins = ins_head;
            }
            else { /* any other line*/
            /*
                IC += 1;
                insertIns_Node(&curr_ins, IC, line_num);
            }
           
            get_next_word(input,cur_word, p);
            p = skip_spaces(p);

            if (is_lable(cur_word)) {
                /* TODO: just for the compiling
                if (!(is_valid_lable(cur_word))) {
                    curr_ins->is_error = 1;
                    update_error(&curr_ins, "not a valid lable\n");
                    continue;
                }
                */
               /*
                lable = (char*)malloc((strlen(cur_word)) * sizeof(char));
                strcpy(lable, cur_word);
                p += strlen(cur_word);
                get_next_word(input,cur_word, p);
                p = skip_spaces(p);
            }
            
            if (is_data(cur_word)){ /* .data, .extern or .string .entry*/
            /*
                insertLable_Node(&Lables_head, lable, DC ,cur_word, "D"); /*1 is for DC 0 for IC*/
                /*
                p = skip_spaces(p);
                /* TODO
                DC = update_data_list(cur_Data, p, input, DC);
                */
               /*
                continue;
            }
            else{ /* is instruction*/
            /*
                if (lable != NULL){
                    /*TODO: not compiling*/
                    /* insertLable_Node(&Lables_head, lable, DC , 1); */
                    /*1 is for DC 0 for IC*/
                    /*
                }
                curr_ins = update_Ins_list(curr_ins, p, input, IC);

            }
        
        }    

    }
    return 0;

}
*/



/*TODO: delete - i have instade*/
/* Function to insert a new Lable_Node at the beginning of the list*/
void insertLable_Node(struct Lable_Node** head, char* name, int counter_value, char* type, char counter_type) {
    /* Create a new Lable_Node*/
    struct Lable_Node* newLable_Node = (struct Lable_Node*)malloc(sizeof(struct Lable_Node));

    /* Allocate memory for the name and copy the string*/
    newLable_Node->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newLable_Node->name, name);

    newLable_Node->counter_type = counter_type;
    newLable_Node->type = (char*)malloc((strlen(type) + 1) * sizeof(char));
    strcpy(newLable_Node->type, type);
    newLable_Node->counter_value = counter_value;

    /* If the list is empty, make the new Lable_Node the head of the list*/
    if (*head == NULL) {
        *head = newLable_Node;
    } else {
        /* Otherwise, insert the new Lable_Node at the beginning*/
        newLable_Node->next = *head;
        *head = newLable_Node;
    }
}