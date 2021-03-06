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
	lexeme **aval;
	lexeme *(*fval)(lexeme *);
	lexeme *left;
	lexeme *right;
}lexeme;

lexeme *newLexemeInt(int x){
	lexeme *y = malloc(sizeof(lexeme));
	assert(y != 0);
	y->type = INTEGER;
	//setLexemeType(y, "INTEGER");
	y->integer = x;
	y->stage = 1;
	return y;
}

lexeme *newLexemeString(char *x){
	lexeme *y = malloc(sizeof(lexeme));
	assert(y != 0);
	y->type = STRING;
	y->string = x;
	y->stage = 2;
	return y;
}

lexeme *newLexemeFloat(double x){
	lexeme *y = malloc(sizeof(lexeme));
	assert(y != 0);
	y->type = FLOAT;
	y->real = x;
	y->stage = 3;
	return y;
}

lexeme *newLexemeVar(char *x){
	lexeme *y = malloc(sizeof(lexeme));
	assert(y != 0);
	y->type = VARIABLE;
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
	//fprintf(stdout, "%s", d->type);
	if(d->stage == 1) fprintf(stdout, "%d", d->integer);
	else if(d->stage == 2) fprintf(stdout, "%s", d->string);
	else if(d->stage == 3) fprintf(stdout, "%f", d->real);
	//else exit(-1);
	//fprintf(stdout, "\n");
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

int getLexemeIVAL(lexeme *t){
	return t->integer;
}

double getLexemeRVAL(lexeme *t){
	return t->real;
}

void setLexemeAVALsize(lexeme *t, int size){
	t->aval = malloc(sizeof(struct lexeme *) * size);
}

lexeme *getLexemeAVAL(lexeme *t, int index){
	return t->aval[index];
}

void setLexemeAVAL(lexeme *t, int index, lexeme *value){
	t->aval[index] = value;
}

lexeme *cdr(lexeme *t){
	return t->right;
}

lexeme *car(lexeme *t){
	return t->left;
}

void setcdr(lexeme *t, lexeme *new){
	t->right = new;
}

void setcar(lexeme *t, lexeme *new){
	t->left = new;
}

lexeme *cons(char *c, lexeme *l, lexeme *r){
	lexeme *y = newLexeme(c);
	//y->type = c;
	y->left = l;
	y->right = r;
	return y;
}

lexeme *cadr(lexeme *t){
	return car(cdr(t));
}

lexeme *cddr(lexeme *t){
	return cdr(cdr(t));
}

lexeme *caar(lexeme *t){
	return car(car(t));
}

lexeme *cdar(lexeme *t){
	return cdr(car(t));
}