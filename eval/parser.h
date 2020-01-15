#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"
#include "lexeme.h"



extern lexeme *unary(FILE *);

extern lexeme *operator(FILE *);

extern lexeme *optExpressionList(FILE *);

extern lexeme *expression(FILE *);

extern lexeme *expression2(FILE *);

extern lexeme *expression3(FILE *);

extern lexeme *expressionList(FILE *);

extern lexeme *conditional(FILE *);

extern lexeme *list(FILE *);

extern lexeme *item(FILE *);

extern lexeme *functionCall(FILE *);

extern lexeme *optionalList(FILE *);

extern lexeme *ifStatement(FILE *);

extern lexeme *optElse(FILE *);

extern lexeme *block(FILE *);

extern lexeme *whileLoop(FILE *);

extern lexeme *statements(FILE *);

extern lexeme *statement(FILE *);

extern lexeme *varDef(FILE *);

extern lexeme *optInit(FILE *);

extern lexeme *functionDef(FILE *);

extern lexeme *parameterList(FILE *);

extern lexeme *comments(FILE *);

extern lexeme *words(FILE *);

extern lexeme *structDef(FILE *);

extern lexeme *structVar(FILE *);

extern lexeme *endLine(FILE *);

extern lexeme *forLoop(FILE *);

extern lexeme *structAtt(FILE *);

extern lexeme *print(FILE *);

extern lexeme *optPrint(FILE *);

extern lexeme *program(FILE *);

extern lexeme *definition(FILE *);

extern lexeme *returnFunct(FILE *);

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

extern bool forLoopPending();

extern bool wordsPending();

extern bool returnPending();

extern bool parameterListPending();

extern bool expressionListPending();

extern lexeme *parse(FILE *);