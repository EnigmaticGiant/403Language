#ifndef __LEXEME_INCLUDED__
#define __LEXEME_INCLUDED__

#include <stdio.h>

typedef struct lexeme lexeme;

extern lexeme *newLexemeInt(int);

extern lexeme *newLexemeString(char *);

extern lexeme *newLexemeFloat(double);

extern lexeme *newLexemeVar(char *);

extern lexeme *newLexeme(char *);

extern void displayLexeme(lexeme *);

extern char *getLexemeType(lexeme *);

extern char *getLexemeSVAL(lexeme *);

extern lexeme *cdr(lexeme *t);

extern lexeme *car(lexeme *t);

extern void setcdr(lexeme *t, lexeme *new);

extern void setcar(lexeme *t, lexeme *new);

extern lexeme *cons(char *c, lexeme *l, lexeme *r);

extern lexeme *cadr(lexeme *);

#endif