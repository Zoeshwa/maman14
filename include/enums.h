#ifndef _ENUMS_HEADER_
#define _ENUMS_HEADER_

    #define _ENUMS_HEADER_
    
    #define TRUE 1
    #define FALSE 0

    #define PRINT_NUM_LINE_ERROR(line_num) printf("The Error in line %d\n", line_num)

    /*ERROR STR*/
    #define ERROR_NOT_VALID_LABEL_LEN "ERROR - not a valid lable - Exceeds size limit\n"
    #define ERROR_NOT_VALID_LABEL_CHAR "ERROR - not a valid lable - There is an invalid character\n"
    #define ERROR_LABEL_ALREADY_EXISTS "ERROR - not a valid lable - The label already exists\n"
    #define ERROR_LABEL_IS_SAVED_WORD "ERROR - not a valid lable - Using a reserved word as a label\n"

    #define ERROR_ILLEGAL_COMMA "ERROR - Comma in illegal place\n"
    #define ERROR_MISSING_COMMA "ERROR - missing a comma\n"
    #define ERROR_MULTIPLE_COMMAS "ERROR - There are too many commas\n"

    /*Warnning STR*/
    #define WARNING_LABEL_NOT_USE "WARNING - This label is not use\n"
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
