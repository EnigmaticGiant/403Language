#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "lexeme.h"
#include "lexer.h"
#include "parser.h"

extern void pp(lexeme *);
extern void printProgram(lexeme *);
extern void printVarDef(lexeme *);
extern void printFunction(lexeme *);
//extern void printExpression(lexeme *);
extern void printIDList(lexeme *);
extern void printStatements(lexeme *);
extern void printReturn(lexeme *);
extern void printCall(lexeme *);
extern void printIf(lexeme *);
extern void printElse(lexeme *);
extern void printWhile(lexeme *);
extern void printFor(lexeme *);