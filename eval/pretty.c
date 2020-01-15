#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pretty.h"

int iLevel = 0;
int ifCheck = 0;

void indent(){
	for(int i = 0; i < iLevel; i++){
		printf("    ");
	}
}

void pp(lexeme *tree){
	char *type = getLexemeType(tree);
	//printf("the lexeme is currently ");
	//displayLexeme(tree);
	if (type == STRING)
		printf("\"%s\"", getLexemeSVAL(tree));
	else if (type == INTEGER)
		printf("%d", getLexemeIVAL(tree));
	else if (type == VARIABLE){
		//printf("at the variable now\n");
		//displayLexeme(tree);
		//indent();
		printf("%s", getLexemeSVAL(tree));
	}
	else if (type == COMMA)
		printf(",");
	else if (type == OPEN_PAREN)
		printf("(");
	else if (type == CLOSE_PAREN)
		printf(")");
	else if (type == PLUS){
		pp(car(tree));
		printf("+");
		pp(cdr(tree));
	}
	else if (type == MINUS){
		pp(car(tree));
		printf("-");
		pp(cdr(tree));
	}
	else if (type == DIVIDE){
		pp(car(tree));
		printf("/");
		pp(cdr(tree));
	}
	else if (type == ASSIGN){
		pp(car(tree));
		printf("=");
		pp(cdr(tree));
	}
	else if (type == LESS_THAN){
		pp(car(tree));
		printf("<");
		pp(cdr(tree));
	}
	else if (type == GREAT_THAN){
		pp(car(tree));
		printf(">");
		pp(cdr(tree));
	}
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
	else if(type == CALL){
		printCall(tree);
	}
	else if(type == IF){
		printIf(tree);
	}
	else if(type == ELSE){
		printElse(tree);
	}
	
	else if(type == WHILE){
		printWhile(tree);
	}
	
	else if(type == FOR){
		printFor(tree);
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
		pp(cdr(tree));
	}
	printf(";");
}
/*
void printExpression(lexeme *tree){
	//recursively prin left and right sides
	pp(tree);
}*/

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
	indent();
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
	indent();
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
		pp(car(tree));
	}
	printf(";");
}

void printCall(lexeme *tree){
	indent();
	pp(car(tree)); //function name
	printf("(");
	pp(cdr(tree)); //function arguments
	printf(");");
}

void printIf(lexeme *tree){
	if(ifCheck == 0) indent();
	else{
		printf(" ");
		ifCheck = 0;
	}
//	printf("made it here\n");
	printf("if(");
	pp(car(tree)); //expression conditional
	printf(")\n");
	pp(cddr(tree)); //block
	if(cadr(tree) != NULL){
		pp(cadr(tree));
	}
}

void printElse(lexeme *tree){
	indent();
	printf("else");
	if(car(tree) != NULL){
		//printf("mark\n");
		ifCheck = 1;
		pp(car(tree)); //else if scenario
	}
	else{
		printf("\n");
		pp(cdr(tree)); // block
	}
}

void printWhile(lexeme *tree){
	indent();
	printf("while(");
	pp(car(tree)); //expression conditional
	printf(")\n");
	pp(cdr(tree)); //block
}

void printFor(lexeme *tree){
	indent();
	printf("for(");
	pp(caar(tree)); // expression1
	printf(",");
	pp(cdar(tree)); // expression2
	printf(",");
	pp(cadr(tree)); //expression3
	printf(")\n");
	pp(cddr(tree)); //block

}