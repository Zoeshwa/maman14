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
    } Symbol_Type;

#endif
