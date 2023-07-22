/*
#if !defined(_ENUMS_HEADER_)
    #define _ENUMS_HEADER_
    typedef enum {
        FASLE = 0,
        TRUE
    }Boolean;
#endif
*/


#ifndef _ENUMS_HEADER_
#define _ENUMS_HEADER_

    #define _ENUMS_HEADER_
    
    #define TRUE 1
    #define FALSE 0

    #define PRINT_NUM_LINE_ERROR(line_num) printf("The Error in line %d\n", line_num)

    /*ERROR STR*/
    #define ERROR_NOT_VALID_LABEL "ERROR - not a valid lable\n"
    #define ERROR_NOT_VALID_LABEL_CHAR "ERROR - not a valid lable - There is an invalid character\n"
    #define ERROR_LABEL_ALREADY_EXISTS "ERROR - not a valid lable - The label already exists\n"
    #define ERROR_LABEL_IS_SAVED_WORD "ERROR - not a valid lable - Using a reserved word as a label\n"


    /*Warnning STR*/
    #define WARNING_LABEL_NOT_USE "WARNING - This label is not use\n"

    typedef enum Counter_Type {
        DC,
        IC
    } Counter_Type;
/*
    typedef enum Scope_Type {
        NONE, 
        ENTRY,
        EXTERNAL,
        UNKNOWEN
    } Scope_Type;
    */

    /*MAYBE page 19 in symbol table*/
    typedef enum Symbol_Type {
        DATA,
        CODE,
        EXTERNALT
    }Symbol_Type;

#endif
