#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lexeme lexeme;

lexeme *newLexemeInt(int x);
lexeme *newLexemeString(char *x);
lexeme *newLexemeFloat(double x);
lexeme *newLexemeVar(char *x);
lexeme *newLexeme(char *sym);


void displayLexeme(lexeme *d);
char readChar(FILE *f);
void skipWhiteSpace(FILE *f);
lexeme *lexVariableOrKeyword(FILE *f);
lexeme *lexNumber(FILE *f);
lexeme *lexString(FILE *f);
lexeme* lex(FILE *f);
void scanner(FILE *filename);