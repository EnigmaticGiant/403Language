#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eval.h"

int main(int argc, char **argv){
	if(argc == 1){
		printf("not enough args!!\n");
		exit(1);
	}
	FILE *fp = fopen(argv[1], "r");
	lexeme *env = create();
	lexeme *tree = parse(fp);
	//printf("parse done\n");
	//pp(tree);
	eval(tree, env);
	//printf("the first eval is done\n");
	//displayEnv(env);
	lexeme *call = cons(CALL, newLexemeVar("main"), NULL);
	eval(call, env);
	return 0;
}