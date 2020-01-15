#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "lexer.h"
#include "types.h"
#include "lexeme.h"
#include "environment.h"

extern lexeme *token;

lexeme *unary(FILE *f){
	//printf("unary\n");
	////////printf("the current lexeme is type %s\n", getLexemeType(token));
	lexeme *tree;
	if(check(INTEGER)){
		return match(INTEGER, f);
	}
	else if(check(FLOAT)){
		return match(FLOAT, f);
	}
	else if(check(STRING)){
		return match(STRING, f);
	}
	else if(check(VARIABLE)){
		//printf("unary variable is %s\n", getLexemeSVAL(token));
		lexeme *v;
		v = match(VARIABLE, f);
		///displayLexeme(v);
		//printf("the current type is %s\n", getLexemeType(token));
		if(check(OPEN_PAREN)){
			match(OPEN_PAREN, f);
			////printf("about to get args\n");
			tree = optExpressionList(f);
			//displayLexeme(tree);
			match(CLOSE_PAREN, f);
			return cons(CALL, v, tree);
		}
		else{
			tree = NULL;
			////printf("\n im here for some reason?!\n");
			//return cons(OPEN_PAREN, v, tree);
			return v;
		}
	}
	else if(check(LAMBDA)){
		//printf("in the lambda tree\n");
		lexeme *s;
		match(LAMBDA, f);
		match(OPEN_PAREN, f);
		if(parameterListPending()){
			//printf("there is a parameterList\n");
			tree = parameterList(f);
		}
		else{
			//printf("no parameterList\n");
			tree = NULL;
		}
		match(CLOSE_PAREN, f);
		match(OPEN_BRACE, f);
		//printf("calling statments\n");
		s = statements(f);
		//printf("done with statments\n");
		match(CLOSE_BRACE, f);
		//endLine(f);
		return cons(LAMBDA, NULL, cons(JUNK, tree, s));
	}
	else if(check(OPEN_PAREN)){
		match(OPEN_PAREN, f);
		tree = expression(f);
		match(CLOSE_PAREN, f);
		return cons(OPEN_PAREN, NULL, tree);
	}
	else if(check(MINUS)){
		match(MINUS, f);
		tree = unary(f);
		return cons(UMINUS, NULL, tree);
	}
	else if(check(NOT)){
		match(NOT, f);
		tree = unary(f);
		return cons(NOT, NULL, tree);
	}
	else{
		match(OPEN_BRACK, f);
		tree = optionalList(f);
		match(CLOSE_BRACK, f);
		return cons(OPEN_BRACK, NULL, tree);
	}
}
lexeme *operator(FILE *f){
	//printf("operator\n");
	lexeme *o;
	if(check(PLUS)){
		o = match(PLUS, f);
	}
	else if(check(TIMES)){
		o = match(TIMES, f);
	}
	else if(check(MOD)){
		o = match(MOD, f);
	}
	else if(check(DIVIDE)){
		o = match(DIVIDE, f);
	}
	else if(check(MINUS)){
		o = match(MINUS, f);
	}
	else if(check(ASSIGN)){
		o = match(ASSIGN, f);
	}
	else if(check(DOT)){
		o = match(DOT, f);
	}
	else if(check(GREAT_THAN)){
		o = match(GREAT_THAN, f);
	}
	else{
		o = match(LESS_THAN, f);
	}
	return o;
}
lexeme *optExpressionList(FILE *f){
	//printf("optExpressionList\n");
	lexeme *e;
	if(expressionListPending()){
		e = expressionList(f);
	}
	else{
		e = NULL;
	}
	return e;
}

lexeme *expressionList(FILE *f){
	lexeme *e, *l;
	e = expression(f);
	if(check(COMMA)){
		match(COMMA, f);
		l = expressionList(f);
	}
	else{
		////printf("no more list\n");
		l = NULL;
	}
	return cons(IDList, e, l);
}

lexeme *expression(FILE *f){
	//printf("expression\n");
	lexeme *u, *e;
	u = expression2(f);
	if(check(ASSIGN)){
		match(ASSIGN, f);
		e = expression(f);
		return cons(ASSIGN, u, e);
	}
	else{
		return u;
	}
}

lexeme *expression2(FILE *f){
	//printf("expression2\n");
	lexeme *u, *o, *e;
	u = expression3(f);
	////printf("mark\n");
	if(operatorPending()){
		o = operator(f);
		e = expression2(f);
		return cons(getLexemeType(o), u, e);
	}
	else{
		return u;
	}
}

lexeme *expression3(FILE *f){
	//printf("expression3\n");
	lexeme *u, *e;
	u = unary(f);
	while(check(DOT)){
		match(DOT, f);
		e = unary(f);
		u = cons(DOT, u, e);
	}
	////printf("mark\n");
	if(cdr(u) && getLexemeType(cdr(u)) == CALL){
		//printf("a weird rotate, maybe...\n");
		return cons(CALL, cons(DOT, car(u), cadr(u)), cddr(u));
	}
	else{
		return u;
	}
}


lexeme *list(FILE *f){
	//printf("list\n");
	lexeme *i, *l;
	if(itemPending()){
		i = item(f);
		if(check(COMMA)){
			match(COMMA, f);
			l = list(f);
		}
		else{
			l = NULL;
		}
	}
	else{
		i = NULL;
	}
	return cons(IDList, i, l);
}

lexeme *item(FILE *f){
	//printf("item\n");
	lexeme *u = unary(f);
	return u;
}
/*
lexeme *functionCall(FILE *f){
	//printf("functionCall\n");
	lexeme *i, *a;
	//if(check(VARIABLE)){
		i = match(VARIABLE, f);
		match(OPEN_PAREN, f);
		a = optionalList(f);
		match(CLOSE_PAREN, f);
		return cons(CALL, i, a);
	//}
}
*/
lexeme *optionalList(FILE *f){
	//printf("optionalList\n");
	lexeme *l = list(f);
	return l;
}
lexeme *ifStatement(FILE *f){
	//printf("ifStatement\n");
	lexeme *e, *b, *o;
	match(IF, f);
	match(OPEN_PAREN, f);
	e = expression(f);
	match(CLOSE_PAREN, f);
	b = block(f);
	if(check(ELSE)){
		o = optElse(f);
	}
	else{
		o = NULL;
	}
	return cons(IF, e, cons(JUNK, o, b));
}

lexeme *block(FILE *f){
	//printf("block\n");
	lexeme *s;
	match(OPEN_BRACE, f);
	s = statements(f);
	match(CLOSE_BRACE, f);
	return s;
}

lexeme *whileLoop(FILE *f){
	//printf("whileLoop\n");
	lexeme *e, *b;
	match(WHILE, f);
	match(OPEN_PAREN, f);
	e = expression(f);
	match(CLOSE_PAREN, f);
	b = block(f);
	return cons(WHILE, e, b);
}

lexeme *optElse(FILE *f){
	//printf("optElse\n");
	lexeme *b, *i;
	match(ELSE, f);
	if(ifStatementPending()){
		i = ifStatement(f);
		b = NULL;
	}
	else{
		i = NULL;
		b = block(f);
	}
	return cons(ELSE, i, b);
}
lexeme *statements(FILE *f){
	//printf("multiple statments\n");
	lexeme *s1, *s2;
	s1 = statement(f);
	if(statementsPending()){
		//printf("it never ends...\n");
		s2 = statements(f);
	}
	else{
		s2 = NULL;
	}
	//printf("end of statements\n");
	return cons(statementList, s1, s2);
}
lexeme *statement(FILE *f){
	//printf("statement\n");
	//printf("the current lexeme is type %s\n", getLexemeType(token));
	lexeme *s;
	if(expressionPending()){
		s = expression(f);
		endLine(f);
	}
	else if(ifStatementPending()){
		s = ifStatement(f);
	}
	else if(whileLoopPending()){
		s = whileLoop(f);
	}
	else if(returnPending()){
		s = returnFunct(f);
	}
	else if(varDefPending()){
		s = varDef(f);
	}
	else if(functionDefPending()){
		s = functionDef(f);
	}
	else if(check(PRINT)){
		s = print(f);
	}
	else if(structDefPending()){
		s = structDef(f);
	}
	else if(forLoopPending()){
		s = forLoop(f);
	}
	else{
		////printf("nothing\n");
		s = NULL;
	}
	return s;
}
lexeme *varDef(FILE *f){
	//printf("VarDef\n");
	lexeme *i, *e;
	match(VAR_TYPE,f);
	////////printf("mark1\n");
	i = match(VARIABLE,f);
	////////printf("mark2\n");
	e = optInit(f);
	//endLine(f);
	match(SEMICOLON, f);
	return cons(VARDEF, i, e);
}
lexeme *optInit(FILE *f){
	//printf("optInit\n");
	lexeme *e;
	//if(check(ASSIGN)){
		match(ASSIGN, f);
		e = expression(f);
	//}
	//else{
	//	e = NULL;
	//}
	return e;
}
lexeme *functionDef(FILE *f){
	//printf("function definition\n");
	lexeme *v, *p, *b;
	match(FUNCTION, f);
	v = match(VARIABLE, f);
	match(OPEN_PAREN, f);
	if(parameterListPending()){
		p = parameterList(f);
	}
	else{
		//printf("\n this shouldn't be here\n");
		p = NULL;
	}
	match(CLOSE_PAREN, f);
	b = block(f);
	return cons(FUNCDEF, v, cons(JUNK, p, b));
}
lexeme *parameterList(FILE *f){
	//printf("parameterList\n");
	lexeme *i, *p;
	match(VAR_TYPE,f);
	i = match(VARIABLE,f);
	if(check(COMMA)){
		match(COMMA, f);
		p = parameterList(f);
	}
	else{
		p = NULL;
	}
	return cons(IDList, i, p);
}
lexeme *structDef(FILE *f){
	//printf("structure definition\n");
	//match(TYPEDEF, f);
	lexeme *s, *b;
	match(STRUCT, f);
	s = match(VARIABLE, f);
	b = block(f);
//	match(VARIABLE, f);
	endLine(f);
	return cons(STRUCT, s, b);
}


lexeme *endLine(FILE *f){
	//printf("endLine\n");
	match(SEMICOLON, f);
	return cons(SEMICOLON, NULL, NULL);
}
lexeme *forLoop(FILE *f){
	//printf("forLoop\n");
	lexeme *e1, *e2, *e3, *b;
	match(FOR, f);
	match(OPEN_PAREN, f);
	e1 = expression(f);
	match(COMMA, f);
	e2 = expression(f);
	match(COMMA, f);
	e3 = expression(f);
	match(CLOSE_PAREN, f);
	b = block(f);
	return cons(FOR, cons(JUNK, e1, e2), cons(JUNK, e3, b));
}

lexeme *print(FILE *f){
	//printf("printing\n");
	lexeme *u, *o;
	match(PRINT, f);
	match(OPEN_PAREN, f);
	u = unary(f);
	if(check(COMMA)){
		o = optPrint(f);
	}
	else{
		o = NULL;
	}
	match(CLOSE_PAREN, f);
	endLine(f);
	return cons(PRINT, u, o);
}
lexeme *optPrint(FILE *f){
	//printf("optPrint\n");
	lexeme *u, *o;
	match(COMMA, f);
	u = unary(f);
	if(check(COMMA)){
		o = optPrint(f);
	}
	else{
		o = NULL;
	}
	return cons(OPTPRINT, u, o);
}

lexeme *program(FILE *f){
	//printf("In the program\n");
	lexeme *d, *p;
	d = definition(f);
	if(programPending()){
		p = program(f);
	}
	else{
		p = NULL;
	}
	return cons(PROGRAM, d, p);
}

lexeme *definition(FILE *f){
	//printf("in the definition\n");
	lexeme *d;
	if(structDefPending()){
		d = structDef(f);
	}
	else if(varDefPending()){
		d = varDef(f);
	}
	else{
		d = functionDef(f);
	}
	return d;
}

lexeme *returnFunct(FILE *f){
	//printf("returning\n");
	lexeme *e;
	match(RETURN, f);
	if(expressionPending()){
		e = expression(f);
		endLine(f);
	}
	else{
		e = NULL;
		endLine(f);
	}
	return cons(RETURN, e, NULL);
}

bool programPending(){
	//printf("Program pending\n");
	return definitionPending();
}

bool definitionPending(){
	//printf("definitionPending\n");
	return structDefPending() || varDefPending() || functionDefPending();
}

bool structDefPending(){
	//printf("Testing the STRUCT definition\n");
	return check(STRUCT);
}

bool parameterListPending(){
	return check(VAR_TYPE);
}

bool varDefPending(){
	//printf("Testing the Variable definition\n");
	return check(VAR_TYPE);
}

bool functionDefPending(){
	//printf("testing the Function definition\n");
	return check(FUNCTION);
}

bool expressionPending(){
	//printf("expressionPending\n");
	return unaryPending(); 
}

bool unaryPending(){
	//printf("unaryPending\n");
	return check(INTEGER) || check(FLOAT) || check(STRING) || check(VARIABLE) || check(LAMBDA) || check(OPEN_PAREN) || check(MINUS) || check(NOT);
}

bool operatorPending(){
	return check(PLUS) || check(TIMES) || check(MOD) || check(DIVIDE) || check(MINUS) 
			|| check(ASSIGN) || check(DOT) || check(LESS_THAN) || check(GREAT_THAN);
}

bool itemPending(){
	return unaryPending();
}

bool expressionListPending(){
	return expressionPending();
}

bool blockPending(){
	return check(OPEN_BRACE);
}

bool statementsPending(){
	return expressionPending() || ifStatementPending() ||
			 whileLoopPending() || returnPending() || functionDefPending() || structDefPending() || varDefPending();
}

bool ifStatementPending(){
	return check(IF);
}

bool whileLoopPending(){
	return check(WHILE);
}

bool forLoopPending(){
	return check(FOR);
}

bool returnPending(){
	return check(RETURN);
}

lexeme *parse(FILE *f){
	startParse(f);
	lexeme *p = program(f);
	return p;
}