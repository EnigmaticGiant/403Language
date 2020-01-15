#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "scanner.h"
#include "types.h"
#include "lexer.h"
#include "lexeme.h"


void scanner(FILE *filename){
	//printf("starting the scanner\n");
    lexeme *token; 
    token = lex(filename); 
    while (strcmp(getLexemeType(token) ,"ENDofINPUT") != 0) { 
        displayLexeme(token); 
        token = lex(filename); 
    }
    displayLexeme(token); 
}

int main(int argc, char* argv[]){
	if(argc == 1){
		fprintf(stderr,"There ain't no file to read, dummy!\n");
		exit(-1);
	}
	FILE *read = fopen(argv[1], "r");
	scanner(read);
	return 0;
}
