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


/*TODO:*/
struct Ins_Node* update_Ins_list(struct Ins_Node* cur_line, char * p, char * input, int IC){
    return NULL;
}


/**/


/*TODO: ido parse*/

/*My version*/
int params_parsing(char** results, int* len, char* p){
    char curr_word[MAX_LENGTH], *tmp;
    int results_index, curr_word_index;
    results_index = 0, curr_word_index = 0;


    while (*p != '\n' && *p != '\0' && *p != EOF) { /*till end of line*/
       /*if its between words - save the space between as a word*/
       if(*p == ',' || *p == ' ' || *p == '\t') {
            p = skip_spaces(p);
            while (*p == ',' || *p == ' ' || *p == '\t')
            {
                curr_word[curr_word_index++] = *p;
                p++;
                p = skip_spaces(p);

            }
            if(curr_word_index > 0) {
                curr_word[curr_word_index] = '\0';
                tmp = (char*)malloc((strlen(curr_word)+1) * sizeof(char));
                strcpy(tmp, curr_word);
                results[results_index++] = tmp; 
            }
            curr_word_index = 0;
            
       } else { /*there is word - save the the whole word*/
            while (*p != ',' && *p != ' ' && *p != '\t')
            {
                curr_word[curr_word_index++] = *p;
                p++;
            }
            curr_word[curr_word_index] = '\0';
            tmp = (char*)malloc((strlen(curr_word)+1) * sizeof(char));
            strcpy(tmp, curr_word);
            results[results_index++] = tmp; 
            curr_word_index = 0;
       }
    }
    *len = results_index;
    results[results_index] = NULL;

    return is_valid_commas_for_params(**results, len);
}

int is_valid_commas_for_params(char** results, int * len) {
    char curr_word[MAX_LENGTH], last_word, *p;
    /*every 2 words have one comma*/
    
    /*the final word dont have comma*/
    p = results[*len-1];
/*TODO*/
return 1;
}

char** parsing_ido(char* p){
    char tmp_word[MAX_LENGTH], **splited, *element;
    int comma_flag, s_index, tmp_index;
    comma_flag=0, s_index=0, tmp_index=0;

    splited = (char**)malloc(MAX_LENGTH * sizeof(char*)); /*alocating for ellements array */

    p = skip_spaces(p);
    if (*p == ',') { /*if the first char is comma in illegal*/
        printf("illegal comma\n");
        comma_flag=1;
        p++;
        p = skip_spaces(p);
    }

    while (*p != '\n' && *p != '\0') { /*till end of line*/
       
        printf("cur is:%c\n", *p);


        if (*p == ',' && comma_flag){ /*second or more commas in a row*/
            printf("more than one consecutive commas\n");
        }

        else if (*p == ',' && !comma_flag){  /*comma after element, save the element in the array*/
            tmp_word[tmp_index] = '\0';
            comma_flag=1;
            element = (char*)malloc((strlen(tmp_word)+1) * sizeof(char));
            strcpy(element, tmp_word);
            splited[s_index++] = element; 
            tmp_index=0;
            
            
            printf("splited[%d] is: |%s|\n", s_index-1, splited[s_index-1]);
            
        }
        else{
            tmp_word[tmp_index++] = *p; /*middle of an element read*/
        }
        p=skip_spaces(p);
        p++;
    }
    splited[s_index] = NULL;
    return splited;

}


int ido_main_for_pars(int argc, char* argv[]) {

    FILE* src_file;
    char** parsed;
    char  input[MAX_LENGTH], *file_name;
    int i;
    file_name = argv[1];
    src_file = fopen(file_name, "r");
    while (fgets(input, MAX_LENGTH, src_file) != NULL) {
        printf("input is: %s", input);
        parsed = parsing_ido(input);
        for(i=0; parsed[i] != NULL;i++){
            printf("next word is: %s\n", parsed[i]);
        }

    }


    return 0;
}




/*int main_ido(){
    File_Config* file_conf;
    FILE* am_file;
    Ins_Node* test_ptr;
    char input[MAX_LEN];

    am_file = fopen("assembly.am","r");
    file_conf = intialiez_file_config();

    while (fgets(input, MAX_LEN, am_file) != NULL){  
        printf("input is: %s\n", input)  ;
        handle_code_line(file_conf, input);
        file_conf->curr_line_num += 1;
        print_ins_node(file_conf->ins_tail);

    }

    test_ptr = file_conf->ins_head;
    while (test_ptr != NULL){
        print_ins_node(test_ptr);
        test_ptr = test_ptr->next;
    }
    return 0;

}*/

/*void test_init_ins_node(Ins_Node** head, int type, int src, int dest, int opcode){
       (*head)->type = type;
       (*head)->operrands[0] = src; 
       (*head)->operrands[1] =  dest;
       (*head)->opcode = opcode; 
}
*/

/*Description: check if a given char is a number or a letter*/
/*Input: a char to check*/
/*Output: true if the char is a number or a letter, else - false*/
int is_letter_or_num_char(char c){
    /*TODO: use isalpha for a-z, A-Z*/
    /*if (isdigit(c) || IS_UPPERCASE_LETTERS(c) || IS_LOWERCASE_LETTERS(c))
        return TRUE;
    return FALSE;*/
    return isalnum(c);
}



/*
void make_am_name(char* file_original_name, char* am_name){
    int i;
    
    i = 0;
    while (*file_original_name != '.'){
         am_name[i] = *file_original_name;
         i++;
         file_original_name++;
    }
    am_name[i++] = '.';
    am_name[i++] = 'a';
    am_name[i++] = 's';
    am_name[i] = '\0';
}
*/



void make_bin_DIR_word(Ins_Node** head, File_Config* file_conf){
    Lable_Node* lable;
    char* bin_adress, *bin_are;
    (*head)->bin_rep = (char*)calloc(13,sizeof(char));

    lable = find_lable(get_label_node_head(file_conf), (*head)->lable);
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
    strcat((*head)->bin_rep, bin_adress);
    strcat((*head)->bin_rep, bin_are);
    (*head)->bin_rep[13] = '\0';

}


/*ASK IDO: why lable_head?*/
void update_lable_adress(Ins_Node** node, Lable_Node* lable_head){
    (*node)->bin_rep = (char*)calloc(13,sizeof(char));

}



Ins_Node** add_extra_ins_words(Ins_Node** head, File_Config* file_config, int param_type[2], char** params){
    int i,j;
    j=0;

    if (param_type[0] == REG_DIR && param_type[1] == REG_DIR){ /*case of two parameters, both registers*/
        head = insert_ins_node(head,  get_IC_counter(file_config), get_curr_line_number(file_config)); 
        update_IC_counter(&file_config, 1);
        (*head)->type = REG_DIR;
        (*head)->operrands[0] = get_reg_num(params[0]);
        (*head)->operrands[1] = get_reg_num(params[1]);
        (*head)->bin_rep = (char*)calloc(13,sizeof(char));
        make_bin_REG_word(head, 0); 
                /*test*/
        printf("reg_extra_word is: ");
        print_ins_node(*head);

    }
    else{    
        for (i=0; i< 2; i++){
            if(param_type[i] == NONE){ /* if no params or 1 param set the src and dest accordinly with 0*/
                (*head)->operrands[i] = 0;
            }
            else if (param_type[i]){/*otherwise another node should be added with values of params*/
                head = insert_ins_node(head,  get_IC_counter(file_config), get_curr_line_number(file_config)); 
                update_IC_counter(&file_config, 1);
                (*head)->type = get_param_type(params[j]);
                if (i == 0){
                    (*head)->operrands[0] = set_operand_value(params[j++], head); 
                    (*head)->operrands[1] = NONE;
                }
                else{
                    (*head)->operrands[0] = NONE;
                    (*head)->operrands[1] = set_operand_value(params[j++], head);  
                }
                make_bin_extra_word(head,i, file_config);
              
            }
        }
    
    }
    return head;
}