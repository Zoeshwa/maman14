#ifndef _ENUMS_HEADER_
#define _ENUMS_HEADER_
    
    /*Defining macros of true or false for the benefit of code readings*/
    #define TRUE 1
    #define FALSE 0

    #define WORD_LEN_BINARY 12 /*Binary word size*/
    #define MAX_LEN 80 /*Line length / length of lines in the file*/

    /*ERRORS*/

   #define ERROR_GENERAL(curr_line_num) print_error("Something went worng", curr_line_num)

    /*labels errors*/
    #define ERROR_NOT_VALID_LABEL_CHAR(curr_line_num) print_error("Invalid lable - There is an invalid character\n", curr_line_num)
    #define ERROR_LABEL_ALREADY_EXISTS(curr_line_num) print_error("Invalid lable - The label already exists\n", curr_line_num)
    #define ERROR_LABEL_IS_SAVED_WORD(curr_line_num) print_error("Invalid lable - Using a reserved word as a label\n", curr_line_num)
    #define ERROR_NOT_VALID_LABEL_LEN(curr_line_num) print_error("Invalid label - length\n", curr_line_num)
    #define ERR_EXT_NOT_IN_USE(curr_line_num) print_error("External lable not in use\n", curr_line_num)

    /*entry errors*/
    #define ERROR_NOT_FOUND_ENTRY(curr_line_num) print_error("The entry label was not found in the file\n", curr_line_num)
    #define ERROR_LABEL_ENTRY_EXTERN(curr_line_num) print_error("It is not possible to define the same label as both entry and external in the same file\n", curr_line_num)

    /*ins errors*/
    #define ERROR_NOT_VALID_COMMAND_NAME(curr_line_num) print_error("not a valid command\n", curr_line_num)
    #define ERROR_NOT_COMPATIBLE_PARAMS(curr_line_num) print_error("not compatible num of params between enterd and command parameters\n", curr_line_num)
    #define ERROR_NOT_VALID_PARAMS(curr_line_num) print_error("not a valid parameter/s \n", curr_line_num)

    /*commas errors*/
    #define ERROR_ILLEGAL_COMMA(curr_line_num) print_error("Comma in illegal place\n", curr_line_num)
    #define ERROR_MISSING_COMMA(curr_line_num) print_error("missing a comma\n", curr_line_num)
    #define ERROR_MULTIPLE_COMMAS(curr_line_num) print_error("There are too many commas\n", curr_line_num)

    /*data errors*/
    #define ERROR_MULTIPLE_ARGUMENTS(curr_line_num) print_error("Too many arguments\n", curr_line_num)
    #define ERROR_INVALID_CHARS(curr_line_num) print_error("The string contains invalid characters\n", curr_line_num)
    #define ERROR_INVALID_QUOTES(curr_line_num) print_error("The string must be enclosed in double quotes\n", curr_line_num)
    #define ERROR_MISSING_ARGUMENTS(curr_line_num) print_error("Arguments are missing\n", curr_line_num)

    #define ERROR_INVALID_NUM(curr_line_num) print_error("Invalid number\n", curr_line_num)

     /*files error*/
    #define ERROR_CREATING_FILE(file_name) print_error_file("cannot create this file: ", file_name)
    #define ERROR_WRITING_FILE(file_name) print_error_file("cannot write this file:", file_name)
    #define ERROR_READING_FILE(file_name) print_error_file("cannot read this file:", file_name)

    /*ENUMS*/

    /*enums for label type*/
    typedef enum Symbol_Type {
        DATA,
        CODE,
        EXTERNAL
    }Symbol_Type;

    /*emums for data storage type*/
    typedef enum Data_Type {
        NUM,
        STRING
    } Data_Type;

    /*enums for param type*/
    typedef enum Param_Type {
        NONE = 0,  /*no param*/
        IMM = 1, /*number*/
        DIR = 3, /*label*/
        REG_DIR = 5,  /*register*/
        ERR = 6 /*there is error*/
    } Param_Type;
    
    /*commands*/
    typedef enum Coms{MOV, CMP, ADD, SUB, NOT, CLR, LEA, INC, DEC, JMP, BNE, RED, PRN, JSR, RTS, STOP, SKIP} Coms;

    void print_error(char* error_msg, int line_num);
    void print_error_file(char* error_msg, char* file_name);
#endif

