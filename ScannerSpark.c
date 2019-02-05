#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>

#define IDFSIZE 50 // taille maximal d'un identificateur
#define NUMBERSIZE 50 // talle maximal d'un nombre
#define COMMENTSIZE 100

typedef enum{
	//other tokens
		ID_TOKEN, INT_TOKEN, ERROR_TOKEN, REALINT_TOKEN, FIN_TOKEN, STRING_TOKEN,
	//keyword tokens
		PACKAGE_TOKEN, PROJECT_TOKEN, FOR_TOKEN, IS_TOKEN, END_TOKEN, USE_TOKEN, WITH_TOKEN, TYPE_TOKEN, RANGE_TOKEN, NEW_TOKEN, ARRAY_TOKEN,
		FUNCTION_TOKEN, RETURN_TOKEN, OF_TOKEN, OUT_TOKEN, BODY_TOKEN, BEGIN_TOKEN, LOOP_TOKEN, IF_TOKEN, THEN_TOKEN, WHILE_TOKEN, RECORD_TOKEN,
		CASE_TOKEN, WHEN_TOKEN, NULL_TOKEN, IN_TOKEN, ALL_TOKEN, NOT_TOKEN, SOME_TOKEN, ELSE_TOKEN, AND_TOKEN, PRAGMA_TOKEN, SUBTYPE_TOKEN, 
		PROCEDURE_TOKEN, OR_TOKEN, CONSTANT_TOKEN, ELSIF_TOKEN, PRIVATE_TOKEN, MOD_TOKEN, XOR_TOKEN, OVERRIDING_TOKEN, INTERFACES_TOKEN, 
		OTHERS_TOKEN, PRE_TOKEN, POST_TOKEN, DEPENDS_TOKEN, ON_TOKEN, OFF_TOKEN, LIMITED_TOKEN, INTEGER_TOKEN, TRUE_TOKEN, RAISE_TOKEN, CHAR_TOKEN,
		FALSE_TOKEN, BOOLEAN_TOKEN, NATURAL_TOKEN, GLOBAL_TOKEN, INPUT_TOKEN, OUTPUT_TOKEN, IN_OUT_TOKEN, PUTLINE_TOKEN, CHARACTER_TOKEN, STRINGKEY_TOKEN,
		OLD_TOKEN, LENGTH_TOKEN, LAST_TOKEN, FIRST_TOKEN, VARSRANGE_TOKEN, SPARKMODE_TOKEN, FLOAT_TOKEN, PROTECTED_TOKEN, EXCEPTION_TOKEN, POSITIVE_TOKEN, 

	// Symboles
		 PT_TOKEN,  AFF_TOKEN, DEPENDING_TOKEN, RANGEREDECLARE_TOKEN, NOTEQUAL_TOKEN, FROMTO_TOKEN, TYPESYM_TOKEN, MULT_TOKEN,
		 DIVIDE_TOKEN, POWER_TOKEN, EQUAL_TOKEN, PV_TOKEN, VR_TOKEN, PLUS_TOKEN, MINUS_TOKEN, GREATERTHANEQUAL_TOKEN,
		GREATERTHAN_TOKEN, LESSTHANEQUAL_TOKEN, LESSTHAN_TOKEN, ANDLOGICAL_TOKEN, PO_TOKEN, PF_TOKEN, COMMENT_TOKEN
	
}CODES_LEX;



typedef struct token{
		CODES_LEX CODE;
        char NOM[100];
}token;

token nomToken[] = {
		{PACKAGE_TOKEN,"package"},
		{CONSTANT_TOKEN,"constant"},
		{FOR_TOKEN,"for"},
		{IS_TOKEN, "is"},
		{END_TOKEN,"end"},
		{USE_TOKEN,"use"}, 
		{WHILE_TOKEN, "while"},
		{PROJECT_TOKEN, "project"},
		{RANGE_TOKEN, "range"},
		{WITH_TOKEN, "with"}, 
		{TYPE_TOKEN, "type"},
		{NEW_TOKEN, "new"},
		{ARRAY_TOKEN, "array"},
		{FUNCTION_TOKEN, "function"},
		{RETURN_TOKEN, "return"},
		{OF_TOKEN, "of"}, 
		{OUT_TOKEN, "out"},
		{BODY_TOKEN, "body"},
		{BEGIN_TOKEN, "begin"},
		{LOOP_TOKEN, "loop"},
		{IF_TOKEN, "if"},
		{THEN_TOKEN, "then"},
		{RECORD_TOKEN, "record"},
		{CASE_TOKEN, "case"},
		{WHEN_TOKEN, "when"},
		{NULL_TOKEN, "null"},
		{IN_TOKEN, "in"},
		{ALL_TOKEN, "all"},
		{NOT_TOKEN, "not"},
		{SOME_TOKEN, "some"}, 
		{ELSE_TOKEN, "else"},
		{AND_TOKEN, "and"},
		{PRAGMA_TOKEN, "pragma"},
		{SUBTYPE_TOKEN, "subtype"},
		{PROCEDURE_TOKEN, "procedure"},
		{OR_TOKEN, "or"}, 
		{ELSIF_TOKEN, "elsif"},
		{PRIVATE_TOKEN, "private"},
		{MOD_TOKEN, "mod"},
		{XOR_TOKEN, "xor"},
		{OVERRIDING_TOKEN, "overriding"}, 
		{INTERFACES_TOKEN, "interfaces"},
		{OTHERS_TOKEN, "others"}, 
		{PRE_TOKEN, "Pre"}, 
		{POST_TOKEN, "Post"},
		{DEPENDS_TOKEN, "Depends"},
		{ON_TOKEN, "On"},
		{OFF_TOKEN, "Off"},
		{LIMITED_TOKEN, "limited"},
		{OLD_TOKEN, "'Old"},
		{INTEGER_TOKEN, "Integer"}, 
		{TRUE_TOKEN, "True"}, 
		{FALSE_TOKEN, "False"}, 
		{SPARKMODE_TOKEN, "SPARK_Mode"},
		{LAST_TOKEN, "'Last"},
		{FIRST_TOKEN, "'First"}, 
		{LENGTH_TOKEN, "'Length"}, 
		{VARSRANGE_TOKEN, "'Range"}, 
		{BOOLEAN_TOKEN, "Boolean"},
		{NATURAL_TOKEN, "Natural"},
		{GLOBAL_TOKEN, "Global"}, 
		{INPUT_TOKEN, "Input"}, 
		{OUTPUT_TOKEN,"Output"}, 
		{IN_OUT_TOKEN, "In_Out"},
		{FLOAT_TOKEN, "Float"},
		{PUTLINE_TOKEN, "Put_Line"},
		{PROTECTED_TOKEN,"Protected"},
		{RAISE_TOKEN, "raise"},
		{EXCEPTION_TOKEN, "exception"},
		{CHARACTER_TOKEN, "Character"},
		{POSITIVE_TOKEN, "Positive"},
		{STRINGKEY_TOKEN, "String"}
};


token symboleToken[] = {  
        {PO_TOKEN, "("},
        {PF_TOKEN, ")"},          
        {PV_TOKEN, ";"},
        {VR_TOKEN, ","},
        {PLUS_TOKEN, "+"},        
        {ANDLOGICAL_TOKEN, "&"},

        {COMMENT_TOKEN, "--"},
        {TYPESYM_TOKEN, ":"},
        {AFF_TOKEN, ":="},
        {DEPENDING_TOKEN, "=>"},
        {RANGEREDECLARE_TOKEN, "<>"},
        {NOTEQUAL_TOKEN, "/="},
        {FROMTO_TOKEN, ".."},
        {POWER_TOKEN, "**"},
        {LESSTHANEQUAL_TOKEN, ">="},
        {GREATERTHANEQUAL_TOKEN, "<="},

        {DIVIDE_TOKEN, "/"},  
        {PT_TOKEN, "."}, 
        {MINUS_TOKEN, "-"}, 
        {MULT_TOKEN, "*"}, 
        {GREATERTHAN_TOKEN, ">"},   
        {LESSTHAN_TOKEN, "<"},
        {EQUAL_TOKEN, "="}
          
};

token Sym_Cour;
int ligne = 1; 

typedef int bool;
#define true 1
#define false 0

//const char nomfichier[] = "/home/meriem/Desktop/spark/testspark4";
//FILE* fichier = NULL;


char* keyword_token[] = {
			"package",
			"constant",
			"for",
			"is",
			"end",
			"use", 
			"while",
			"project",
			"range",
			"with", 
			"type",
			"new",
			"array",
			"function",
			"return",
			"of", 
			"out",
			"body",
			"begin",
			"loop",
			"if",
			"then",
			"record",
			"case",
			"when",
			"null",
			"in",
			"all",
			"not",
			"some", 
			"else",
			"and",
			"pragma",
			"subtype",
			"procedure",
			"or", 
			"elsif",
			"private",
			"mod",
			"xor",
			"overriding", 
			"interfaces",
			"others", 
			"Pre", 
			"Post",
			"Depends",
			"On",
			"Off",
			"limited",
			"'Old",
			"Integer", 
			"True", 
			"False", 
			"SPARK_Mode",
			"'Last",
			"'First", 
			"'Length", 
			"'Range", 
			"Boolean",
			"Natural",
			"Global", 
			"Input", 
			"Output", 
			"In_Out",
			"Float",
			"Put_Line",
			"Protected",
			"raise",
			"exception",
			"Character",
			"Positive",
			"String"
};
char*  keyword_code[]={
			"PACKAGE_TOKEN",
			"CONSTANT_TOKEN",
			"FOR_TOKEN",
			"IS_TOKEN",
			"END_TOKEN",
			"USE_TOKEN", 
			"WHILE_TOKEN",
			"PROJECT_TOKEN",
			"RANGE_TOKEN",
			"WITH_TOKEN", 
			"TYPE_TOKEN",
			"NEW_TOKEN",
			"ARRAY_TOKEN",
			"FUNCTION_TOKEN",
			"RETURN_TOKEN",
			"OF_TOKEN", 
			"OUT_TOKEN",
			"BODY_TOKEN",
			"BEGIN_TOKEN",
			"LOOP_TOKEN",
			"IF_TOKEN",
			"THEN_TOKEN",
			"RECORD_TOKEN",
			"CASE_TOKEN",
			"WHEN_TOKEN",
			"NULL_TOKEN",
			"IN_TOKEN",
			"ALL_TOKEN",
			"NOT_TOKEN",
			"SOME_TOKEN", 
			"ELSE_TOKEN",
			"AND_TOKEN",
			"PRAGMA_TOKEN",
			"SUBTYPE_TOKEN",
			"PROCEDURE_TOKEN",
			"OR_TOKEN", 
			"ELSIF_TOKEN",
			"PRIVATE_TOKEN",
			"MOD_TOKEN",
			"XOR_TOKEN",
			"OVERRIDING_TOKEN", 
			"INTERFACES_TOKEN",
			"OTHERS_TOKEN", 
			"PRE_TOKEN", 
			"POST_TOKEN",
			"DEPENDS_TOKEN",
			"ON_TOKEN",
			"OFF_TOKEN",
			"LIMITED_TOKEN",
			"OLD_TOKEN",
			"INTEGER_TOKEN",
			"TRUE_TOKEN", 
			"FALSE_TOKEN",
			"SPARKMODE_TOKEN",
			"LAST_TOKEN",
			"FIRST_TOKEN",
			"LENGTH_TOKEN",
			"VARSRANGE_TOKEN",
			"BOOLEAN_TOKEN",
			"NATURAL_TOKEN",
			"GLOBAL_TOKEN",
			"INPUT_TOKEN",
			"OUTPUT_TOKEN", 
			"IN_OUT_TOKEN",
			"FLOAT_TOKEN",
			"PUTLINE_TOKEN",
			"PROTECTED_TOKEN",
			"RAISE_TOKEN",
			"EXCEPTION_TOKEN",
			"CHARACTER_TOKEN",
			"POSITIVE_TOKEN",
			"STRINGKEY_TOKEN"
};
int keyword_token_size = sizeof(keyword_token)/sizeof(keyword_token[0]);

char symbole_token[] = {  
		'(',
		')',
		';',
		',',
		'+',
		'&'
};
char* symbole_code[] = {
		"PO_TOKEN",
        "PF_TOKEN",          
        "PV_TOKEN",
        "VR_TOKEN",
        "PLUS_TOKEN",       
        "ANDLOGICAL_TOKEN"
};
int symbole_token_size = sizeof(symbole_token)/sizeof(symbole_token[0]);



char* isSymboleCode(char c);
char* iskeyword(char* ch);
bool isAlphabetic(char c);
bool isNumeric(char c);
bool isBlanc(char car);
bool isSymbole(char c);
token lireFichier(FILE* fichier);


char* isSymboleCode(char c){
	int i;
	for(int i = 0; i < symbole_token_size; i++){
		if(c == symbole_token[i]){
			char* chaine1 = symbole_code[i];
			Sym_Cour.CODE = symboleToken[i].CODE;
			strcpy(Sym_Cour.NOM, symboleToken[i].NOM);
			return chaine1;
		}
	}
}


char* iskeyword(char* ch){
	int i;
	for(int i = 0; i < keyword_token_size; i++){
		if(strcmp(ch, keyword_token[i]) == 0){
			char* chaine1 = keyword_code[i];
			Sym_Cour.CODE = nomToken[i].CODE;
			strcpy(Sym_Cour.NOM, nomToken[i].NOM);
			return chaine1;
		}
	}
	Sym_Cour.CODE = ID_TOKEN;
	strcpy(Sym_Cour.NOM, ch);
	char* chaine2 = "ID_TOKEN";
	return chaine2;
}


bool isAlphabetic(char c){
     if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'){
        return true;
     }
     return false;
}


bool isNumeric(char c){
     if(c >= '0' && c <= '9'){
         return true;
     }
     return false;
}

bool isSymbole(char c){
          if(c == '+' || c == '(' || c == ')' || c == ';' || c == ',' || c == '&'){
               return true;
          }
    return false;
}

bool isBlanc(char car){
	if(car == ' ' || car == '\t'){
		return true;
	} else if ( car == '\n'){
				ligne++;
				return true;
	}
	return false;
}

token lireFichier(FILE* fichier){
			
			char car;
			car =  fgetc(fichier);
			int i = 0;
			char* number = (char *)malloc(NUMBERSIZE*sizeof(char));
			char* chaine = (char *)malloc(IDFSIZE*sizeof(char));
			
//traitement number
			if(isNumeric(car)){
				 do{
					 number[i] = car;
			 		 car = fgetc(fichier); // caractère suivant
					 i++;
		       		 }while (isNumeric(car));

				if(isAlphabetic(car)){
					do{
						number[i] = car;
			 			car = fgetc(fichier); // caractère suivant
						i++;
					}while(isAlphabetic(car));
					ungetc(car, fichier);
					number[i] = '\0';
					//printf("	ERROR_TOKEN(%s) 😜😝😜\n", number);
					Sym_Cour.CODE = ERROR_TOKEN;
					strcpy(Sym_Cour.NOM, number);
					return Sym_Cour;

				}else if(car == '.'){
							do{
									 number[i] = car;
							 		 car = fgetc(fichier); // caractère suivant
									 i++;
				       		 }while (isNumeric(car));				       		 
							ungetc(car, fichier);
							number[i] = '\0';
							float val = atof(number);
							//printf("	REALINT_TOKEN(%f)\n", val);
							Sym_Cour.CODE = REALINT_TOKEN;
							strcpy(Sym_Cour.NOM, number);
							return Sym_Cour;
							

				}else{
					ungetc(car, fichier);
					 number[i] = '\0';
					int val = atoi(number);
					//printf("	INT_TOKEN(%d)\n", val);
					Sym_Cour.CODE = INT_TOKEN;
					strcpy(Sym_Cour.NOM, number);
					return Sym_Cour;
					

				}
//traitment id et keyword
			}else if(isAlphabetic(car)){
				 do{
					 chaine[i] = car;
			 		 car = fgetc(fichier); // caractère suivant
					 i++;
		       		 }while (isAlphabetic(car) == true);
				if(isNumeric(car)){
					do{
						chaine[i] = car;
			 		 	car = fgetc(fichier); // caractère suivant
					 	i++;
					}while(isNumeric(car) || isAlphabetic(car));
					ungetc(car, fichier);
					chaine[i] = '\0';
					iskeyword(chaine);
					//printf("	%s(%s)\n",iskeyword(chaine),  chaine);
					return Sym_Cour;	
				}else{
					ungetc(car, fichier);
					chaine[i] = '\0';
					iskeyword(chaine);
					//printf("	%s(%s)\n",iskeyword(chaine),  chaine);	
					return Sym_Cour;
				}
				
			free(chaine);

//traitement symbole
			}else if(isSymbole(car)){
				isSymboleCode(car);
				//printf("	%s(%c)\n", isSymboleCode(car), car);
				return Sym_Cour;

//traitement < <= <>
			}else if( car == '<'){
				car = fgetc(fichier); // caractère suivant
				if(car == '='){
					//printf("	LESSTHANEQUAL_TOKEN(<=)\n");
					Sym_Cour.CODE = LESSTHANEQUAL_TOKEN;
					strcpy(Sym_Cour.NOM, "<=");
					return Sym_Cour;
				}else if(car == '>'){
					//printf("	RANGEREDECLARE_TOKEN(<>)\n");
					Sym_Cour.CODE = RANGEREDECLARE_TOKEN;
					strcpy(Sym_Cour.NOM, "<>");
					return Sym_Cour;
				}else{
					ungetc(car, fichier);
					//printf("	LESSTHAN_TOKEN(<)\n");
					Sym_Cour.CODE = LESSTHAN_TOKEN;
					strcpy(Sym_Cour.NOM, "<");
					return Sym_Cour;
				}
//traitement > >=
			}else if( car == '>'){
				car = fgetc(fichier); // caractère suivant
				if(car == '='){
					//printf("	GREATERTHANEQUAL_TOKEN(>=)\n");
					Sym_Cour.CODE = GREATERTHANEQUAL_TOKEN;
					strcpy(Sym_Cour.NOM, ">=");
					return Sym_Cour;
				}else{
					ungetc(car, fichier);
					//printf("	GREATERTHAN_TOKEN(>)\n");
					Sym_Cour.CODE = GREATERTHAN_TOKEN;
					strcpy(Sym_Cour.NOM, ">");
					return Sym_Cour;
				}			
//traitement :=
			}else if( car == ':'){
				car = fgetc(fichier); // caractère suivant
				if(car == '='){
					//printf("	AFF_TOKEN(:=)\n");
					Sym_Cour.CODE = AFF_TOKEN;
					strcpy(Sym_Cour.NOM, ":=");
					return Sym_Cour;

				}else {
					// TYPESYM_TOKEN
					ungetc(car, fichier);
					Sym_Cour.CODE = TYPESYM_TOKEN;
					strcpy(Sym_Cour.NOM, ":");
					return Sym_Cour;					
				}
//traitement  =>
			}else if( car == '='){
				car = fgetc(fichier); // caractère suivant
						if(car == '>'){
							//printf("	DEPENDING_TOKEN(=>)\n");
							Sym_Cour.CODE = DEPENDING_TOKEN;
							strcpy(Sym_Cour.NOM, "=>");
							return Sym_Cour;
// traitement =
						}else{
							//printf("	EQUAL_TOKEN(=)\n");
							Sym_Cour.CODE = EQUAL_TOKEN;
							strcpy(Sym_Cour.NOM, "=");
							return Sym_Cour;
						}
						
//caractere eof				
			}else if(car == EOF){
				//printf("	FIN_TOKEN(%c)\n", car);
				Sym_Cour.CODE = FIN_TOKEN;
				strcpy(Sym_Cour.NOM, "EOF");
				return Sym_Cour;
// caractere blanc			
			}else if(isBlanc(car)){
				do{
					car = fgetc(fichier);
				}while(isBlanc(car));
				ungetc(car, fichier);			
				return lireFichier(fichier);
// traitement ..
			}else if( car == '.'){
				car = fgetc(fichier); // caractère suivant
				if(car == '.'){
					//printf("	FROMTO_TOKEN(..)\n");
					Sym_Cour.CODE = FROMTO_TOKEN;
					strcpy(Sym_Cour.NOM, "..");
					return Sym_Cour;
// traitement .
				}else{
					ungetc(car, fichier);
					//printf("	PT_TOKEN(.)\n");
					Sym_Cour.CODE = PT_TOKEN;
					strcpy(Sym_Cour.NOM, ".");
					return Sym_Cour;
				}
// traitement **
			}else if( car == '*'){
					car = fgetc(fichier); // caractère suivant
					if(car == '*'){
						//printf("	POWER_TOKEN(**)\n");
						Sym_Cour.CODE = POWER_TOKEN;
						strcpy(Sym_Cour.NOM, "**");
						return Sym_Cour;
// traitement *
					}else{
						ungetc(car, fichier);
						//printf("	MULT_TOKEN(*)\n");
						Sym_Cour.CODE = MULT_TOKEN;
						strcpy(Sym_Cour.NOM, "*");
						return Sym_Cour;
					}

// traitement commentaires --
			}else if(car == '-'){
				if((car = fgetc(fichier)) == '-'){
					char* chainecomment = (char *)malloc(COMMENTSIZE*sizeof(char));
					int j = 0;
					do{
						car = fgetc(fichier);
						chainecomment[j] = car;
						j++;
					}while(car != '\n');
						if(car == '\n'){
							chainecomment[j-1] = '\0';
							ligne++;
							//printf("	COMMENT_TOKEN(%s)\n", chainecomment);
							return lireFichier(fichier);
						}	
// traitement -				
				}else{
					ungetc(car, fichier);
					//printf("	MINUS_TOKEN(-)\n");
					Sym_Cour.CODE = MINUS_TOKEN;
					strcpy(Sym_Cour.NOM, "-");
					return Sym_Cour;
				}

// traitement string "....."
			}else if(car == '"'){
					char* chainestring = (char *)malloc(COMMENTSIZE*sizeof(char));
					int e = 0;
					do{
						car = fgetc(fichier);
						chainestring[e] = car;
						e++;
					}while(car != '"' && car != '\n');
						if(car == '"'){
							chainestring[e-1] = '\0';
							//printf("	STRING_TOKEN(%s)\n", chainestring);
							Sym_Cour.CODE = STRING_TOKEN;
							strcpy(Sym_Cour.NOM, chainestring);
							return Sym_Cour;
// string error	
						}else{
							chainestring[e-1] = '\0';
							//printf("	ERROR_TOKEN(%s) 😜😝😜\n", chainestring);
							Sym_Cour.CODE = ERROR_TOKEN;
							strcpy(Sym_Cour.NOM, chainestring);
							return Sym_Cour;
						}	
// traitement char 	
	}else if(car == 39 ){
						car = fgetc(fichier);
						char str[2];
						str[0] = car;
						str[1] = '\0';
						if((car = fgetc(fichier)) == 39){
							Sym_Cour.CODE = CHAR_TOKEN;
							strcpy(Sym_Cour.NOM, str);
							return Sym_Cour;							
// char error	
						}else{
							ungetc(car, fichier);
							//printf("	ERROR_TOKEN(%s) 😜😝😜\n", str);
							Sym_Cour.CODE = ERROR_TOKEN;
							strcpy(Sym_Cour.NOM, str);
							return Sym_Cour;
						}		
				
// traitement commentaires /=
			}else if(car == '/'){
				if((car = fgetc(fichier)) == '='){
					//printf("	NOTEQUAL_TOKEN(/=)\n");
					Sym_Cour.CODE = NOTEQUAL_TOKEN;
					strcpy(Sym_Cour.NOM, "/=");
					return Sym_Cour;
								
// traitement /				
				}else{
					ungetc(car, fichier);
					//printf("	DIVIDE_TOKEN(/)\n");
					Sym_Cour.CODE = DIVIDE_TOKEN;
					strcpy(Sym_Cour.NOM, "/");
					return Sym_Cour;
				}			

// traitement error
			}else{
					//printf("	ERROR_TOKEN(%c) 😜😝😜\n", car);
					char str[2];
					str[0] = car;
					str[1] = '\0';
					Sym_Cour.CODE = ERROR_TOKEN;
					strcpy(Sym_Cour.NOM, str);
					return Sym_Cour;
			}

}



/*

int main(){
	fichier = fopen(nomfichier, "r");
	if(fichier != NULL){

			do{
				lireFichier(fichier);
			}while(Sym_Cour.CODE != FIN_TOKEN);
					

			 if(Sym_Cour.CODE == FIN_TOKEN){
			 		printf("\n BRAVO: le programme est correcte!!!\n");
			 }else{
			 		printf("\n PAS BRAVO: fin de programme erronée!!!!\n");	
			 }

  
	}else {
		printf("Erreur d'ouverture du fichier source..\n\n");
		exit(0);
	}

	fclose(fichier);
	return 0;
}

*/