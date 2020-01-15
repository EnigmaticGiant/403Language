#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"
#include "lexeme.h"



extern void unary(FILE *);

extern void operator(FILE *);

extern void optExpressionList(FILE *);

extern void expression(FILE *);

extern void expressionList(FILE *);

extern void conditional(FILE *);

extern void list(FILE *);

extern void item(FILE *);

extern void functionCall(FILE *);

extern void optionalList(FILE *);

extern void ifStatement(FILE *);

extern void optElse(FILE *);

extern void block(FILE *);

extern void whileLoop(FILE *);

extern void statements(FILE *);

extern void statement(FILE *);

extern void varDef(FILE *);

extern void optInit(FILE *);

extern void functionDef(FILE *);

extern void parameterList(FILE *);

extern void comments(FILE *);

extern void words(FILE *);

extern void structDef(FILE *);

extern void structVar(FILE *);

extern void endLine(FILE *);

extern void forLoop(FILE *);

extern void structAtt(FILE *);

extern void print(FILE *);

extern void optPrint(FILE *);

extern void program(FILE *);

extern void definition(FILE *);

extern void returnFunct(FILE *);

extern bool programPending();

extern bool definitionPending();

extern bool structDefPending();

extern bool varDefPending();

extern bool functionDefPending();

extern bool expressionPending();

extern bool unaryPending();

extern bool structAttPending();

extern bool operatorPending();

extern bool itemPending();

extern bool blockPending();

extern bool statementsPending();

extern bool ifStatementPending();

extern bool whileLoopPending();

extern bool wordsPending();

extern bool returnPending();

extern bool parameterListPending();

extern bool expressionListPending();

extern int parse(FILE *);