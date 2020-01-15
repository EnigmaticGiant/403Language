#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pretty.h"

int iLevel = 0;

void indent(){
	for(int i = 0; i < iLevel; i++){
		printf("    ");
	}
}

void pp(lexeme *tree){
	char *type = getLexemeType(tree);
	//printf("the lexeme is currently\n");
	//displayLexeme(tree);
	if (type == STRING)
		printf("\"%s\"", getLexemeSVAL(tree));
	else if (type == INTEGER)
		printf("%d", getLexemeIVAL(tree));
	else if (type == VARIABLE){
		//printf("at the variable now\n");
		//displayLexeme(tree);
		printf("%s", getLexemeSVAL(tree));
	}
	else if (type == COMMA)
		printf(",");
	else if (type == OPEN_PAREN)
		printf("(");
	else if (type == CLOSE_PAREN)
		printf(")");
	else if (type == PLUS)
		printf("+");
	else if (type == MINUS)
		printf("-");
	else if (type == DIVIDE)
		printf("/");
	else if (type == ASSIGN)
		printf("=");
	else if (type == LESS_THAN)
		printf("<");
	else if (type == GREAT_THAN)
		printf(">");
	else if (type == COLON)
		printf(":");
	else if (type == SEMICOLON)
		printf(";");
	else if (type == DOT)
		printf(".");
	else if (type == OPEN_BRACE)
		printf("{");
	else if (type == CLOSE_BRACE)
		printf("}");
	else if (type == POUND)
		printf("#");
	else if (type == NOT)
		printf("!");
	else if (type == MOD)
		printf("%%");
	else if (type == OPEN_BRACK){
		printf("[");
		printIDList(cdr(tree));
		printf("]");
	}
	else if (type == CLOSE_BRACK)
		printf("]");
	else if (type == AMPERSAND)
		printf("&");
	else if (type == SINGLE_QUOTE)
		printf("\'");
	else if (type == FOR_SLASH)
		printf("\\");
	else if (type == VERTICAL_BAR)
		printf("|");
	else if (type == IF)
		printf("if");
	else if (type == ELSE)
		printf("else");
	else if (type == WHILE)
		printf("while");
	else if (type == FOR)
		printf("for");
	else if (type == STRUCT)
		printf("struct");
	else if (type == PRINT)
		printf("print");
	//... ID, PLUS, TIMES, ...
	else if (type == FUNCDEF){
		printFunction(tree);
		//printf("Gonna work on this in a second\n");
	}
	else if(type == IDList){
		printIDList(tree);
	}
	else if(type == statementList){
		printStatements(tree);
	}
	else if(type == PROGRAM){
		printProgram(tree);
	}
	else if(type == VARDEF){
		printVarDef(tree);
	}
	else if(type == RETURN){
		//printf("should've made it here\n");
		printReturn(tree);
	}
	//...
	else if(type == ENDofINPUT){
		printf("\nend of the program\n");
		exit(1);
	}
	else{
		printf("looking for type %s currently have %s\n", VARIABLE, getLexemeType(tree));
		printf("haven't implemented pp for this yet!\n");
	}
}

void printProgram(lexeme *tree){
	pp(car(tree)); //definition
	printf("\n");
	if(cdr(tree) != NULL){
		pp(cdr(tree)); // other programs
	}
}

void printVarDef(lexeme *tree){
	indent();
	printf("var ");
	pp(car(tree)); //variable
	if(cdr(tree) != NULL){
		printf(" = ");
		//pp(cdr(tree)); //optInit
		printExpression(cdr(tree));
	}
	printf(";");
}

void printExpression(lexeme *tree){
	//recursively prin left and right sides
	if(car(tree)) pp(car(tree));

	pp(tree);

	if(cdr(tree)) pp(cdr(tree));
}

void printFunction(lexeme *tree){
	printf("function ");
	pp(car(tree));
	printf("(");
	//printf("made it here\n");
	if(cadr(tree) != NULL) pp(cadr(tree));		// IDlist
	printf(")\n");
	pp(cddr(tree));		// block
}

void printStatements(lexeme *tree){
	printf("{\n");
	iLevel++;
	//lexeme *check = car(tree);
	while (tree != NULL)
	{
		//printf("mark\n");
		if(car(tree) == NULL) break;
		else pp(car(tree));
		printf("\n");
		tree = cdr(tree);
	}
	iLevel--;
	printf("}\n");
}

void printIDList(lexeme *tree){
	while (tree != NULL)
	{
		pp(car(tree));
		if (cdr(tree) != NULL)
			printf(", ");
		tree = cdr(tree);
	}
}

void printReturn(lexeme *tree){
	indent();
	printf("return");
	//pp(car(tree));
	if(car(tree) != NULL){
		printf(" ");
		printExpression(car(tree));
	}
	printf(";");
}

