#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>

#define MAX_IDFS 200

typedef enum {
  //other tokens
    ERROR_ID_TOKEN,
    ERROR_INT_TOKEN,
    ERROR_REALINT_TOKEN,
    ERROR_STRING_TOKEN,
  //keyword tokens
    ERROR_PACKAGE_TOKEN,
    ERROR_PROJECT_TOKEN,
    ERROR_FOR_TOKEN,
    ERROR_IS_TOKEN,
    ERROR_END_TOKEN,
    ERROR_USE_TOKEN,
    ERROR_WITH_TOKEN,
    ERROR_TYPE_TOKEN,
    ERROR_RANGE_TOKEN,
    ERROR_NEW_TOKEN,
    ERROR_ARRAY_TOKEN,
    ERROR_FUNCTION_TOKEN,
    ERROR_RETURN_TOKEN,
    ERROR_OF_TOKEN,
    ERROR_OUT_TOKEN,
    ERROR_BODY_TOKEN,
    ERROR_BEGIN_TOKEN,
    ERROR_LOOP_TOKEN,
    ERROR_IF_TOKEN,
    ERROR_THEN_TOKEN,
    ERROR_WHILE_TOKEN,
    ERROR_RECORD_TOKEN,
    ERROR_CASE_TOKEN,
    ERROR_WHEN_TOKEN,
    ERROR_NULL_TOKEN,
    ERROR_IN_TOKEN,
    ERROR_ALL_TOKEN,
    ERROR_NOT_TOKEN,
    ERROR_SOME_TOKEN,
    ERROR_ELSE_TOKEN,
    ERROR_AND_TOKEN,
    ERROR_PRAGMA_TOKEN,
    ERROR_SUBTYPE_TOKEN, 
    ERROR_PROCEDURE_TOKEN,
    ERROR_OR_TOKEN,
    ERROR_CONSTANT_TOKEN,
    ERROR_ELSIF_TOKEN,
    ERROR_PRIVATE_TOKEN,
    ERROR_MOD_TOKEN,
    ERROR_XOR_TOKEN,
    ERROR_OVERRIDING_TOKEN,
    ERROR_INTERFACES_TOKEN, 
    ERROR_OTHERS_TOKEN,
    ERROR_PRE_TOKEN,
    ERROR_POST_TOKEN,
    ERROR_DEPENDS_TOKEN, 
    ERROR_ON_TOKEN,
    ERROR_OFF_TOKEN,
    ERROR_LIMITED_TOKEN,
    ERROR_INTEGER_TOKEN,
    ERROR_TRUE_TOKEN, 
    ERROR_FALSE_TOKEN,
    ERROR_BOOLEAN_TOKEN,
    ERROR_NATURAL_TOKEN,
    ERROR_GLOBAL_TOKEN,
    ERROR_INPUT_TOKEN,
    ERROR_OUTPUT_TOKEN,
    ERROR_IN_OUT_TOKEN,
    ERROR_PUTLINE_TOKEN,
    ERROR_OLD_TOKEN,
    ERROR_LENGTH_TOKEN,
    ERROR_LAST_TOKEN,
    ERROR_FIRST_TOKEN,
    ERROR_VARSRANGE_TOKEN,
    ERROR_SPARKMODE_TOKEN,
    ERROR_FLOAT_TOKEN,
    ERROR_FIN_PACKAGE,
    ERROR_CHARACTER_TOKEN,
    ERROR_POSITIVE_TOKEN,
    ERROR_EXCEPTION_TOKEN,
    ERROR_STRINGKEY_TOKEN,
    ERROR_CHAR_TOKEN,

  // Symboles
     ERROR_PT_TOKEN,
     ERROR_AFF_TOKEN,
     ERROR_DEPENDING_TOKEN,
     ERROR_RANGEREDECLARE_TOKEN,
     ERROR_NOTEQUAL_TOKEN,
     ERROR_FROMTO_TOKEN,
     ERROR_TYPESYM_TOKEN,
     ERROR_MULT_TOKEN,
     ERROR_DIVIDE_TOKEN,
     ERROR_POWER_TOKEN,
     ERROR_EQUAL_TOKEN,
     ERROR_PV_TOKEN,
     ERROR_VR_TOKEN,
     ERROR_PLUS_TOKEN,
     ERROR_MINUS_TOKEN,
     ERROR_GREATERTHANEQUAL_TOKEN,
     ERROR_GREATERTHAN_TOKEN,
     ERROR_LESSTHANEQUAL_TOKEN,
     ERROR_LESSTHAN_TOKEN,
     ERROR_ANDLOGICAL_TOKEN,
     ERROR_PO_TOKEN,
     ERROR_PF_TOKEN,
     ERROR_COMMENT_TOKEN
} error_code_t;


// enum symbole table
typedef enum {
    TPACKAGE,
    TCONST,
    TPROC,
    TFUNC,
    TVAR,
    TDECLPROC,
    TARGPROC,
    TDECLPACK,
    TARGFUNC,
    TDECLFUNC,
    TDECLRECORDPROC,
    TDECLRECORDF,
    TDECLRECORDP
} t_Idf;

// enum symbole table
typedef enum {
    TINTEGER,
    TNATURAL,
    TARRAY,
    TPOSITIVE,
    TSTRING,
    TCHARACTER,
    TBOOLEAN,
    TFLOAT,
    TRANGE,
    ID,
    NOTHING
} t_type;

// struct symbole table
typedef struct {
    char NOM[100];
    t_Idf TYPE;
    int value;
    t_type typevar;
} t_tab_idf;

// enum error semantic
typedef enum {
    DEJA_DECLAREE_IDPACKAGE,
    DEJA_DECLAREE,
    IS_CONST
} sm_error_table;


// struct error semantic
typedef struct {
    char NOM[20];
    int   ligne;
    sm_error_table error_type;
} sm_error_list;

// semantic functions
bool isdeclared(char*);
bool isdeclaredArg(char*);
bool isConst(char*);
void addTo_Symbole_table(char*, t_Idf); // add to table_symboles
t_tab_idf new_idf(char*, t_Idf); // add to table_symboles
void add_semantic_error(char*, int, sm_error_table); // add to errors_list



// print errors
void print_syntax_errors(char*, int, char*);
void print_sm_error(char*, int, char*);
void print_sm_errorArg(char*, int, char*);
void print_sm_errors();


void printf_table_S();

sm_error_list errors_list[MAX_IDFS];

int symbole_t_index = 0;

t_tab_idf table_symboles[MAX_IDFS];


int symbole_t_indexArg = 0;
t_tab_idf table_symbolesArg[MAX_IDFS];
