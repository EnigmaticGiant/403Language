#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "types.h"
#include "lexer.h"

int boolean = 0;
int LineNumber = 1;

char readChar(FILE *f){
	int ch = fgetc(f);
	if(ch == '\n') ++LineNumber;
	return (char) ch;

}

void skipWhiteSpace(FILE *f)
        {
    char ch = readChar(f);
    while (isspace(ch)){
    	//printf("theres a space here\n");
        ch = readChar(f);

        // the character that got us out of the loop was NOT whitespace
        // so we need to push it back so it can be read again.
    }
    //printf("skip is over\n");
    //pushback(ch);
    ungetc(ch, f);
}

lexeme *lexVariableOrKeyword(FILE *f){
	//printf("currently deciding between variable or keyword\n");
        char ch;
        int length = 32;
        int index = 0;
        char *token = malloc(sizeof(char) * length + 1);
        ch = readChar(f);

        while (!feof(f) && (isalpha(ch) || isdigit(ch))){
        	if (index == length){
       			token = realloc(token,sizeof(char) * length * 2 + 1);
       			length *= 2;
       		}
            token[index++] = ch; //grow the token string
            token[index] = '\0';
            ch = readChar(f);
            }
        //printf("the string is now %s\n", token);
        //push back the character that got us out of the loop
        //it may be some kind of punctuation

        //pushback(ch);
        ungetc(ch, f);
        //token holds either a variable or a keyword, so figure it out
        //printf("comapring %s and %s\n", token, IF);
        if (strcmp(token, IF) == 0) return newLexeme("IF");
        else if (strcmp(token,ELSE) == 0) return newLexeme("ELSE");
        else if (strcmp(token,WHILE) == 0) return newLexeme("WHILE");
        else if (strcmp(token,FOR) == 0) return newLexeme("FOR");
        else if (strcmp(token,INTEGER) == 0) return newLexeme("INTEGER_TYPE");
        else if (strcmp(token,CHAR) == 0) return newLexeme("CHARACTER_TYPE");
        else if (strcmp(token,FLOAT) == 0) return newLexeme("FLOAT_TYPE");
        else if (strcmp(token, INCLUDE) == 0) return newLexeme("INCLUDE");
        else if (strcmp(token, VOID) == 0) return newLexeme("VOID_TYPE");
        else if (strcmp(token, TYPEDEF) == 0) return newLexeme("TYPE_DEF");
        else if (strcmp(token, STRUCT) == 0) return newLexeme("STRUCT");

        //... //more keyword testing here
        else{ //must be a variable!
        	//printf("doesn't match a keyword\n");
            return newLexemeVar(token);
        }
}

lexeme *lexNumber(FILE *f){
	int real = 0;
	int length = 32;
	int index = 0;
	char *token = malloc(sizeof(char) * length + 1); 
	char ch;
	ch = readChar(f);
	while(!feof(f) && (isdigit(ch) || ch == '.')){
		//printf("still reading number\n");
		if (index == length){
       		token = realloc(token,sizeof(char) * length * 2 + 1);
       		length *= 2;
       	}
		token[index++] = ch; //grow the token string
        token[index] = '\0';
		if(ch == '.' && real == 1){
			//return newLexeme("BAD_NUMBER", buffer);
			fprintf(stdout, "BAD NUMBER AT LINE %d, ABORT!\n", LineNumber);
			exit(-1);
		}
		if(ch == '.') real = 1;
		ch = readChar(f);
	}
	//pushback(ch);
	ungetc(ch, f);
	//printf("testing before conversion: the number in string form is %s\n", token);
	if (real == 1){
		return newLexemeFloat(atof(token));
	}
	else{
		//printf("this in an integer\n");
		return newLexemeInt(atoi(token));
	}
}

lexeme *lexString(FILE *f){
	int length = 32;
	int index = 0;
	char *token = malloc(sizeof(char) * length + 1); 
	char ch;
	ch = readChar(f);
	//printf("made it here\n");
	//printf("the character is %c\n", ch);
	while(!feof(f) &&  ch != '\"'){
		//printf("still reading string\n");
		if (index == length){
       		token = realloc(token,sizeof(char) * length * 2 + 1);
       		length *= 2;
       	}
		token[index++] = ch; //grow the token string
        token[index] = '\0';
		ch = readChar(f);
	}
	//pushback(ch);
	//ungetc(ch, f);
	//printf("testing before conversion: the number in string form is %s\n", token);
	return newLexemeString(token);
}

lexeme* lex(FILE *f) { 
    //printf("starting the lex\n");
    char ch;
    skipWhiteSpace(f);  //why do we skip whitespace?

    ch = readChar(f); 
    //printf("Just got the character\n");
    //printf("The character is %c\n", ch);
    if (feof(f)){
    	//printf("the end of the input\n");
    	return newLexeme("ENDofINPUT"); 
    }
    switch(ch){ 
        // single character tokens 

        case '(': return newLexeme("OPEN_PAREN"); 
        case ')': return newLexeme("CLOSE_PAREN"); 
        case ',': return newLexeme("COMMA"); 
        case '+': return newLexeme("PLUS"); //what about ++ and += ?
        case '*': return newLexeme("TIMES"); 
        case '-': return newLexeme("MINUS"); 
        case '/': return newLexeme("DIVIDES"); 
        case '<': return newLexeme("LESS_THAN"); 
        case '>': return newLexeme("GREATER_THAN"); 
        case '=': return newLexeme("ASSIGN"); 
        case ':': return newLexeme("COLON");
        case ';': return newLexeme("SEMICOLON"); 
        case '.': return newLexeme("DOT"); 
        case '{': return newLexeme("OPEN_BRACE");
        case '}': return newLexeme("CLOSE_BRACE");
        case '#': return newLexeme("POUND");
        case '!': return newLexeme("NOT");
        case '%': return newLexeme("MOD");
        case '[': return newLexeme("OPEN_BRACK");
        case ']': return newLexeme("CLOSE_BRACK");
        case '&': return newLexeme("AMPERSAND");
        case '\'': return newLexeme("SINGLE_QUOTE");
        case '\\': return newLexeme("FOR_SLASH");
        case '|': return newLexeme("VERTICAL_BAR");
        //add any other cases here

        default: 
            // multi-character tokens (only numbers, 
            // variables/keywords, and strings) 
            if (isdigit(ch)) { 
                //pushback(ch);
                ungetc(ch, f); 
                return lexNumber(f); 
            } 
            else if (isalpha(ch)) { 
                //pushback(ch);
                ungetc(ch, f); 
                return lexVariableOrKeyword(f);
            } 
            else if (ch == '\"') { 
                return lexString(f); 
            } 
            else{
                //return newLexeme("UNKNOWN", ch); 
                fprintf(stdout, "unknown lexical at line %d, abort!\n", LineNumber);
                exit(-1);
            }
    }
    return newLexeme("JUNK"); 
}