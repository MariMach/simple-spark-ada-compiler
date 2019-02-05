#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>


#include "syntax.c"





const char nomfichier[] = "/home/meriem/Desktop/spark/ifloop";
FILE* fichier = NULL;

token Sym_cour;

void lire(){
	Sym_cour = lireFichier(fichier);
}


int main(){

	fichier = fopen(nomfichier, "r");
	if(fichier != NULL){		
    	   package();
    			 if(Sym_cour.CODE == FIN_TOKEN){
	    			 	if(sm_error == false){
	    			 		printf("\n BRAVO: le programme est correcte!!!\n\n");
	    			 		printf_table_S();
	    			 	 }else{
	    			 	 printf("\n PAS BRAVO: fin de programme erronée!!!!\n\n");	
	    			 	}		  
    			 }else{
    			 	 printf("\n PAS BRAVO: fin de programme erronée!!!!\n\n");	
    			 }  
	} else {
    		printf("Erreur d'ouverture du fichier source..\n\n");
    		exit(0);
	}
	fclose(fichier);

	return 0;
}

