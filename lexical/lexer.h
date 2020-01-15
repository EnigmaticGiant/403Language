#include <stdio.h>
#include "lexeme.h"
#include "types.h"


char readChar(FILE *f);

void skipWhiteSpace(FILE *f);

lexeme *lexVariableOrKeyword(FILE *f);

lexeme *lexNumber(FILE *f);

lexeme *lexString(FILE *f);

lexeme* lex(FILE *f);