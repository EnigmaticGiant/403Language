#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"


int main(){
	lexeme *env = create();
		//displayEnv(env);

	insert(newLexeme("x"), newLexeme("5"), env);
	displayEnv(env);

	insert(newLexeme("y"), newLexeme("4.4"), env);
	//printf("second insert sucessful\n");
	//env = extend(newLexeme("Z"), newLexeme("goodbye"), env);
	//env = extend(newLexeme("alpha"), newLexeme("gamma phi"), env);
	displayEnv(env);
	/*printf("attempting lookup of Z\n");
	lexeme *result = lookup(newLexeme("Z"), env);
	printf("The lookup of Z is %s\n", getLexemeType(result));
	printf("Updating Z to say \"hello\"\n");
	update(newLexeme("Z"), env, newLexeme("hello"));
	displayEnv(env);
	*/return 0;
}