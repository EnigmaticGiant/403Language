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

extern int getLexemeIVAL(lexeme *);

extern double getLexemeRVAL(lexeme *);

extern void setLexemeAVALsize(lexeme *, int);

extern lexeme *getLexemeAVAL(lexeme *, int);

extern void setLexemeAVAL(lexeme *, int, lexeme *);

extern lexeme *cdr(lexeme *);

extern lexeme *car(lexeme *);

extern void setcdr(lexeme *, lexeme *);

extern void setcar(lexeme *, lexeme *);

extern lexeme *cons(char *, lexeme *, lexeme *);

extern lexeme *cadr(lexeme *);

extern lexeme *cddr(lexeme *);

extern lexeme *caar(lexeme *);

extern lexeme *cdar(lexeme *);

#endif