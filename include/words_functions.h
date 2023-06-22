#define IS_NUMBER(c) (47< c && c<58)
#define IS_UPPERCASE_LETTERS(c) (64< c && c<91)
#define IS_LOWERCASE_LETTERS(c) (96< c && c<123)


int is_Ins(char* word);
int is_valid_char(char c);


/*TODO: maybe move to Labels*/
#define MAX_LABEL_LEN 31
#define COLON 58

int is_lable(char* word); 
int is_valid_lable(char* word);