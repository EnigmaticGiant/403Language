#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "lexer.h"
#include "types.h"
#include "lexeme.h"

extern lexeme *token;

void unary(FILE *f){
	printf("unary\n");
	//////printf("the current lexeme is type %s\n", getLexemeType(token));
	if(check(INTEGER)){
		match(INTEGER, f);
	}
	else if(check(FLOAT)){
		match(FLOAT, f);
	}
	else if(check(STRING)){
		match(STRING, f);
	}
	else if(check(VARIABLE)){
		printf("unary variable is %s\n", getLexemeSVAL(token));
		match(VARIABLE, f);
		printf("the current type is %s\n", getLexemeType(token));
		if(check(OPEN_PAREN)){
			match(OPEN_PAREN, f);
			printf("about to get args\n");
			optExpressionList(f);
			match(CLOSE_PAREN, f);
		}
	}
	else if(check(OPEN_PAREN)){
		match(OPEN_PAREN, f);
		expression(f);
		match(CLOSE_PAREN, f);
	}
	else if(check(MINUS)){
		match(MINUS, f);
		unary(f);
	}
	else if(check(NOT)){
		match(NOT, f);
		unary(f);
	}
	else{
		match(OPEN_BRACK, f);
		optionalList(f);
		match(CLOSE_BRACK, f);
	}
}
void operator(FILE *f){
	printf("operator\n");
	if(check(PLUS)){
		match(PLUS, f);
	}
	else if(check(TIMES)){
		match(TIMES, f);
	}
	else if(check(MOD)){
		match(MOD, f);
	}
	else if(check(DIVIDE)){
		match(DIVIDE, f);
	}
	else if(check(MINUS)){
		match(MINUS, f);
	}
	else if(check(ASSIGN)){
		match(ASSIGN, f);
	}
	else if(check(DOT)){
		match(DOT, f);
	}
	else if(check(GREAT_THAN)){
		match(GREAT_THAN, f);
	}
	else{
		match(LESS_THAN, f);
	}
}
void optExpressionList(FILE *f){
	printf("optExpressionList\n");
	if(expressionListPending()){
		expressionList(f);
	}
}

void expressionList(FILE *f){
	expression(f);
	if(check(COMMA)){
		match(COMMA, f);
		expressionList(f);
	}
}

void expression(FILE *f){
	printf("expression\n");
	unary(f);
	if(operatorPending()){
		operator(f);
		if(expressionPending()){
			expression(f);
		}
		else{
			operator(f);
		}
	}
	/*else if(check(OPEN_PAREN)){
		printf("going to function call\n");
		functionCall(f);
	}*/
	else{
		if(check(OPEN_BRACK)){
			match(OPEN_BRACK, f);
			optionalList(f);
			match(CLOSE_BRACK, f);
		}
	}
}

void list(FILE *f){
	printf("list\n");
	if(itemPending()){
		item(f);
		if(check(COMMA)){
			match(COMMA, f);
			list(f);
		}
	}
}

void item(FILE *f){
	printf("item\n");
	unary(f);
}
void functionCall(FILE *f){
	printf("functionCall\n");
	if(check(VARIABLE)){
		match(VARIABLE, f);
		match(OPEN_PAREN, f);
		optionalList(f);
		match(CLOSE_PAREN, f);
	}
}
void optionalList(FILE *f){
	printf("optionalList\n");
	list(f);
}
void ifStatement(FILE *f){
	printf("ifStatement\n");
	match(IF, f);
	match(OPEN_PAREN, f);
	expression(f);
	match(CLOSE_PAREN, f);
	block(f);
	if(check(ELSE)){
		optElse(f);
	}
}

void block(FILE *f){
	printf("block\n");
	match(OPEN_BRACE, f);
	statements(f);
	match(CLOSE_BRACE, f);
}

void whileLoop(FILE *f){
	printf("whileLoop\n");
	match(WHILE, f);
	match(OPEN_PAREN, f);
	expression(f);
	match(CLOSE_PAREN, f);
	block(f);
}

void optElse(FILE *f){
	printf("optElse\n");
	match(ELSE, f);
	if(blockPending()){
		block(f);
	}
	else{
		ifStatement(f);
	}
}
void statements(FILE *f){
	printf("multiple statments\n");
	statement(f);
	if(statementsPending()){
		statements(f);
	}
	else return;
}
void statement(FILE *f){
	printf("statement\n");
	printf("the current lexeme is type %s\n", getLexemeType(token));
	if(expressionPending()){
		expression(f);
		endLine(f);
	}
	else if(ifStatementPending()){
		ifStatement(f);
	}
	else if(whileLoopPending()){
		whileLoop(f);
	}
	else if(returnPending()){
		returnFunct(f);
	}
	else if(varDefPending()){
			varDef(f);
	}
	else if(functionDefPending()){
		functionDef(f);
	}
	else if(check(PRINT)){
		print(f);
	}
	else{
		structDef(f);
	}
}
void varDef(FILE *f){
	printf("VarDef\n");
	match(VAR_TYPE,f);
	match(VARIABLE,f);
	optInit(f);
	endLine(f);
}
void optInit(FILE *f){
	printf("optInit\n");
	if(check(ASSIGN)){
		match(ASSIGN, f);
		expression(f);
	}
}
void functionDef(FILE *f){
	printf("function definition\n");
	match(FUNCTION, f);
	match(VARIABLE, f);
	match(OPEN_PAREN, f);
	if(parameterListPending()){
		parameterList(f);
	}
	match(CLOSE_PAREN, f);
	block(f);
}
void parameterList(FILE *f){
	printf("parameterList\n");
	match(VAR_TYPE,f);
	match(VARIABLE,f);
	if(check(COMMA)){
		match(COMMA, f);
		parameterList(f);
	}
}
void words(FILE *f){
	printf("words\n");
	if(check(WORD)){
		match(WORD, f);
		if(wordsPending()){
			words(f);
		}
	}
}
void structDef(FILE *f){
	printf("structure definition\n");
	//match(TYPEDEF, f);
	match(STRUCT, f);
	match(VARIABLE, f);
	block(f);
//	match(VARIABLE, f);
	endLine(f);
}
void structVar(FILE *f){
	printf("structure variable\n");
	varDef(f);
	if(varDefPending()){
		structVar(f);
	}
}


void endLine(FILE *f){
	printf("endLine\n");
	match(SEMICOLON, f);
}
void forLoop(FILE *f){
	printf("forLoop\n");
	match(FOR, f);
	match(OPEN_PAREN, f);
	expression(f);
	match(COMMA, f);
	expression(f);
	match(COMMA, f);
	expression(f);
	match(CLOSE_PAREN, f);
	block(f);
}

void print(FILE *f){
	printf("printing\n");
	match(PRINT, f);
	match(OPEN_PAREN, f);
	//match(QUOTE, f);
	//words(f);
	//match(QUOTE, f);
	unary(f);
	if(check(COMMA)){
		optPrint(f);
	}
	match(CLOSE_PAREN, f);
	endLine(f);
}
void optPrint(FILE *f){
	printf("optPrint\n");
	match(COMMA, f);
	unary(f);
	if(check(COMMA)){
		optPrint(f);
	}
}

void program(FILE *f){
	printf("In the program\n");
	definition(f);
	if(programPending()){
		program(f);
	}
}

void definition(FILE *f){
	printf("in the definition\n");
	if(structDefPending()){
		structDef(f);
	}
	else if(varDefPending()){
		varDef(f);
	}
	else{
		functionDef(f);
	}
}

void returnFunct(FILE *f){
	printf("returning\n");
	match(RETURN, f);
	if(expressionPending()){
		expression(f);
		endLine(f);
	}
	else{
		endLine(f);
	}
}

bool programPending(){
	printf("Program pending\n");
	return definitionPending();
}

bool definitionPending(){
	printf("definitionPending\n");
	return structDefPending() || varDefPending() || functionDefPending() || check(DIVIDE);
}

bool structDefPending(){
	printf("Testing the STRUCT definition\n");
	return check(STRUCT);
}

bool parameterListPending(){
	return check(VAR_TYPE);
}

bool varDefPending(){
	printf("Testing the Variable definition\n");
	return check(VAR_TYPE);
}

bool functionDefPending(){
	printf("testing the Function definition\n");
	return check(FUNCTION);
}

bool expressionPending(){
	printf("expressionPending\n");
	return unaryPending(); 
}

bool unaryPending(){
	printf("unaryPending\n");
	return check(INTEGER) || check(FLOAT) || check(STRING) || check(VARIABLE) || check(OPEN_PAREN) || check(MINUS) || check(NOT);
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

bool wordsPending(){
	return check(WORD);
}

bool returnPending(){
	return check(RETURN);
}

int parse(FILE *f){
	startParse(f);
	program(f);
	return getResult();
}