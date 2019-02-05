#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>

#include "semantic.h"

/*
int errors_list_index = 0;

void print_sm_errors() {
    int i;
    for(i = 0; i < errors_list_index; i++) {
        printf("SEMANTIC ERROR ligne %d : %s is %d", errors_list[i].ligne, errors_list[i].NOM, errors_list[i].error_type);
    }
}
*/


t_tab_idf new_idf(char* name, t_Idf type) {
    t_tab_idf idf;
    strcpy(idf.NOM, name);
    idf.TYPE = type;
    idf.value = 0;
    idf.typevar = NOTHING;
    return idf;
}

t_tab_idf new_idfArg(char* name, t_Idf type) {
 t_tab_idf idf;
    strcpy(idf.NOM, name);
    idf.TYPE = type;
    idf.value = 0;
    idf.typevar = NOTHING;
    return idf;
}


bool isDeclared(char* name) {
    int i;
    bool res = false;
    for(i = 0; i < symbole_t_index; i++){
        if(strcmp(table_symboles[i].NOM, name) == 0) {
		        res = true;
		        break;
		}
	}
	int j;
	 for(j = 0; j < symbole_t_indexArg; j++){
        if(strcmp(table_symbolesArg[j].NOM, name) == 0) {
		        res = true;
		        break;
		}
	}
	return res;
}

bool isDeclaredArg(char* name){
	//int i;
    bool res = false;
    /*
    for(i = 0; i < symbole_t_index; i++){
        if(strcmp(table_symboles[i].NOM, name) == 0) {
		        res = true;
		        break;
		}
	}
	*/
   return res;
}

bool isConst(char* name) {
    int i;
    bool res = false;
    for(i = 0; i < symbole_t_index; i++) {
        if(strcmp(table_symboles[i].NOM, name) == 0) {
            if(table_symboles[i].TYPE == TCONST) {
                res = true;
                break;
            }
        }
    }
    return res;
}


void print_syntax_errors(char* name, int row, char* error){
  printf("syntax_lexical_error : %s in row %d is %s\n", name, row, error);
}

void print_sm_error(char* name, int row, char* error) {
    printf("\n Semantic Error  😜😝😜 : %s in row %d %s\n", name, row, error);
}

// TNATURAL  TARRAY TPOSITIVE TSTRING  TCHARACTER  TBOOLEAN  TFLOAT  TRANGE

char* typevar(t_type enumm){
	if(enumm == TINTEGER){
		char* chaine = "Integer";
		return chaine;
	} else if(enumm == TNATURAL){
		char* chaine = "Natural";
		return chaine;
	} else if(enumm == TARRAY){
		char* chaine = "Array";
		return chaine;
	} else if(enumm == TPOSITIVE){
		char* chaine = "Positive";
		return chaine;
	} else if(enumm == TSTRING){
		char* chaine = "String";
		return chaine;
	} else if(enumm == TCHARACTER){
		char* chaine = "Character";
		return chaine;
	}  else if(enumm == TBOOLEAN){
		char* chaine = "Boolean";
		return chaine;
	}  else if(enumm == TFLOAT){
		char* chaine = "Float";
		return chaine;
	}  else if(enumm == TRANGE){
		char* chaine = "Range";
		return chaine;
	}  else if(enumm == NOTHING){
		char* chaine = "NON";
		return chaine;
	} else if(enumm == ID){
		char* chaine = "Simple ID";
		return chaine;
	}
}


void printf_table_S(){
    int i;
    for(i = 0; i < symbole_t_index; i++) {
            if(table_symboles[i].TYPE == TPACKAGE) {
                printf("\n   T_PACKAGE               |  %s   |  %s   | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar), table_symboles[i].value);
            }
            if(table_symboles[i].TYPE == TCONST) {
                printf("\n   T_CONST                 | %s  | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            }
            if(table_symboles[i].TYPE == TVAR) {
                printf("\n   T_VAR                  |  %s  | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            }
            if(table_symboles[i].TYPE == TPROC) {
                printf("\n   T_PROCEDURE             |  %s   |  %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            }
            if(table_symboles[i].TYPE == TARGPROC) {
                printf("\n   T_ARGUMENT_PROCEDURE    | %s | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            }
             if(table_symboles[i].TYPE == TFUNC) {
                printf("\n   T_FUNCTION              |  %s  | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            } if(table_symboles[i].TYPE == TDECLPROC) {
                printf("\n   T_DEC_PROCEDURE         |  %s  | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            }  if(table_symboles[i].TYPE == TDECLPACK) {
                printf("\n   T_DECL_PACKAGE          |  %s  |  %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            }  if(table_symboles[i].TYPE == TARGFUNC) {
                printf("\n   T_ARGUMENT_FUNCTION     |  %s  | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            }  if(table_symboles[i].TYPE == TDECLFUNC) {
                printf("\n   T_DECLARATION_FUNCTION  | %s  | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            }  if(table_symboles[i].TYPE == TDECLRECORDF) {
                printf("\n   T_DECL_RECORD_FUNCTION  | %s  | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            } if(table_symboles[i].TYPE == TDECLRECORDPROC) {
                printf("\n   T_DECL_RECORD_PROCEDURE | %s  | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            } if(table_symboles[i].TYPE == TDECLRECORDP) {
                printf("\n   T_DECL_RECORD_PACKAGE   | %s  | %s | %d \n", table_symboles[i].NOM, typevar(table_symboles[i].typevar),  table_symboles[i].value);
            }

    }
    int j;

        for(j = 0; j < symbole_t_indexArg; j++) {
            if(table_symbolesArg[j].TYPE == TPACKAGE) {
                printf("\n   T_PACKAGE  | %s  | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            }
            if(table_symbolesArg[j].TYPE == TCONST) {
                printf("\n   T_CONST | %s  | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            }
            if(table_symbolesArg[j].TYPE == TVAR) {
                printf("\n   T_VAR   | %s  | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            }
            if(table_symbolesArg[j].TYPE == TPROC) {
                printf("\n   T_PROCEDURE  | %s  | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            }
            if(table_symbolesArg[j].TYPE == TARGPROC) {
                printf("\n   T_ARGUMENT_PROCEDURE   | %s  | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            }
             if(table_symbolesArg[j].TYPE == TFUNC) {
                printf("\n   T_FUNCTION    | %s   | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            } if(table_symbolesArg[j].TYPE == TDECLPROC) {
                printf("\n   T_DEC_PROCEDURE  |  %s  | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            }  if(table_symbolesArg[j].TYPE == TDECLPACK) {
                printf("\n   T_DECL_PACKAGE  |  %s  | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            }  if(table_symbolesArg[j].TYPE == TARGFUNC) {
                printf("\n   T_ARGUMENT_FUNCTION    |  %s    | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            }  if(table_symbolesArg[j].TYPE == TDECLFUNC) {
                printf("\n   T_DECLARATION_FUNCTION   |  %s    | %s \n", table_symbolesArg[j].NOM,  typevar(table_symbolesArg[j].typevar));
            } if(table_symboles[i].TYPE == TDECLRECORDF) {
                printf("\n   T_DECL_RECORD_FUNCTION   |  %s   | %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            } if(table_symboles[i].TYPE == TDECLRECORDPROC) {
                printf("\n   T_DECL_RECORD_PROCEDURE  |  %s   |  %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            } if(table_symboles[i].TYPE == TDECLRECORDP) {
                printf("\n   T_DECL_RECORD_PACKAGE   |  %s    |  %s \n", table_symbolesArg[j].NOM, typevar(table_symbolesArg[j].typevar));
            } 
    }
}
