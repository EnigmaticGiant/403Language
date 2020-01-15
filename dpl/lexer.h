#include <stdio.h>
#include "lexeme.h"
#include "types.h"


extern char readChar(FILE *f);

extern void skipWhiteSpace(FILE *f);

extern lexeme *lexVariableOrKeyword(FILE *f);

extern lexeme *lexNumber(FILE *f);

extern lexeme *lexString(FILE *f);

extern lexeme* lex(FILE *f);

extern bool check(char *type);
  
extern void advance(FILE *);
  
extern lexeme *match(char *type, FILE *);
  
extern void matchNoAdvance(char *type);

extern void startParse(FILE *);

extern int getResult();