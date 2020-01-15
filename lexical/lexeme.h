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

#endif