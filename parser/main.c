#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"


int main(int argc, char *argv[]){
	FILE *fp = fopen(argv[1], "r");
	if(argc == 1){
		fprintf(stderr, "no file to open\n");
		exit(-1);
	}
	//printf("starting the parse\n");
	int result = parse(fp);
	if(result == 0) fprintf(stdout, "legal\n");
	else fprintf(stdout, "illegal\n");
	//call lex(fp);
	fclose(fp);
	return 0;
}