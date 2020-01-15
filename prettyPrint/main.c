#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexeme.h"
#include "pretty.h"
#include "parser.h"


int main(int argc, char *argv[]){
	if(argc == 1){
		printf("not enough args!!\n");
		exit(1);
	}
	FILE *fp = fopen(argv[1], "r");
	//printf("beginning parse\n");
	lexeme *tree = parse(fp);
	//printf("parse done\n");
	printf("starting the prettiest print!\n\n");
	pp(tree);
	printf("print done look how pretty\n");
	fclose(fp);
	return 0;
}