#ifndef _ENUMS_HEADER_
#define _ENUMS_HEADER_

    #define _ENUMS_HEADER_
    
    #define TRUE 1
    #define FALSE 0

    /*ERROR STR*/
    #define ERROR_GENERAL(curr_line_num) printf("ERROR in line %d: Something went worng\n", curr_line_num)

    /*labels errors*/
    #define ERROR_NOT_VALID_LABEL_CHAR(curr_line_num) printf("ERROR in line %d: not a valid lable - There is an invalid character\n", curr_line_num)
    #define ERROR_LABEL_ALREADY_EXISTS(curr_line_num) printf("ERROR in line %d: not a valid lable - The label already exists\n", curr_line_num)
    #define ERROR_LABEL_IS_SAVED_WORD(curr_line_num) printf("ERROR in line %d: not a valid lable - Using a reserved word as a label\n", curr_line_num)
    #define ERROR_NOT_VALID_LABEL_LEN(curr_line_num) printf("ERROR in line %d: Invalid label length\n", curr_line_num)

    /*labels errors*/
    #define ERROR_NOT_VALID_COMMAND_NAME(curr_line_num) printf("ERROR in line %d: not a valid command\n", curr_line_num)
    #define ERROR_NOT_COMPATIBLE_PARAMS(curr_line_num) printf("ERROR in line %d: not compatible num of params between enterd and command parameters\n", curr_line_num)


    /*commas errors*/
    #define ERROR_ILLEGAL_COMMA(curr_line_num) printf("ERROR in line %d: Comma in illegal place\n", curr_line_num)
    #define ERROR_MISSING_COMMA(curr_line_num) printf("ERROR in line %d: missing a comma\n", curr_line_num)
    #define ERROR_MULTIPLE_COMMAS(curr_line_num) printf("ERROR in line %d: There are too many commas\n", curr_line_num)

    /*data errors*/
    #define ERROR_MULTIPLE_ARGUMENTS(curr_line_num) printf("ERROR in line %d: Too many arguments\n", curr_line_num)
    #define ERROR_INVALID_CHARS(curr_line_num) printf("ERROR in line %d: The string contains invalid characters\n", curr_line_num)
    #define ERROR_INVALID_QUOTES(curr_line_num) printf("ERROR in line %d: The string must be enclosed in double quotes\n", curr_line_num)

    /*Warnning STR*/
    #define WARNING_LABEL_NOT_USE(curr_line_num) printf("WARNING in line %d: This label is not use\n", curr_line_num)
/*
    typedef enum Scope_Type {
        RELOCATABLE,
        EXTERNAL 
    } Scope_Type;

*/

    typedef enum Symbol_Type {
        DATA,
        CODE,
        EXTERNAL
    }Symbol_Type;

    typedef enum Data_Type {
        NUM,
        STRING
    } Data_Type;

#endif
