#include <stdio.h>
#include "lexeme.h"
#include "types.h"


extern char readChar(FILE *f);

extern void skipWhiteSpace(FILE *f);

extern lexeme *lexVariableOrKeyword(FILE *f);

extern lexeme *lexNumber(FILE *f);

extern lexeme *lexString(FILE *f);

extern lexeme* lex(FILE *f);

extern bool check(char *type/*, lexeme **/);
  
extern void advance(FILE */*, lexeme **/);
  
extern void match(char *type, FILE */*, lexeme **/);
  
extern void matchNoAdvance(char *type/*, lexeme **/);

extern void startParse(FILE *);

extern int getResult();