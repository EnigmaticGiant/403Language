#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>
#include "types.h"
#include "lexeme.h"

typedef struct lexeme{
	char* type;
	int stage;
	char* string;
	int integer;
	double real;
}lexeme;

lexeme *newLexemeInt(int x){
	lexeme *y = malloc(sizeof(lexeme));
	assert(y != 0);
	y->type = "int";
	//setLexemeType(y, "INTEGER");
	y->integer = x;
	y->stage = 1;
	return y;
}

lexeme *newLexemeString(char *x){
	lexeme *y = malloc(sizeof(lexeme));
	assert(y != 0);
	y->type = "string";
	y->string = x;
	y->stage = 2;
	return y;
}

lexeme *newLexemeFloat(double x){
	lexeme *y = malloc(sizeof(lexeme));
	assert(y != 0);
	y->type = "double";
	y->real = x;
	y->stage = 3;
	return y;
}

lexeme *newLexemeVar(char *x){
	lexeme *y = malloc(sizeof(lexeme));
	assert(y != 0);
	y->type = "VARIABLE";
	y->string = x;
	y->stage = 2;
	return y;
}

lexeme *newLexeme(char *sym){
	lexeme *x = malloc(sizeof(lexeme));
	assert(x != 0);
	x->type = sym;
	return x;
}

void displayLexeme(lexeme *d){
	fprintf(stdout, "%s", d->type);
	if(d->stage == 1) fprintf(stdout, " %d", d->integer);
	else if(d->stage == 2) fprintf(stdout, " %s", d->string);
	else if(d->stage == 3) fprintf(stdout, " %f", d->real);
	//else exit(-1);
	fprintf(stdout, "\n");
}

char *getLexemeType(lexeme *t){
	//printf("the type of the lexeme is ");
	//displayLexeme(t);
	//printf("\n");

	return t->type;
}

char *getLexemeSVAL(lexeme *t){
	return t->string;
}