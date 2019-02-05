#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>

#include "ScannerSpark.c"

#include "semanticc.c"


void Test_Symbole (CODES_LEX, char*);
void package();
void block();
void lire();
void INSTS();
void PROCEDURES();
void PROCEDURESP();
void ARGUMENTS();
void AffecInt();
void AffecN();
void AffecF();
void AffecB();
void CONSTANTFUNC();
void DECLSIMPLE();
void DECLS();
void DECLSTYPE();
void DECLSRECORD();
void TYPEARG();
void INOUTTYPE();
void TYPEARGF();
void ARRAYFUNC();
void ENUMFUNC();
void RANGEFUNC();
void RECORDFUNC();
void AFFECINSTS();
void FORINSTS();
void PUTLINEINST();
void WHILEINSTS();
void IFINSTS();
void COND();
void EXPR();
void term();
void fact();
void DECLSPack();
void Dec_function();
void  CASEINST();
void AffecSt();
void AffecCh();
void ARGUMENTSFunc();
void DECLSTYPEP();
void DECLSTYPEF();
void RECORDFUNCF();
void DECLSRECORDF();
void RECORDFUNCPack();
void DECLSRECORDPack();




//const char nomfichier[] = "/home/meriem/Desktop/spark/testspark4";
//FILE* fichier = NULL;

token Sym_cour;
char ID_Package[100];
char ID_Proc[100];
char ID_FUNC[100];

char idcont[100];
int a;
int b;
                                    

char ID_ProcSec[100];

token table_Proc[50];
int indexProc = 0;

bool sm_error = false;

int indexta = -1;
int indexArg = -1;


void Test_Symbole (CODES_LEX cl, char* messageErreur){
    //if(sm_error == false){
          if (Sym_cour.CODE == cl){
              //printf("  %s", Sym_cour.NOM);
              lire();
        } else if(Sym_cour.CODE == ERROR_TOKEN){
             printf("\n LEXICAL _______________INDEFINED_TOKEN________________ \n");
              exit(0);          
        }else {
            //printf("Semantic Error  😜😝😜 : %s in row %d is %s\n", name, row, error);
            printf("\n SYNTAX ERROR at row %d  Current token %s  EXPECTED token %s  \n\n", ligne, Sym_cour.NOM, messageErreur);
            exit(0);
        }
   // }
}

//PACKAGE ::= package body ID with SPARK_MODE is BLOCK end ID;
void package(){
  //printf("\n");
  lire();
  Test_Symbole(PACKAGE_TOKEN, "PACKAGE_TOKEN");
  Test_Symbole(BODY_TOKEN, "BODY_TOKEN");
  if(Sym_cour.CODE == ID_TOKEN){
      table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TPACKAGE); indexta++;
      table_symboles[indexta].typevar = ID;
      strcpy(ID_Package, Sym_Cour.NOM);
  }
  Test_Symbole(ID_TOKEN, "ID_TOKEN");
  Test_Symbole(WITH_TOKEN, "WITH_TOKEN");
  Test_Symbole(SPARKMODE_TOKEN, "SPARKMODE_TOKEN");
  Test_Symbole(IS_TOKEN, "IS_TOKEN");
  //printf("\n\n________________FIN_PACKAGE_LIGNE________________ \n");
  block();
  Test_Symbole(END_TOKEN, "END_TOKEN");
  if(strcmp(Sym_cour.NOM, ID_Package) == 0){
      Test_Symbole(ID_TOKEN, "ID_TOKEN");
  } else{
     printf("\n Semantic Error  😜😝😜 : %s in row %d %s\n", ID_Package, ligne, "Expected to end this package");
  }
  Test_Symbole(PV_TOKEN, "PV_TOKEN");
}


// BLOCK ::= DECLS  [ PROCEDURS | FUNCTIONS ]
void block(){
  //printf("Body of the package\n");
  DECLSPack();
  while(Sym_cour.CODE != END_TOKEN){
        if(Sym_cour.CODE == PROCEDURE_TOKEN){
              PROCEDURESP();
        } else if(Sym_cour.CODE == FUNCTION_TOKEN){
              Dec_function();
        }         
  }
}

// PROCEDURE ::= procedure ID { ARGUMENTS } is DECLS begin INSTS end ID;
void PROCEDURESP(){
    Test_Symbole(PROCEDURE_TOKEN,"PROCEDURE_TOKEN");
      if(Sym_cour.CODE == ID_TOKEN){
            if(isDeclared(Sym_cour.NOM) == false){
                  table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TPROC); indexta++;
                  table_symboles[indexta].typevar = ID;
            } else {
              print_sm_error(Sym_cour.NOM, ligne, "name of procedure is Already Declared");
              sm_error = true;
            }
            strcpy(ID_Proc, Sym_Cour.NOM);
     }
    Test_Symbole(ID_TOKEN, "ID_TOKEN");
    ARGUMENTS();
    Test_Symbole(IS_TOKEN, "IS_TOKEN");
    //printf("\n\n________________FIN_PROCEDURE_LIGNE________________ \n");
    DECLS();
    Test_Symbole(BEGIN_TOKEN, "BEGIN_TOKEN");
    while(Sym_cour.CODE != END_TOKEN){
      INSTS();
    }    
    Test_Symbole(END_TOKEN, "END_TOKEN");

    if(strcmp(Sym_cour.NOM, ID_Proc) == 0){
        Test_Symbole(ID_TOKEN, "ID_TOKEN");
    } else{
        printf("\n Semantic Error  😜😝😜 : %s in row %d %s\n", ID_Proc, ligne, "Expected to end this procedure");
    }
    Test_Symbole(PV_TOKEN, "PV_TOKEN");
}


void PROCEDURES(){
    Test_Symbole(PROCEDURE_TOKEN,"PROCEDURE_TOKEN");

      if(Sym_cour.CODE == ID_TOKEN){
            
            if(isDeclared(Sym_cour.NOM) == false){
                  table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TPROC); indexta++;
                  table_symboles[indexta].typevar = ID;
            } else {
              print_sm_error(Sym_cour.NOM, ligne, "name of procedure is Already Declared");
              sm_error = true;
            }

            strcpy(ID_ProcSec, Sym_Cour.NOM);                       
     }
    Test_Symbole(ID_TOKEN, "ID_TOKEN");
    ARGUMENTS();
    Test_Symbole(IS_TOKEN, "IS_TOKEN");
    //printf("\n\n________________FIN_PROCEDURE_LIGNE________________ \n");
    DECLS();
    Test_Symbole(BEGIN_TOKEN, "BEGIN_TOKEN");
    while(Sym_cour.CODE != END_TOKEN){
      INSTS();
    }    
    Test_Symbole(END_TOKEN, "END_TOKEN");

    if(strcmp(Sym_cour.NOM, ID_ProcSec) == 0){
        Test_Symbole(ID_TOKEN, "ID_TOKEN");
    } else{
        printf("\n Semantic Error  😜😝😜 : %s in row %d %s\n", ID_ProcSec, ligne, "Expected to end this procedure");
    }
    Test_Symbole(PV_TOKEN, "PV_TOKEN");
}


//  ARGUMENTS    ::=  (ID {,ID} : TYPEARG {; ID : TYPEARG } ) | epsilon
void ARGUMENTS(){
  printf("\n");
  switch (Sym_cour.CODE) {  
              case PO_TOKEN :  Test_Symbole(PO_TOKEN, "PO_TOKEN");
                                     if(Sym_cour.CODE == ID_TOKEN){
                                              if(isDeclaredArg(Sym_cour.NOM) == false) { table_symbolesArg[symbole_t_indexArg++] = new_idfArg(Sym_cour.NOM, TARGPROC); indexArg++; } 
                                              else { print_sm_error(Sym_cour.NOM, ligne, "procedure argument is Already Declared"); sm_error = true; }
                                    }
                               Test_Symbole(ID_TOKEN, "ID_TOKEN");
                               while(Sym_cour.CODE == VR_TOKEN){
                                    Test_Symbole(VR_TOKEN, "VR_TOKEN");
                                     if(Sym_cour.CODE == ID_TOKEN){
                                              if(isDeclaredArg(Sym_cour.NOM) == false) { table_symbolesArg[symbole_t_indexArg++] = new_idfArg(Sym_cour.NOM, TARGPROC); indexArg++; } 
                                              else { print_sm_error(Sym_cour.NOM, ligne, " procedure argument is Already Declared"); sm_error = true; }
                                    }
                                    Test_Symbole(ID_TOKEN, "ID_TOKEN");
                               }
                               Test_Symbole(TYPESYM_TOKEN, "TYPESYM_TOKEN"); 
                               TYPEARG();
                                while(Sym_cour.CODE == PV_TOKEN){
                                      Test_Symbole(PV_TOKEN,"PV_TOKEN");
                                       if(Sym_cour.CODE == ID_TOKEN){
                                              if( isDeclaredArg(Sym_cour.NOM) == false) { table_symbolesArg[symbole_t_indexArg++] = new_idfArg(Sym_cour.NOM, TARGPROC); indexArg++; } 
                                              else { print_sm_error(Sym_cour.NOM, ligne, "procedure argument is Already Declared"); sm_error = true; }
                                    }
                                      Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                      while(Sym_cour.CODE == VR_TOKEN){
                                            Test_Symbole(VR_TOKEN, "VR_TOKEN");
                                             if(Sym_cour.CODE == ID_TOKEN){
                                                          if(isDeclaredArg(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idfArg(Sym_cour.NOM, TARGPROC); indexArg++; } 
                                                          else { print_sm_error(Sym_cour.NOM, ligne, "procedure argument is Already Declared"); sm_error = true; }
                                             }
                                            Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                      }
                                      Test_Symbole(TYPESYM_TOKEN, "TYPESYM_TOKEN"); 
                                      TYPEARG();
                                }
                                Test_Symbole(PF_TOKEN, "PF_TOKEN");
                                break;

              case IS_TOKEN : break;  // epsilon
              default: printf("\n SYNTAX ERROR ________________PROCEDURE________________ \n");  exit(0); break;  
  }    
    //printf("\n\n________________FIN_ARGUMENTS________________ \n");  
}


// TYPEARG  ::=  Natural | Integer | Boolean | Float | INOUTTYPE 
void TYPEARG(){
  switch (Sym_cour.CODE) {  
               case NATURAL_TOKEN :  table_symbolesArg[indexArg].typevar = TNATURAL; Test_Symbole(NATURAL_TOKEN, "NATURAL_TOKEN"); break;
              case INTEGER_TOKEN : table_symbolesArg[indexArg].typevar = TINTEGER;  Test_Symbole(INTEGER_TOKEN, "INTEGER_TOKEN"); break; 
              case BOOLEAN_TOKEN : table_symbolesArg[indexArg].typevar = TBOOLEAN; Test_Symbole(BOOLEAN_TOKEN, "BOOLEAN_TOKEN"); break; 
              case FLOAT_TOKEN : table_symbolesArg[indexArg].typevar = TFLOAT;  Test_Symbole(FLOAT_TOKEN, "FLOAT_TOKEN"); break;
              case STRINGKEY_TOKEN : table_symbolesArg[indexArg].typevar = TSTRING;  Test_Symbole(STRINGKEY_TOKEN, "STRINGKEY_TOKEN"); break; 
              case POSITIVE_TOKEN : table_symbolesArg[indexArg].typevar = TPOSITIVE; Test_Symbole(POSITIVE_TOKEN, "POSITIVE_TOKEN"); break; 
              case CHARACTER_TOKEN : table_symbolesArg[indexArg].typevar = TCHARACTER; Test_Symbole( CHARACTER_TOKEN, "CHARACTER_TOKEN"); break;

              case IN_TOKEN :INOUTTYPE(); break;
              case OUT_TOKEN : INOUTTYPE(); break;

              default: printf("\n SYNTAX ERROR ________________ARGUMENT________________ \n");  exit(0); break;  
  }    
    //printf("\n\n________________FIN_TYPE_ARGUMENTS________________ \n");  
}

// INOUTTYPE ::=   in out TYPEARG |  in TYPEARG  |  out TYPEARG 
void INOUTTYPE(){
   switch (Sym_cour.CODE) {   
              case IN_TOKEN : Test_Symbole(IN_TOKEN, "IN_TOKEN"); 
                              if(Sym_cour.CODE == OUT_TOKEN){
                                  Test_Symbole(OUT_TOKEN, "OUT_TOKEN");
                                  TYPEARG();
                                  break;
                              }    
                              TYPEARG(); break;
              case OUT_TOKEN : Test_Symbole(OUT_TOKEN, "OUT_TOKEN"); TYPEARG(); break;

              default: printf("\n SYNTAX ERROR ________________ARGUMENT_IN_OUT________________ \n");  exit(0); break;  
  }    
    //printf("\n\n________________FIN_TYPE_IN_OUT________________ \n");  

}


// TYPEARGF  ::= Positive | Character | Stringkey | Natural | Integer | Boolean | Float | IN [ID | NATURAL | INTEGER | CHARACHTER | FLOAT | BOOLEAN | POSITIVE ] | OUT [ID | NATURAL | INTEGER | CHARACHTER | FLOAT | BOOLEAN | POSITIVE ] 
void TYPEARGF(){
  switch (Sym_cour.CODE) {  
              case NATURAL_TOKEN :  table_symbolesArg[indexArg].typevar = TNATURAL; Test_Symbole(NATURAL_TOKEN, "NATURAL_TOKEN"); break;
              case INTEGER_TOKEN : table_symbolesArg[indexArg].typevar = TINTEGER;  Test_Symbole(INTEGER_TOKEN, "INTEGER_TOKEN"); break; 
              case BOOLEAN_TOKEN : table_symbolesArg[indexArg].typevar = TBOOLEAN; Test_Symbole(BOOLEAN_TOKEN, "BOOLEAN_TOKEN"); break; 
              case FLOAT_TOKEN : table_symbolesArg[indexArg].typevar = TFLOAT;  Test_Symbole(FLOAT_TOKEN, "FLOAT_TOKEN"); break;
              case STRINGKEY_TOKEN : table_symbolesArg[indexArg].typevar = TSTRING;  Test_Symbole(STRINGKEY_TOKEN, "STRINGKEY_TOKEN"); break; 
              case POSITIVE_TOKEN : table_symbolesArg[indexArg].typevar = TPOSITIVE; Test_Symbole(POSITIVE_TOKEN, "POSITIVE_TOKEN"); break; 
              case CHARACTER_TOKEN : table_symbolesArg[indexArg].typevar = TCHARACTER; Test_Symbole( CHARACTER_TOKEN, "CHARACTER_TOKEN"); break;
              case IN_TOKEN : Test_Symbole(IN_TOKEN, "IN_TOKEN"); 
                    if(Sym_cour.CODE == ID_TOKEN) {
                          lire();
                    } else if(Sym_cour.CODE == INTEGER_TOKEN){
                      table_symbolesArg[indexArg].typevar = TINTEGER;
                          lire();
                    } else if (Sym_cour.CODE == NATURAL_TOKEN) {
                      table_symbolesArg[indexArg].typevar = TNATURAL;
                          lire();
                    }else if(Sym_cour.CODE == FLOAT_TOKEN){
                      table_symbolesArg[indexArg].typevar = TFLOAT;
                            lire();
                    }else if (Sym_cour.CODE == BOOLEAN_TOKEN){
                      table_symbolesArg[indexArg].typevar = TBOOLEAN;
                          lire();
                    } else if (Sym_cour.CODE == POSITIVE_TOKEN){
                      table_symbolesArg[indexArg].typevar = TPOSITIVE;
                            lire();
                    } else if (Sym_cour.CODE == STRINGKEY_TOKEN) {
                      table_symbolesArg[indexArg].typevar = TSTRING;
                          lire();
                    } else if (Sym_cour.CODE == CHARACTER_TOKEN ){
                      table_symbolesArg[indexArg].typevar = TCHARACTER;
                        lire();
                    } else {
                         printf("\n SYNTAX ERROR ________________TYPE_ARG_IN_______________ \n"); exit(0);
                    } 
                              break;
              default: printf("\n SYNTAX ERROR ________________ARGUMENT________________ \n");  exit(0); break;  
  }    
    //printf("\n\n________________FIN_TYPE_ARGUMENTS________________ \n");  
}

// DECLS ::=  PROCEDURES |  ID {, ID} : DECLSIMPLE | type DECLSTYPE | epsilon
void DECLS(){
  while(Sym_cour.CODE != FUNCTION_TOKEN && Sym_cour.CODE != END_TOKEN && Sym_cour.CODE != BEGIN_TOKEN){
     switch (Sym_cour.CODE) {   
              case ID_TOKEN :  if(Sym_cour.CODE == ID_TOKEN){
                                              if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLPROC); indexta++;} 
                                              else { print_sm_error(Sym_cour.NOM, ligne, " in procedure declaration is Already Declared"); sm_error = true; }
                                }
                                strcpy(idcont, Sym_cour.NOM); 
                              Test_Symbole(ID_TOKEN, "ID_TOKEN");

                                while(Sym_cour.CODE == VR_TOKEN){
                                    Test_Symbole(VR_TOKEN, "VR_TOKEN");
                                          if(Sym_cour.CODE == ID_TOKEN){
                                                    if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLPROC); indexta++;} 
                                                    else { print_sm_error(Sym_cour.NOM, ligne, "in procedure declaration is Already Declared"); sm_error = true; }
                                      }
                                      strcpy(idcont, Sym_cour.NOM);
                                       Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                }
                                DECLSIMPLE(); break;

              case TYPE_TOKEN : Test_Symbole(TYPE_TOKEN, "TYPE_TOKEN"); DECLSTYPE(); break;
              case PROCEDURE_TOKEN : PROCEDURES();  break; // epsilon
              case FUNCTION_TOKEN : break;  // epsilon
              default: printf("\n SYNTAX ERROR ________________DECLS________________ \n");  exit(0); break;  
      }
  }
    //printf("\n\n________________FIN_DECLS________________ \n");  
}


// DECLSPack ::=       FUNCTIONS  | ID DECLSIMPLE  | type DECLSTYPE | epsilon
void DECLSPack(){
  while(Sym_cour.CODE != PROCEDURE_TOKEN && Sym_cour.CODE != END_TOKEN && Sym_cour.CODE != BEGIN_TOKEN){
     switch (Sym_cour.CODE) {   
              case ID_TOKEN :  if(Sym_cour.CODE == ID_TOKEN){
                                              if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLPACK); indexta++; } 
                                              else { print_sm_error(Sym_cour.NOM, ligne, " in package declaration is  Already Declared"); sm_error = true; }
                                } 
                                strcpy(idcont, Sym_cour.NOM); 
                              Test_Symbole(ID_TOKEN, "ID_TOKEN");  
                                  while(Sym_cour.CODE == VR_TOKEN){
                                    Test_Symbole(VR_TOKEN, "VR_TOKEN");
                                          if(Sym_cour.CODE == ID_TOKEN){
                                                    if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLPACK); indexta++;} 
                                                    else { print_sm_error(Sym_cour.NOM, ligne, " in package declaration is Already Declared"); sm_error = true; }
                                      }
                                      strcpy(idcont, Sym_cour.NOM);
                                       Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                }
                              DECLSIMPLE(); break;
              case TYPE_TOKEN : Test_Symbole(TYPE_TOKEN, "TYPE_TOKEN"); DECLSTYPEP(); break;           
              case FUNCTION_TOKEN :  Dec_function(); break;  // epsilon
              default: printf("\n SYNTAX ERROR ________________DECLSPack________________ \n");  exit(0); break;  
      }
  }
    //printf("\n\n________________FIN_DECLS________________ \n");  
}

void  DECLSF(){
   while(Sym_cour.CODE != PROCEDURE_TOKEN && Sym_cour.CODE != END_TOKEN && Sym_cour.CODE != BEGIN_TOKEN){
     switch (Sym_cour.CODE) {   
              case ID_TOKEN :  if(Sym_cour.CODE == ID_TOKEN){
                                              if(isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLFUNC); indexta++; } 
                                              else { print_sm_error(Sym_cour.NOM, ligne, " in function declaration is  Already Declared"); sm_error = true; }
                                }
                                strcpy(idcont, Sym_cour.NOM);  
                              Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
                                  while(Sym_cour.CODE == VR_TOKEN){
                                    Test_Symbole(VR_TOKEN, "VR_TOKEN");
                                          if(Sym_cour.CODE == ID_TOKEN){
                                                    if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLFUNC); indexta++;} 
                                                    else { print_sm_error(Sym_cour.NOM, ligne, " in function declaration is Already Declared"); sm_error = true; }
                                      }
                                      strcpy(idcont, Sym_cour.NOM);
                                       Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                }
                               DECLSIMPLE(); break;
              case TYPE_TOKEN : Test_Symbole(TYPE_TOKEN, "TYPE_TOKEN"); DECLSTYPEF(); break;           
              case FUNCTION_TOKEN :  Dec_function(); break;  // epsilon
              default: printf("\n SYNTAX ERROR ________________DECLS_F_______________ \n");  exit(0); break;  
      }
  }
    //printf("\n\n________________FIN_DECLS________________ \n");  
}

// DECLSIMPLE ::=  [ ID | Natural ( := AffecN | epsilon) | Integer ( :=  AffecInt | epsilon) | Boolean  ( := AffecB | epsilon) | Float ( := AffecF  | epsilon) |  Constant CONSTANTFUNC | Character ( := AffecCh  | epsilon) |  String ( := AffecSt | epsilon) | Positive ( :=  AffecN | epsilon) ]  
void DECLSIMPLE(){
  Test_Symbole(TYPESYM_TOKEN, "TYPESYM_TOKEN");
  switch (Sym_cour.CODE) {   
              case NATURAL_TOKEN :  table_symboles[indexta].typevar = TNATURAL;
                                    Test_Symbole(NATURAL_TOKEN, "NATURAL_TOKEN"); 
                                  if(Sym_cour.CODE == AFF_TOKEN){
                                      Test_Symbole(AFF_TOKEN, "AFF_TOKEN");
                                      AffecN();
                                  } 
                                   Test_Symbole(PV_TOKEN, "PV_TOKEN");   
                                   break;

              case INTEGER_TOKEN : table_symboles[indexta].typevar = TINTEGER; Test_Symbole(INTEGER_TOKEN, "INTEGER_TOKEN");
                                   if(Sym_cour.CODE == AFF_TOKEN){
                                      Test_Symbole(AFF_TOKEN, "AFF_TOKEN");
                                      AffecInt();
                                   }  
                                   Test_Symbole(PV_TOKEN, "PV_TOKEN");   
                                   break; 

              case BOOLEAN_TOKEN : table_symboles[indexta].typevar = TBOOLEAN; Test_Symbole(BOOLEAN_TOKEN, "BOOLEAN_TOKEN"); 
                                  if(Sym_cour.CODE == AFF_TOKEN){
                                      Test_Symbole(AFF_TOKEN, "AFF_TOKEN");
                                      AffecB();
                                   }
                                   Test_Symbole(PV_TOKEN, "PV_TOKEN");   
                                   break;

              case CHARACTER_TOKEN : table_symboles[indexta].typevar = TCHARACTER; Test_Symbole(CHARACTER_TOKEN, "CHARACTER_TOKEN");
                                    if(Sym_cour.CODE == AFF_TOKEN){
                                      Test_Symbole(AFF_TOKEN, "AFF_TOKEN");
                                      AffecCh();
                                     }
                                     Test_Symbole(PV_TOKEN, "PV_TOKEN");  
                                     break; 

              case STRINGKEY_TOKEN : table_symboles[indexta].typevar = TSTRING; Test_Symbole(STRINGKEY_TOKEN, "STRINGKEY_TOKEN");
                                  if(Sym_cour.CODE == AFF_TOKEN){
                                      Test_Symbole(AFF_TOKEN, "AFF_TOKEN");
                                      AffecSt();
                                   }
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN"); 
                                  break; 

              case POSITIVE_TOKEN : table_symboles[indexta].typevar = TPOSITIVE; Test_Symbole(POSITIVE_TOKEN, "POSITIVE_TOKEN"); 
                                    if(Sym_cour.CODE == AFF_TOKEN){
                                      Test_Symbole(AFF_TOKEN, "AFF_TOKEN");
                                      AffecN();
                                   }
                                    Test_Symbole(PV_TOKEN, "PV_TOKEN"); 
                                    break; 

              case ID_TOKEN :  if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, " in declaration undeclared first use in this function"); sm_error = true; }  }
                              Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
                              Test_Symbole(PV_TOKEN, "PV_TOKEN");   
                              break;  

              case FLOAT_TOKEN : table_symboles[indexta].typevar = TFLOAT;  Test_Symbole(FLOAT_TOKEN, "FLOAT_TOKEN"); 
                                  if(Sym_cour.CODE == AFF_TOKEN){
                                      Test_Symbole(AFF_TOKEN, "AFF_TOKEN");
                                      AffecF();
                                   } 
                                 Test_Symbole(PV_TOKEN, "PV_TOKEN");   
                                 break; 

              case CONSTANT_TOKEN :  Test_Symbole(CONSTANT_TOKEN, "CONSTANT_TOKEN");                                                                
                                    table_symboles[symbole_t_index++] = new_idf(idcont, TCONST);
                                    indexta++;
                                   CONSTANTFUNC();                                  
                                    break;
              default: printf("\n SYNTAX ERROR ________________DECLSSIMPLE________________ \n");  exit(0); break;  
  }    
    //printf("\n\n________________FIN_TYPE_IN_OUT________________ \n");  

}

// CONSTANTFUNC ::= Natural :=  AffecN | Integer :=  AffecInt| Boolean :=  AffecB| Float :=  AffecF
//   a completer  Character |  String | Positive
void CONSTANTFUNC(){
    switch (Sym_cour.CODE) {   
              case NATURAL_TOKEN : table_symboles[indexta].typevar = TNATURAL;
                                   Test_Symbole(NATURAL_TOKEN, "NATURAL_TOKEN");
                                   Test_Symbole(AFF_TOKEN,"AFF_TOKEN"); 
                                   AffecN();
                                   Test_Symbole(PV_TOKEN, "PV_TOKEN"); 
                                   break;

              case INTEGER_TOKEN : table_symboles[indexta].typevar = TINTEGER; 
                                   Test_Symbole(INTEGER_TOKEN, "INTEGER_TOKEN"); 
                                   Test_Symbole(AFF_TOKEN,"AFF_TOKEN"); 
                                   AffecInt();
                                   Test_Symbole(PV_TOKEN, "PV_TOKEN"); 
                                   break; 

              case BOOLEAN_TOKEN : table_symboles[indexta].typevar = TBOOLEAN;
                                   Test_Symbole(BOOLEAN_TOKEN, "BOOLEAN_TOKEN"); 
                                   Test_Symbole(AFF_TOKEN,"AFF_TOKEN"); 
                                   AffecB(); 
                                   Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                   break;

              case FLOAT_TOKEN : table_symboles[indexta].typevar = TFLOAT;
                                 Test_Symbole(FLOAT_TOKEN, "FLOAT_TOKEN"); 
                                 Test_Symbole(AFF_TOKEN,"AFF_TOKEN"); 
                                 AffecF(); 
                                 Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                 break; 

              case CHARACTER_TOKEN : table_symboles[indexta].typevar = TCHARACTER;
                                     Test_Symbole(CHARACTER_TOKEN, "CHARACTER_TOKEN"); 
                                     Test_Symbole(AFF_TOKEN,"AFF_TOKEN"); 
                                     AffecCh(); 
                                     Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                     break; 

              case STRING_TOKEN : table_symboles[indexta].typevar = TSTRING;
                                  Test_Symbole(STRINGKEY_TOKEN, "STRINGKEY_TOKEN"); 
                                  Test_Symbole(AFF_TOKEN,"AFF_TOKEN"); 
                                  AffecSt(); 
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break; 

              case POSITIVE_TOKEN :  table_symboles[indexta].typevar = TPOSITIVE;
                                    Test_Symbole(POSITIVE_TOKEN, "POSITIVE_TOKEN"); 
                                    Test_Symbole(AFF_TOKEN,"AFF_TOKEN"); 
                                    AffecN(); 
                                    Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                    break;  

              default: printf("\n SYNTAX ERROR ________________CONSTANT________________ \n");  exit(0); break;  
  }    
}

// AffecSt ::=    STRING 
void AffecSt(){
  Test_Symbole(STRING_TOKEN,"STRING_TOKEN");
}

// AffecCh ::=   CHAR 
void AffecCh(){
  Test_Symbole(CHAR_TOKEN,"CHAR_TOKEN");
}

// AffecN ::=   [INT  | ID]
void AffecN(){
 switch (Sym_cour.CODE) {   
              case INT_TOKEN :  table_symboles[indexta].value = atoi(Sym_cour.NOM);
                                Test_Symbole(INT_TOKEN, "INT_TOKEN");                             
                                break;

              case ID_TOKEN :   if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, " in assignment undeclared first use in this function"); sm_error = true; }  }
                                Test_Symbole(ID_TOKEN, "ID_TOKEN");                                
                                break; 

              default: printf("\n SYNTAX ERROR ________________AFFECN________________ \n"); exit(0); break;  
  }       
}

// AffecF ::=  [INT  | ID | REALINT]
void AffecF(){
    switch (Sym_cour.CODE) {   
                  case REALINT_TOKEN :  table_symboles[indexta].value = atoi(Sym_cour.NOM);
                                        Test_Symbole(REALINT_TOKEN, "REALINT_TOKEN");                             
                                        break;

                  case ID_TOKEN :    if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "in assignment undeclared first use in this function"); sm_error = true; }  }
                                    Test_Symbole(ID_TOKEN, "ID_TOKEN");                                
                                    break; 

                  case INT_TOKEN :  table_symboles[indexta].value = atoi(Sym_cour.NOM);
                                    Test_Symbole(INT_TOKEN, "NATURAL_TOKEN");                             
                                    break;

                  default: printf("\n SYNTAX ERROR ________________AFFECF________________ \n");  exit(0); break;  
      }
}

// AffecInt ::=  [INT  | ID]
void AffecInt(){
    switch (Sym_cour.CODE) {   
                  case INT_TOKEN :  
                                    table_symboles[indexta].value = atoi(Sym_cour.NOM);
                                    Test_Symbole(INT_TOKEN, "NATURAL_TOKEN");                           
                                    break;

                  case ID_TOKEN :    if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "in assignment undeclared first use in this function"); sm_error = true; }  }
                                    Test_Symbole(ID_TOKEN, "ID_TOKEN");                                                                   
                                    break; 

                  default: printf("\n SYNTAX ERROR ________________AFFECINT________________ \n");  exit(0); break;  
      }
}


//  AffecB ::=  [True | False  | ID]
void AffecB(){
    switch (Sym_cour.CODE) {   
                  case TRUE_TOKEN :  Test_Symbole(TRUE_TOKEN, "TRUE_TOKEN");                             
                                    break;

                  case FALSE_TOKEN :   Test_Symbole(FALSE_TOKEN, "FALSE_TOKEN");                                
                                    break; 

                  case ID_TOKEN :    if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "in assignment undeclared first use in this function"); sm_error = true; }  }
                                    Test_Symbole(ID_TOKEN, "ID_TOKEN");                               
                                    break;

                  default: printf("\n SYNTAX ERROR ________________AFFECB________________ \n"); exit(0);  break;  
      }

}

// DECLSTYPE ::= ID 'is' ['range' RANGEFUNC | 'array' ARRAYFUNC | 'record' RECORDFUNC | '('  ENUMFUNC | 'new' ['Integer' | 'Float' | 'Positive' | 'Natural' | 'Stringkey' | 'Character' | 'Boolean' ] ]
void DECLSTYPE(){
  if(Sym_cour.CODE == ID_TOKEN){
        if(isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLPROC); indexta++;} 
        else { print_sm_error(Sym_cour.NOM, ligne, "in procedure declaration is Already Declared"); sm_error = true; }
  }
  Test_Symbole(ID_TOKEN, "ID_TOKEN");
  Test_Symbole(IS_TOKEN, "IS_TOKEN"); 
  switch (Sym_cour.CODE){
          case RANGE_TOKEN : table_symboles[indexta].typevar = TRANGE; Test_Symbole(RANGE_TOKEN, "RANGE_TOKEN"); 
                              RANGEFUNC();
                              break;

          case ARRAY_TOKEN : table_symboles[indexta].typevar = TARRAY; Test_Symbole(ARRAY_TOKEN, "ARRAY_TOKEN"); 
                              ARRAYFUNC();
                              break;

          case RECORD_TOKEN : Test_Symbole(RECORD_TOKEN, "RECORD_TOKEN"); 
                              RECORDFUNC();
                              break;

          case PO_TOKEN : Test_Symbole(PO_TOKEN, "PO_TOKEN"); 
                              ENUMFUNC();
                              break;

          case NEW_TOKEN : Test_Symbole(NEW_TOKEN, "NEW_TOKEN");
                           
                            if(Sym_cour.CODE == ID_TOKEN) {
                          
                                if(isDeclared(Sym_cour.NOM) == false) {
                               print_sm_error(Sym_cour.NOM, ligne, " in new undeclared first use in this function"); sm_error = true; }

                                  Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            } else if(Sym_cour.CODE == INTEGER_TOKEN){
                                  table_symboles[indexta].typevar = TINTEGER;
                                  Test_Symbole(INTEGER_TOKEN, "INTEGER_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            } else if (Sym_cour.CODE == NATURAL_TOKEN) {
                                  table_symboles[indexta].typevar = TNATURAL;
                                  Test_Symbole(NATURAL_TOKEN, "NATURAL_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            }else if(Sym_cour.CODE == FLOAT_TOKEN){
                                    table_symboles[indexta].typevar = TFLOAT;
                                    Test_Symbole(FLOAT_TOKEN, "FLOAT_TOKEN");
                                    Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                    break;

                            }else if (Sym_cour.CODE == BOOLEAN_TOKEN){
                                  table_symboles[indexta].typevar = TBOOLEAN;
                                   Test_Symbole(BOOLEAN_TOKEN, "BOOLEAN_TOKEN");
                                   Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                   break;

                            } else if (Sym_cour.CODE == POSITIVE_TOKEN){
                                    table_symboles[indexta].typevar = TPOSITIVE;
                                    Test_Symbole(POSITIVE_TOKEN, "POSITIVE_TOKEN");
                                    Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                    break;

                            } else if (Sym_cour.CODE == STRINGKEY_TOKEN) {
                                  table_symboles[indexta].typevar = TSTRING;
                                  Test_Symbole(STRINGKEY_TOKEN, "STRINGKEY_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            } else if (Sym_cour.CODE == CHARACTER_TOKEN ){
                                  table_symboles[indexta].typevar = TCHARACTER;
                                  Test_Symbole(CHARACTER_TOKEN, "CHARACTER_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                           } else if(Sym_cour.CODE == RECORD_TOKEN){

                                    Test_Symbole(RECORD_TOKEN, "RECORD_TOKEN"); 
                                    RECORDFUNC();
                                    break;

                            }else if(Sym_cour.CODE == ARRAY_TOKEN){
                              table_symboles[indexta].typevar = TARRAY;
                                    Test_Symbole(ARRAY_TOKEN, "ARRAY_TOKEN"); 
                                    ARRAYFUNC();
                                    break;

                            } else if(Sym_cour.CODE == RANGE_TOKEN){
                              table_symboles[indexta].typevar = TRANGE;
                                    Test_Symbole(RANGE_TOKEN, "RANGE_TOKEN"); 
                                    RANGEFUNC();
                                    break;

                            } else if(Sym_cour.CODE == PO_TOKEN){

                              Test_Symbole(PO_TOKEN, "PO_TOKEN"); 
                              ENUMFUNC();
                              break;

                            } else {
                                printf("\n SYNTAX ERROR ________________NEW_TYPE_______________ \n"); exit(0);
                            }


                            Test_Symbole(PV_TOKEN, "PV_TOKEN");
                            break;

          default : printf("\n SYNTAX ERROR ________________DECLTYPE_PROC_______________ \n"); exit(0);  break;  
    }
}

void DECLSTYPEP(){
    if(Sym_cour.CODE == ID_TOKEN){
        if(isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLPACK); indexta++; } 
        else { print_sm_error(Sym_cour.NOM, ligne, "in package declaration is Already Declared"); sm_error = true; }
  }
  Test_Symbole(ID_TOKEN, "ID_TOKEN");
  Test_Symbole(IS_TOKEN, "IS_TOKEN"); 
  switch (Sym_cour.CODE){
          case RANGE_TOKEN : table_symboles[indexta].typevar = TRANGE; Test_Symbole(RANGE_TOKEN, "RANGE_TOKEN"); 
                              RANGEFUNC();
                              break;

          case ARRAY_TOKEN : table_symboles[indexta].typevar = TARRAY; Test_Symbole(ARRAY_TOKEN, "ARRAY_TOKEN"); 
                              ARRAYFUNC();
                              break;

          case RECORD_TOKEN : Test_Symbole(RECORD_TOKEN, "RECORD_TOKEN"); 
                              RECORDFUNCPack();
                              break;

          case PO_TOKEN : Test_Symbole(PO_TOKEN, "PO_TOKEN"); 
                              ENUMFUNC();
                              break;
          case NEW_TOKEN : Test_Symbole(NEW_TOKEN, "NEW_TOKEN");
                           if(Sym_cour.CODE == ID_TOKEN) {
                            if(isDeclared(Sym_cour.NOM) == false) {
                               print_sm_error(Sym_cour.NOM, ligne, " in new undeclared first use in this function"); sm_error = true; }
                                  Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            } else if(Sym_cour.CODE == INTEGER_TOKEN){
                                  table_symboles[indexta].typevar = TINTEGER;
                                  Test_Symbole(INTEGER_TOKEN, "INTEGER_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            } else if (Sym_cour.CODE == NATURAL_TOKEN) {
                                  table_symboles[indexta].typevar = TNATURAL;
                                  Test_Symbole(NATURAL_TOKEN, "NATURAL_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            }else if(Sym_cour.CODE == FLOAT_TOKEN){
                                    table_symboles[indexta].typevar = TFLOAT;
                                    Test_Symbole(FLOAT_TOKEN, "FLOAT_TOKEN");
                                    Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                    break;

                            }else if (Sym_cour.CODE == BOOLEAN_TOKEN){
                                  table_symboles[indexta].typevar = TBOOLEAN;
                                   Test_Symbole(BOOLEAN_TOKEN, "BOOLEAN_TOKEN");
                                   Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                   break;

                            } else if (Sym_cour.CODE == POSITIVE_TOKEN){
                                    table_symboles[indexta].typevar = TPOSITIVE;
                                    Test_Symbole(POSITIVE_TOKEN, "POSITIVE_TOKEN");
                                    Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                    break;

                            } else if (Sym_cour.CODE == STRINGKEY_TOKEN) {
                                  table_symboles[indexta].typevar = TSTRING;
                                  Test_Symbole(STRINGKEY_TOKEN, "STRINGKEY_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            } else if (Sym_cour.CODE == CHARACTER_TOKEN ){
                                  table_symboles[indexta].typevar = TCHARACTER;
                                  Test_Symbole(CHARACTER_TOKEN, "CHARACTER_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;
                                //printf("  %s", Sym_cour.NOM);
                            }else if(Sym_cour.CODE == RECORD_TOKEN){
                                    Test_Symbole(RECORD_TOKEN, "RECORD_TOKEN"); 
                                    RECORDFUNC();
                                    break;

                            }else if(Sym_cour.CODE == ARRAY_TOKEN){
                              table_symboles[indexta].typevar = TARRAY;
                                    Test_Symbole(ARRAY_TOKEN, "ARRAY_TOKEN"); 
                                    ARRAYFUNC();
                                    break;

                            } else if(Sym_cour.CODE == RANGE_TOKEN){
                              table_symboles[indexta].typevar = TRANGE;
                                    Test_Symbole(RANGE_TOKEN, "RANGE_TOKEN"); 
                                    RANGEFUNC();
                                    break;

                            } else if(Sym_cour.CODE == PO_TOKEN){

                              Test_Symbole(PO_TOKEN, "PO_TOKEN"); 
                              ENUMFUNC();
                              break;

                            } else {
                                printf("\n SYNTAX ERROR ________________NEW_TYPE_______________ \n"); exit(0);
                            }
                            Test_Symbole(PV_TOKEN, "PV_TOKEN");
                            break;

          default : printf("\n SYNTAX ERROR ________________DECLTYPE_PACK_______________ \n"); exit(0);  break;  
    }

}

void DECLSTYPEF(){
      if(Sym_cour.CODE == ID_TOKEN){
        if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLFUNC); indexta++;} 
        else { print_sm_error(Sym_cour.NOM, ligne, "in function declaration is  Already Declared"); sm_error = true; }
  }
  Test_Symbole(ID_TOKEN, "ID_TOKEN");
  Test_Symbole(IS_TOKEN, "IS_TOKEN"); 
  switch (Sym_cour.CODE){
          case RANGE_TOKEN : table_symboles[indexta].typevar = TRANGE;
                              Test_Symbole(RANGE_TOKEN, "RANGE_TOKEN"); 
                              RANGEFUNC();
                              break;

          case ARRAY_TOKEN : table_symboles[indexta].typevar = TARRAY; Test_Symbole(ARRAY_TOKEN, "ARRAY_TOKEN"); 
                              ARRAYFUNC();
                              break;

          case RECORD_TOKEN : Test_Symbole(RECORD_TOKEN, "RECORD_TOKEN"); 
                              RECORDFUNCF();
                              break;

          case PO_TOKEN : Test_Symbole(PO_TOKEN, "PO_TOKEN"); 
                              ENUMFUNC();
                              break;

          case NEW_TOKEN : Test_Symbole(NEW_TOKEN, "NEW_TOKEN");
                            if(Sym_cour.CODE == ID_TOKEN) {
                              if(isDeclared(Sym_cour.NOM) == false) {
                               print_sm_error(Sym_cour.NOM, ligne, " in new undeclared first use in this function"); sm_error = true; }
                                  Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            } else if(Sym_cour.CODE == INTEGER_TOKEN){
                                  table_symboles[indexta].typevar = TINTEGER;
                                  Test_Symbole(INTEGER_TOKEN, "INTEGER_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            } else if (Sym_cour.CODE == NATURAL_TOKEN) {
                                  table_symboles[indexta].typevar = TNATURAL;
                                  Test_Symbole(NATURAL_TOKEN, "NATURAL_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            }else if(Sym_cour.CODE == FLOAT_TOKEN){
                                    table_symboles[indexta].typevar = TFLOAT;
                                    Test_Symbole(FLOAT_TOKEN, "FLOAT_TOKEN");
                                    Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                    break;

                            }else if (Sym_cour.CODE == BOOLEAN_TOKEN){
                                  table_symboles[indexta].typevar = TBOOLEAN;
                                   Test_Symbole(BOOLEAN_TOKEN, "BOOLEAN_TOKEN");
                                   Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                   break;

                            } else if (Sym_cour.CODE == POSITIVE_TOKEN){
                                    table_symboles[indexta].typevar = TPOSITIVE;
                                    Test_Symbole(POSITIVE_TOKEN, "POSITIVE_TOKEN");
                                    Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                    break;

                            } else if (Sym_cour.CODE == STRINGKEY_TOKEN) {
                                  table_symboles[indexta].typevar = TSTRING;
                                  Test_Symbole(STRINGKEY_TOKEN, "STRINGKEY_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;

                            } else if (Sym_cour.CODE == CHARACTER_TOKEN ){
                                  table_symboles[indexta].typevar = TCHARACTER;
                                  Test_Symbole(CHARACTER_TOKEN, "CHARACTER_TOKEN");
                                  Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                  break;
                            }else if(Sym_cour.CODE == RECORD_TOKEN){

                                    Test_Symbole(RECORD_TOKEN, "RECORD_TOKEN"); 
                                    RECORDFUNC();
                                    break;

                            }else if(Sym_cour.CODE == ARRAY_TOKEN){
                              table_symboles[indexta].typevar = TARRAY;
                                    Test_Symbole(ARRAY_TOKEN, "ARRAY_TOKEN"); 
                                    ARRAYFUNC();
                                    break;

                            } else if(Sym_cour.CODE == RANGE_TOKEN){
                              table_symboles[indexta].typevar = TRANGE;
                                    Test_Symbole(RANGE_TOKEN, "RANGE_TOKEN"); 
                                    RANGEFUNC();
                                    break;

                            } else if(Sym_cour.CODE == PO_TOKEN){

                              Test_Symbole(PO_TOKEN, "PO_TOKEN"); 
                              ENUMFUNC();
                              break;

                            } else {
                                printf("\n SYNTAX ERROR ________________NEW_TYPE_______________ \n"); exit(0);
                            }
                            Test_Symbole(PV_TOKEN, "PV_TOKEN");
                            break;

          default : printf("\n SYNTAX ERROR ________________DECLTYPE_FUNC_______________ \n"); exit(0);  break;  
    }
}

// RANGEFUNC ::= (INT | ID) .. (INT | ID ) ;
void RANGEFUNC(){
    switch (Sym_cour.CODE){
          case ID_TOKEN :  if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "in range/array undeclared first use in this function"); sm_error = true; }  }
                          Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
                          Test_Symbole(FROMTO_TOKEN, "FROMTO_TOKEN");
                          switch (Sym_cour.CODE){
                                        case ID_TOKEN :  if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "in range/array undeclared first use in this function"); sm_error = true; }  }
                                                        Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
                                                        Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                                            break;

                                        case INT_TOKEN : Test_Symbole(INT_TOKEN, "INT_TOKEN"); 
                                                            Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                                            break;

                                        default: printf("\n SYNTAX ERROR ________________RANGEFUNC2________________ \n"); exit(0);  break;  
                                  }
                          break;

          case INT_TOKEN : 
                          a = atoi(Sym_cour.NOM);
                          Test_Symbole(INT_TOKEN, "INT_TOKEN"); 
                          Test_Symbole(FROMTO_TOKEN, "FROMTO_TOKEN");
                          switch (Sym_cour.CODE){
                                        case ID_TOKEN :  if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, " in range/array undeclared first use in this function"); sm_error = true; }  }
                                                        Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
                                                        Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                                        break;

                                        case INT_TOKEN : b = atoi(Sym_cour.NOM);
                                                            Test_Symbole(INT_TOKEN, "INT_TOKEN"); 
                                                            if(a > b){
                                                                print_sm_error("!!", ligne, " must be greater than previous integer "); sm_error = true;
                                                            } 
                                                         Test_Symbole(PV_TOKEN, "PV_TOKEN");
                                                         break;

                                        default: printf("\n SYNTAX ERROR ________________RANGEFUNC2________________ \n"); exit(0);  break;  
                                  }
                          break;
          default : printf("\n SYNTAX ERROR ________________RANGEFUNC1________________ \n"); exit(0);  break;  
    }
}

// ARRAYFUNC ::= '('  (ID | INT..INT | ID range <>)  ')'  of  (ID | Integer | Natural)  ;
void ARRAYFUNC(){
  Test_Symbole(PO_TOKEN, "PO_TOKEN");
  //switch case
    switch (Sym_cour.CODE){
          case ID_TOKEN :  if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "in array type undeclared first use in this function"); sm_error = true; }  }
                          Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
                          if(Sym_Cour.CODE == RANGE_TOKEN){
                                Test_Symbole(RANGE_TOKEN, "RANGE_TOKEN");
                                Test_Symbole(RANGEREDECLARE_TOKEN, "RANGEREDECLARE_TOKEN");
                          }      
                          break;

          case INT_TOKEN : a = atoi(Sym_cour.NOM);
                            Test_Symbole(INT_TOKEN, "INT_TOKEN"); 
                           Test_Symbole(FROMTO_TOKEN, "FROMTO_TOKEN");
                            b = atoi(Sym_cour.NOM);        
                            Test_Symbole(INT_TOKEN, "INT_TOKEN");                                                    
                            if(a > b){ print_sm_error("!!", ligne, " must be greater than previous integer "); sm_error = true;} 
                           break;
         default: printf("\n SYNTAX ERROR ________________ARRAYFUNC1________________ \n"); exit(0);  break;  
    }
  Test_Symbole(PF_TOKEN, "PF_TOKEN");
    Test_Symbole(OF_TOKEN, "OF_TOKEN");
                          if(Sym_cour.CODE == ID_TOKEN) {
if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "in array type undeclared first use in this function"); sm_error = true; }  
                                 
                                  Test_Symbole(ID_TOKEN, "ID_TOKEN");
                             
                            } else if(Sym_cour.CODE == INTEGER_TOKEN){
                                  table_symboles[indexta].typevar = TINTEGER;
                                  Test_Symbole(INTEGER_TOKEN, "INTEGER_TOKEN");                              

                            } else if (Sym_cour.CODE == NATURAL_TOKEN) {
                                  table_symboles[indexta].typevar = TNATURAL;
                                  Test_Symbole(NATURAL_TOKEN, "NATURAL_TOKEN");                        

                            }else if(Sym_cour.CODE == FLOAT_TOKEN){
                                    table_symboles[indexta].typevar = TFLOAT;
                                    Test_Symbole(FLOAT_TOKEN, "FLOAT_TOKEN");
                             
                            }else if (Sym_cour.CODE == BOOLEAN_TOKEN){
                                  table_symboles[indexta].typevar = TBOOLEAN;
                                   Test_Symbole(BOOLEAN_TOKEN, "BOOLEAN_TOKEN");

                            } else if (Sym_cour.CODE == POSITIVE_TOKEN){
                                    table_symboles[indexta].typevar = TPOSITIVE;
                                    Test_Symbole(POSITIVE_TOKEN, "POSITIVE_TOKEN");

                            } else if (Sym_cour.CODE == STRINGKEY_TOKEN) {
                                  table_symboles[indexta].typevar = TSTRING;
                                  Test_Symbole(STRINGKEY_TOKEN, "STRINGKEY_TOKEN");  

                            } else if (Sym_cour.CODE == CHARACTER_TOKEN ){
                                  table_symboles[indexta].typevar = TCHARACTER;
                                  Test_Symbole(CHARACTER_TOKEN, "CHARACTER_TOKEN");

                          } else {
                                printf("\n SYNTAX ERROR ________________ARRAYFUNC2________________ \n"); exit(0);
                          }
  Test_Symbole(PV_TOKEN, "PV_TOKEN");
}


//  RECORDFUNC :: { DECLSRECORD } end record ;
void RECORDFUNC(){
    while(Sym_cour.CODE == ID_TOKEN){
        DECLSRECORD();
    }
    Test_Symbole(END_TOKEN, "END_TOKEN");
    Test_Symbole(RECORD_TOKEN, "RECORD_TOKEN");
    Test_Symbole(PV_TOKEN, "PV_TOKEN");
}

void RECORDFUNCPack(){
  while(Sym_cour.CODE == ID_TOKEN){
        DECLSRECORDPack();
    }
    Test_Symbole(END_TOKEN, "END_TOKEN");
    Test_Symbole(RECORD_TOKEN, "RECORD_TOKEN");
    Test_Symbole(PV_TOKEN, "PV_TOKEN");

}


void RECORDFUNCF(){
      while(Sym_cour.CODE == ID_TOKEN){
        DECLSRECORDF();
    }
    Test_Symbole(END_TOKEN, "END_TOKEN");
    Test_Symbole(RECORD_TOKEN, "RECORD_TOKEN");
    Test_Symbole(PV_TOKEN, "PV_TOKEN");

}

// DECLSRECORD ::=  ID { ,ID } : (ID | Boolean | Float | Integer | Natural  | Character |  String | Positive ) ;
void DECLSRECORD(){
// declaration
  if(Sym_cour.CODE == ID_TOKEN){
        if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLRECORDPROC); indexta++;} 
        else { print_sm_error(Sym_cour.NOM, ligne, " in procedure record declaration is Already Declared"); sm_error = true; }
  }

      Test_Symbole(ID_TOKEN, "ID_TOKEN");
      while(Sym_cour.CODE == VR_TOKEN){
          Test_Symbole(VR_TOKEN, "VR_TOKEN");

           if(Sym_cour.CODE == ID_TOKEN){
        if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLRECORDPROC); indexta++; } 
        else { print_sm_error(Sym_cour.NOM, ligne, " in procedure record declaration is Already Declared"); sm_error = true; }
  }

          Test_Symbole(ID_TOKEN, "ID_TOKEN");
      }
      Test_Symbole(TYPESYM_TOKEN, "ERRPR_TYPESYM_TOKEN");
                 if(Sym_cour.CODE == ID_TOKEN) {

                     if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLRECORDPROC); indexta++;} 
        else { print_sm_error(Sym_cour.NOM, ligne, " in procedure record declaration is Already Declared"); sm_error = true; }
                                  Test_Symbole(ID_TOKEN, "ID_TOKEN");
                             
                            } else if(Sym_cour.CODE == INTEGER_TOKEN){
                                  table_symboles[indexta].typevar = TINTEGER;
                                  Test_Symbole(INTEGER_TOKEN, "INTEGER_TOKEN");                              

                            } else if (Sym_cour.CODE == NATURAL_TOKEN) {
                                  table_symboles[indexta].typevar = TNATURAL;
                                  Test_Symbole(NATURAL_TOKEN, "NATURAL_TOKEN");                        

                            }else if(Sym_cour.CODE == FLOAT_TOKEN){
                                    table_symboles[indexta].typevar = TFLOAT;
                                    Test_Symbole(FLOAT_TOKEN, "FLOAT_TOKEN");
                             
                            }else if (Sym_cour.CODE == BOOLEAN_TOKEN){
                                  table_symboles[indexta].typevar = TBOOLEAN;
                                   Test_Symbole(BOOLEAN_TOKEN, "BOOLEAN_TOKEN");

                            } else if (Sym_cour.CODE == POSITIVE_TOKEN){
                                    table_symboles[indexta].typevar = TPOSITIVE;
                                    Test_Symbole(POSITIVE_TOKEN, "POSITIVE_TOKEN");

                            } else if (Sym_cour.CODE == STRINGKEY_TOKEN) {
                                  table_symboles[indexta].typevar = TSTRING;
                                  Test_Symbole(STRINGKEY_TOKEN, "STRINGKEY_TOKEN");                              
                            } else if (Sym_cour.CODE == CHARACTER_TOKEN ){
                                  table_symboles[indexta].typevar = TCHARACTER;
                                  Test_Symbole(CHARACTER_TOKEN, "CHARACTER_TOKEN");
                          } else {
                                printf("\n SYNTAX ERROR ________________DECL_RECORD_______________ \n"); exit(0);
                          }
      Test_Symbole(PV_TOKEN, "PV_TOKEN");
}


void DECLSRECORDPack(){
    if(Sym_cour.CODE == ID_TOKEN){
        if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLRECORDP); indexta++;} 
        else { print_sm_error(Sym_cour.NOM, ligne, " in package record declaration is Already Declared"); sm_error = true; }
  }

      Test_Symbole(ID_TOKEN, "ID_TOKEN");
      while(Sym_cour.CODE == VR_TOKEN){
          Test_Symbole(VR_TOKEN, "VR_TOKEN");

           if(Sym_cour.CODE == ID_TOKEN){
        if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLRECORDP); indexta++; } 
        else { print_sm_error(Sym_cour.NOM, ligne, " in package record declaration is Already Declared"); sm_error = true; }
  }

          Test_Symbole(ID_TOKEN, "ID_TOKEN");
      }
      Test_Symbole(TYPESYM_TOKEN, "ERRPR_TYPESYM_TOKEN");
      if(Sym_cour.CODE == ID_TOKEN || Sym_cour.CODE == INTEGER_TOKEN || Sym_cour.CODE == NATURAL_TOKEN || Sym_cour.CODE == FLOAT_TOKEN || Sym_cour.CODE == BOOLEAN_TOKEN ||
        Sym_cour.CODE == POSITIVE_TOKEN || Sym_cour.CODE == STRING_TOKEN || Sym_cour.CODE == CHARACTER_TOKEN){
         if(Sym_cour.CODE == ID_TOKEN){
        if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLRECORDP); indexta++;} 
        else { print_sm_error(Sym_cour.NOM, ligne, " in package record declaration is Already Declared"); sm_error = true; }
  }
          lire();
          //printf("  %s", Sym_cour.NOM);
      } else {
          printf("\n SYNTAX ERROR ________________DECLSRECORD________________ \n"); exit(0);
      }
      Test_Symbole(PV_TOKEN, "PV_TOKEN");

}


void DECLSRECORDF(){
    if(Sym_cour.CODE == ID_TOKEN){
        if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLRECORDF); indexta++;} 
        else { print_sm_error(Sym_cour.NOM, ligne, " in function record declaration is Already Declared"); sm_error = true; }
  }

      Test_Symbole(ID_TOKEN, "ID_TOKEN");
      while(Sym_cour.CODE == VR_TOKEN){
          Test_Symbole(VR_TOKEN, "VR_TOKEN");

           if(Sym_cour.CODE == ID_TOKEN){
        if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLRECORDF); indexta++;} 
        else { print_sm_error(Sym_cour.NOM, ligne, "  in function record declaration is Already Declared"); sm_error = true; }
  }

          Test_Symbole(ID_TOKEN, "ID_TOKEN");
      }
      Test_Symbole(TYPESYM_TOKEN, "ERRPR_TYPESYM_TOKEN");
      if(Sym_cour.CODE == ID_TOKEN || Sym_cour.CODE == INTEGER_TOKEN || Sym_cour.CODE == NATURAL_TOKEN || Sym_cour.CODE == FLOAT_TOKEN || Sym_cour.CODE == BOOLEAN_TOKEN ||
        Sym_cour.CODE == POSITIVE_TOKEN || Sym_cour.CODE == STRING_TOKEN || Sym_cour.CODE == CHARACTER_TOKEN){
         if(Sym_cour.CODE == ID_TOKEN){
        if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TDECLRECORDF); indexta++;} 
        else { print_sm_error(Sym_cour.NOM, ligne, "  in function record declaration is Already Declared"); sm_error = true; }
  }
          lire();
          //printf("  %s", Sym_cour.NOM);
      } else {
          printf("\n SYNTAX ERROR ________________DECLSRECORD________________ \n"); exit(0);
      }
      Test_Symbole(PV_TOKEN, "PV_TOKEN");

}


// ENUMFUNC ::=  id { ,id } );
void ENUMFUNC(){
   Test_Symbole(ID_TOKEN, "ID_TOKEN");
  while(Sym_cour.CODE == VR_TOKEN){
          Test_Symbole(VR_TOKEN, "VR_TOKEN");
          Test_Symbole(ID_TOKEN, "ID_TOKEN");
  }
  Test_Symbole(PF_TOKEN, "PF_TOKEN");
  Test_Symbole(PV_TOKEN, "PV_TOKEN");
  //printf("\n SYNTAX ERROR ________________ ENUM ________________ \n");
}

//  INSTS ::=  ID AFFECINSTS | FOR FORINSTS | WHILE WHILEINSTS | IF IFINSTS  | Put_Line PUTLINEINST | return EXPR ; | case CASEINST | null; | loop INSTS end loop; | epsilon
void  INSTS(){
   switch (Sym_cour.CODE){
          case ID_TOKEN :         if(Sym_cour.CODE == ID_TOKEN){
                                          if(isConst(Sym_cour.NOM) == true) { print_sm_error(Sym_cour.NOM, ligne, "cant\' modify const"); sm_error = true; } 
                                          if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "in assignment undeclared first use in this function"); sm_error = true; }
                                  }
                          Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
                          AFFECINSTS();
                          break;

          case FOR_TOKEN : Test_Symbole(FOR_TOKEN, "FOR_TOKEN"); 
                          FORINSTS();
                           break;
          case WHILE_TOKEN: Test_Symbole(WHILE_TOKEN,"WHILE_TOKEN");
                            WHILEINSTS();
                            break;
          case IF_TOKEN :  Test_Symbole(IF_TOKEN, "IF_TOKEN"); 
                           IFINSTS();
                           break;
          case PUTLINE_TOKEN : Test_Symbole(PUTLINE_TOKEN, "PUTLINE_TOKEN");
                               PUTLINEINST();
                               break;
          case RETURN_TOKEN : Test_Symbole(RETURN_TOKEN, "RETURN_TOKEN");                            
                              EXPR();
                              Test_Symbole(PV_TOKEN, "PV_TOKEN");
                              break;
          case LOOP_TOKEN : Test_Symbole(LOOP_TOKEN, "LOOP_TOKEN");
                        while(Sym_cour.CODE != END_TOKEN){
                              INSTS();
                        }                          
                            Test_Symbole(END_TOKEN, "END_TOKEN");
                            Test_Symbole(LOOP_TOKEN, "LOOP_TOKEN");
                            Test_Symbole(PV_TOKEN, "PV_TOKEN");
                            break;

          case NULL_TOKEN : Test_Symbole(NULL_TOKEN, "NULL_TOKEN"); Test_Symbole(PV_TOKEN, "PV_TOKEN"); break;

          case  END_TOKEN :  break;

          case CASE_TOKEN : Test_Symbole(CASE_TOKEN, "CASE_TOKEN");  CASEINST(); break;

         default: printf("\n SYNTAX ERROR ________________ARRAYFUNC1________________ \n"); exit(0);  break;  
    }
}
//  CASEINST ::=   case id is {when EXPR => INSTS} end case ;
void CASEINST(){
      if(Sym_cour.CODE == ID_TOKEN){
          if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "case name undeclared first use in this function"); sm_error = true; }
                                  }
      Test_Symbole(ID_TOKEN, "ID_TOKEN");
      Test_Symbole(IS_TOKEN, "IS_TOKEN");
      while(Sym_cour.CODE == WHEN_TOKEN){
        Test_Symbole(WHEN_TOKEN, "WHEN_TOKEN");
        EXPR();
        Test_Symbole(DEPENDING_TOKEN, "DEPENDING_TOKEN");
        INSTS();
      }
      Test_Symbole(END_TOKEN, "END_TOKEN");
      Test_Symbole(CASE_TOKEN, "CASE_TOKEN");
      Test_Symbole(PV_TOKEN, "PV_TOKEN");
}



// PUTLINEINST ::=   ( STRING | ID   ) ;
void PUTLINEINST(){
  Test_Symbole(PO_TOKEN, "PO_TOKEN");
  switch (Sym_cour.CODE){
    case STRING_TOKEN : Test_Symbole(STRING_TOKEN, "STRING_TOKEN"); break;
    case ID_TOKEN : if(Sym_cour.CODE == ID_TOKEN){
                                          
                                          if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "Put_line id undeclared first use in this function"); sm_error = true; }
                                  }
                        Test_Symbole(ID_TOKEN, "ID_TOKEN"); break;
   default: printf("\n SYNTAX ERROR ________________PUTLINEINST________________ \n"); exit(0);  break; 
  } 
  Test_Symbole(PF_TOKEN, "PF_TOKEN");
  Test_Symbole(PV_TOKEN, "PV_TOKEN");
}



// AFFECINSTS ::=  := EXPR ;
void AFFECINSTS(){
      Test_Symbole(AFF_TOKEN, "AFF_TOKEN"); 
      EXPR();
      Test_Symbole(PV_TOKEN, "PV_TOKEN"); 
}

// FORINSTS ::=    id in int | ID .. int | ID loop {INSTS} end loop;
void FORINSTS(){
  if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, " id in for undeclared first use in this function"); sm_error = true; }  }
                                 
    Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
    Test_Symbole(IN_TOKEN, "IN_TOKEN");
    // switch case
    switch (Sym_cour.CODE){
          case ID_TOKEN : if(Sym_cour.CODE == ID_TOKEN){
                                        
                                          if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, " id in for undeclared first use in this function"); sm_error = true; }
                                  }
                          Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
                          Test_Symbole(FROMTO_TOKEN, "FROMTO_TOKEN");
                          switch (Sym_cour.CODE){
                                        case ID_TOKEN : if(Sym_cour.CODE == ID_TOKEN){
                                         
                                          if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "id in for undeclared first use in this function"); sm_error = true; }
                                  }

                                                            Test_Symbole(ID_TOKEN, "ID_TOKEN");  
                                                            break;

                                        case INT_TOKEN : Test_Symbole(INT_TOKEN, "INT_TOKEN"); 
                                                            break;

                                        default: printf("\n SYNTAX ERROR ________________FORINSTS2________________ \n"); exit(0);  break;  
                                  }
                          break;


          case INT_TOKEN : a = atoi(Sym_cour.NOM);
                          Test_Symbole(INT_TOKEN, "INT_TOKEN"); 
                          Test_Symbole(FROMTO_TOKEN, "FROMTO_TOKEN");
                          switch (Sym_cour.CODE){
                                        case ID_TOKEN : 
 if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, "id in for undeclared first use in this function"); sm_error = true; }  }
                                        Test_Symbole(ID_TOKEN, "ID_TOKEN"); 
                                                            break;
                                        case INT_TOKEN :    b = atoi(Sym_cour.NOM);
                                                            Test_Symbole(INT_TOKEN, "INT_TOKEN"); 
                                                            if(a > b){
                                                                print_sm_error("for ", ligne, " must be greater than previous integer "); sm_error = true;
                                                            }
                                                            break;

                                        default: printf("\n SYNTAX ERROR ________________FORINSTS2________________ \n"); exit(0);  break;  
                                  }
                          break;
          default: printf("\n SYNTAX ERROR ________________FORINSTS1________________ \n"); exit(0);  break;  
   }
    Test_Symbole(LOOP_TOKEN, "LOOP_TOKEN");
    while(Sym_cour.CODE != END_TOKEN){
          INSTS();
    }
    Test_Symbole(END_TOKEN, "END_TOKEN");
    Test_Symbole(LOOP_TOKEN, "LOOP_TOKEN");
    Test_Symbole(PV_TOKEN, "PV_TOKEN");
}



// WHILEINSTS ::=   COND  {['and'|'or'|'xor'] COND} 'loop' INSTS 'end' 'loop' ';'
void WHILEINSTS(){
          COND();
          while(Sym_cour.CODE == AND_TOKEN || Sym_cour.CODE == OR_TOKEN || Sym_cour.CODE == XOR_TOKEN){
                 //printf("  %s", Sym_cour.NOM);
                 lire();
                 COND();
          }
        Test_Symbole(LOOP_TOKEN, "LOOP_TOKEN");
        while(Sym_cour.CODE != END_TOKEN){
            INSTS();
        }      
        Test_Symbole(END_TOKEN, "END_TOKEN");
        Test_Symbole(LOOP_TOKEN, "LOOP_TOKEN");
        Test_Symbole(PV_TOKEN, "PV_TOKEN");
}




//   IFINSTS  ::=  COND  {['and'|'or'|'xor'] COND}  then  INSTS (else INSTS |  {elsif COND {[and COND | or COND]} then INSTS}  else INSTS ) end if ;
void IFINSTS(){
  COND();
  while(Sym_cour.CODE == AND_TOKEN || Sym_cour.CODE == OR_TOKEN || Sym_cour.CODE == XOR_TOKEN){
         //printf("  %s", Sym_cour.NOM);
         lire();
         COND();
  }
  Test_Symbole(THEN_TOKEN, "THEN_TOKEN");
  INSTS();
  switch (Sym_cour.CODE){
            case ELSE_TOKEN  : Test_Symbole(ELSE_TOKEN, "ELSE_TOKEN"); INSTS(); break;
            case ELSIF_TOKEN : Test_Symbole(ELSIF_TOKEN, "ELSIF_TOKEN"); 
                                COND();
                                  while(Sym_cour.CODE == AND_TOKEN || Sym_cour.CODE == OR_TOKEN){
                                         //printf("  %s", Sym_cour.NOM);
                                         lire();
                                         COND();
                                  }
                                Test_Symbole(THEN_TOKEN, "THEN_TOKEN");
                                INSTS(); 
                                while(Sym_cour.CODE == ELSIF_TOKEN){
                                      Test_Symbole(ELSIF_TOKEN, "ELSIF_TOKEN");
                                      COND();
                                      while(Sym_cour.CODE == AND_TOKEN || Sym_cour.CODE == OR_TOKEN){
                                             //printf("  %s", Sym_cour.NOM);
                                             lire();
                                             COND();
                                      }
                                      Test_Symbole(THEN_TOKEN, "THEN_TOKEN");
                                      INSTS();
                                }
                                Test_Symbole(ELSE_TOKEN, "ELSE_TOKEN");
                                INSTS();
                                break;
            case END_TOKEN : break;
           default: printf("\n SYNTAX ERROR ________________IFINSTS________________ \n"); exit(0);  break;  
  }
  Test_Symbole(END_TOKEN, "END_TOKEN");
  Test_Symbole(IF_TOKEN, "IF_TOKEN");
  Test_Symbole(PV_TOKEN, "PV_TOKEN");
}





//COND    ::= EXPR [= | /= | < | > | <= | >= | in | 'mod'] EXPR
void COND(){
    EXPR();
        if(Sym_cour.CODE == EQUAL_TOKEN || Sym_cour.CODE == NOTEQUAL_TOKEN || Sym_cour.CODE == LESSTHAN_TOKEN || Sym_cour.CODE == GREATERTHAN_TOKEN ||
         Sym_cour.CODE == GREATERTHANEQUAL_TOKEN || Sym_cour.CODE == LESSTHANEQUAL_TOKEN  || Sym_cour.CODE == IN_TOKEN || Sym_cour.CODE == MOD_TOKEN ){
            //printf("  %s", Sym_cour.NOM);
            lire();
            EXPR();
        }else{
            printf("\nSYNTAX ERROR ________________COND________________ \n");
            exit(0);
        }
}

//  EXPR ::=  TERM { [+|-] TERM}
void EXPR(){
    term();
    while( Sym_cour.CODE == PLUS_TOKEN || Sym_cour.CODE == MINUS_TOKEN){
        //printf("  %s", Sym_cour.NOM);
        lire();
        term();
    }
}

//TERM    ::= FACT { [*|/| 'mod'] FACT }
void term(){
    fact();
    while( Sym_cour.CODE  == MULT_TOKEN || Sym_cour.CODE == DIVIDE_TOKEN || Sym_cour.CODE == MOD_TOKEN){
          //printf("  %s", Sym_cour.NOM);
          lire();
          fact();
    }
}

//FACT    ::= ID | NUM (.. NUM | epsilon ) | True | False | String | Char | (EXPR)

void fact(){
    switch (Sym_cour.CODE) {
    case ID_TOKEN:   if(Sym_cour.CODE == ID_TOKEN){ if(isDeclared(Sym_cour.NOM) == false) { print_sm_error(Sym_cour.NOM, ligne, " expr id undeclared first use in this function"); sm_error = true; }  }
                    Test_Symbole(ID_TOKEN, "ID_TOKEN");
                    break;
    case INT_TOKEN: //table_symboles[indexta].value = atoi(Sym_cour.NOM);
                    a = atoi(Sym_cour.NOM);
                    Test_Symbole(INT_TOKEN, "INT_TOKEN"); 
                    if(Sym_cour.CODE == FROMTO_TOKEN){
                          Test_Symbole(FROMTO_TOKEN, "FROMTO_TOKEN");
                           b = atoi(Sym_cour.NOM); 
                           Test_Symbole(INT_TOKEN, "INT_TOKEN");                         
                          if(a > b){
                                print_sm_error(" ", ligne, " must be greater than previous integer "); sm_error = true;
                          }                         
                    } 
                    break;
    case REALINT_TOKEN:  //table_symboles[indexta].value = atoi(Sym_cour.NOM);
                        Test_Symbole(REALINT_TOKEN, "REALINT_TOKEN");  break;
    case CHAR_TOKEN :  Test_Symbole(CHAR_TOKEN,"CHAR_TOKEN"); break;
    case STRING_TOKEN :  Test_Symbole(STRING_TOKEN,"STRING_TOKEN"); break;
    case TRUE_TOKEN: Test_Symbole(TRUE_TOKEN, "TRUE_TOKEN");  break;
    case FALSE_TOKEN: Test_Symbole(FALSE_TOKEN, "FALSE_TOKEN");  break;
    case PO_TOKEN:  Test_Symbole(PO_TOKEN, "PO_TOKEN");
                    EXPR();
                    Test_Symbole(PF_TOKEN, "PF_TOKEN");
                    break;
    default: printf("\nSYNTAX ERROR ________________FACT________________ \n");
               exit(0); break;  
    }
}


//Dec_function : function id_token_func{ ARGUMENTS  return type  is DECLS begin INSTS end id ;
void Dec_function(){
      Test_Symbole(FUNCTION_TOKEN, "FUNCTION_TOKEN");
      if(Sym_cour.CODE == ID_TOKEN){

         if( isDeclared(Sym_cour.NOM) == false) { table_symboles[symbole_t_index++] = new_idf(Sym_cour.NOM, TFUNC); indexta++; table_symboles[indexta].typevar = ID;
                } 
        else { print_sm_error(Sym_cour.NOM, ligne, "function name is Already Declared"); sm_error = true; }            
     }
     strcpy(ID_FUNC, Sym_Cour.NOM);
    Test_Symbole(ID_TOKEN, "ID_TOKEN");
    ARGUMENTSFunc();
    Test_Symbole(RETURN_TOKEN, "RETURN_TOKEN");
     if(Sym_cour.CODE == ID_TOKEN || Sym_cour.CODE == INTEGER_TOKEN || Sym_cour.CODE == NATURAL_TOKEN || Sym_cour.CODE == FLOAT_TOKEN || Sym_cour.CODE == BOOLEAN_TOKEN ){
          lire();
          //printf("  %s", Sym_cour.NOM);
      } else {
          printf("\n SYNTAX ERROR ________________TYPE_RETURN________________ \n"); exit(0);
      }
    Test_Symbole(IS_TOKEN, "IS_TOKEN");
    //printf("\n\n________________FIN_FUNCTION_LIGNE________________ \n");
    DECLSF();
    Test_Symbole(BEGIN_TOKEN, "BEGIN_TOKEN");

    while(Sym_cour.CODE != END_TOKEN){
      INSTS();
    }    
    Test_Symbole(END_TOKEN, "END_TOKEN");
    if(strcmp(Sym_cour.NOM, ID_FUNC) == 0){
        Test_Symbole(ID_TOKEN, "ID_TOKEN");
    } else{
        printf("\n Semantic Error  😜😝😜 : %s in row %d %s\n", ID_FUNC, ligne, "Expected to end this function");
    }
    Test_Symbole(PV_TOKEN, "PV_TOKEN");
}

//  ARGUMENTSFunc    ::=  (ID {,ID} : TYPEARGF {; ID : TYPEARGF } ) | epsilon
void ARGUMENTSFunc(){
  //printf("\n");
  switch (Sym_cour.CODE) {  
              case PO_TOKEN :  Test_Symbole(PO_TOKEN, "PO_TOKEN");
                                     if(Sym_cour.CODE == ID_TOKEN){
                                              if(isDeclaredArg(Sym_cour.NOM) == false) { table_symbolesArg[symbole_t_indexArg++] = new_idfArg(Sym_cour.NOM, TARGFUNC); indexArg++; } 
                                              else { print_sm_error(Sym_cour.NOM, ligne, "function argument is Already Declared"); sm_error = true; }
                                    }
                               Test_Symbole(ID_TOKEN, "ID_TOKEN");
                               while(Sym_cour.CODE == VR_TOKEN){
                                    Test_Symbole(VR_TOKEN, "VR_TOKEN");
                                     if(Sym_cour.CODE == ID_TOKEN){
                                              if(isDeclaredArg(Sym_cour.NOM) == false) { table_symbolesArg[symbole_t_indexArg++] = new_idfArg(Sym_cour.NOM, TARGFUNC); indexArg++; } 
                                              else { print_sm_error(Sym_cour.NOM, ligne, "function argument is Already Declared"); sm_error = true; }
                                    }
                                    Test_Symbole(ID_TOKEN, "ID_TOKEN");
                               }
                               Test_Symbole(TYPESYM_TOKEN, "TYPESYM_TOKEN"); 
                               TYPEARGF();
                                while(Sym_cour.CODE == PV_TOKEN){
                                      Test_Symbole(PV_TOKEN,"PV_TOKEN");
                                       if(Sym_cour.CODE == ID_TOKEN){
                                              if(isDeclaredArg(Sym_cour.NOM) == false) { table_symbolesArg[symbole_t_indexArg++] = new_idfArg(Sym_cour.NOM, TARGFUNC); indexArg++; } 
                                              else { print_sm_error(Sym_cour.NOM, ligne, " function argument is Already Declared"); sm_error = true; }
                                    }
                                      Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                      while(Sym_cour.CODE == VR_TOKEN){
                                            Test_Symbole(VR_TOKEN, "VR_TOKEN");
                                             if(Sym_cour.CODE == ID_TOKEN){
                                                          if(isDeclaredArg(Sym_cour.NOM) == false) { table_symbolesArg[symbole_t_indexArg++] = new_idfArg(Sym_cour.NOM, TARGFUNC); indexArg++; } 
                                                          else { print_sm_error(Sym_cour.NOM, ligne, "function argument is Already Declared"); sm_error = true; }
                                             }
                                            Test_Symbole(ID_TOKEN, "ID_TOKEN");
                                      }
                                      Test_Symbole(TYPESYM_TOKEN, "TYPESYM_TOKEN"); 
                                      TYPEARGF();
                                }
                                Test_Symbole(PF_TOKEN, "PF_TOKEN");
                                break;

              case IS_TOKEN : break;  // epsilon
              default: printf("\n SYNTAX ERROR ________________PROCEDURE________________ \n");  exit(0); break;  
  }    
    //printf("\n\n________________FIN_ARGUMENTS________________ \n");  
}


/*
int main(){

	fichier = fopen(nomfichier, "r");
	if(fichier != NULL){		
    	   package();
    			 if(Sym_cour.CODE == FIN_TOKEN){
                //printf_table_S();
    			 		  printf("\n BRAVO: le programme est correcte!!!\n");
    			 }else{
                printf_table_S();
    			 		  printf("\n PAS BRAVO: fin de programme erronée!!!!\n");	
    			 }  
	} else {
    		printf("Erreur d'ouverture du fichier source..\n\n");
    		exit(0);
	}
	fclose(fichier);

	return 0;
}
*/