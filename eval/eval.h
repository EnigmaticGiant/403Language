#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lexeme.h"
#include "types.h"
#include "environment.h"
#include "parser.h"
#include "pretty.h"

extern lexeme *eval(lexeme *, lexeme *);
extern lexeme *evalProgram(lexeme *, lexeme *);
extern lexeme *evalFuncDef(lexeme *, lexeme *);
extern lexeme *evalVarDef(lexeme *, lexeme *);
extern lexeme *getVarVal(lexeme *, lexeme *);
extern lexeme *evalSimpleOp(lexeme *, lexeme *);
extern lexeme *evalPlus(lexeme *, lexeme *);
extern lexeme *evalMinus(lexeme *, lexeme *);
extern lexeme *evalTimes(lexeme *, lexeme *);
extern lexeme *evalDivide(lexeme *, lexeme *);
extern lexeme *evalMod(lexeme *, lexeme *);
extern lexeme *evalAssign(lexeme *, lexeme *);
extern lexeme *evalBlock(lexeme *, lexeme *);
extern lexeme *evalDot(lexeme *, lexeme *);
extern lexeme *evalCall(lexeme *, lexeme *);
extern void evalPrintln(lexeme *);
extern lexeme *evalIf(lexeme *, lexeme *);
extern lexeme *evalElse(lexeme *, lexeme *);
extern lexeme *evalGreatThan(lexeme *, lexeme *);
extern lexeme *evalLessThan(lexeme *, lexeme *);
extern lexeme *evalLambda(lexeme *, lexeme *);
extern lexeme *evalWhile(lexeme *, lexeme *);
extern lexeme *evalNewArray(lexeme *);
extern lexeme *evalGetArray(lexeme *);
extern lexeme *evalSetArray(lexeme *);