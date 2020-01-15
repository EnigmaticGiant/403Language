OBJS = types.o lexeme.o main.o environment.o parser.o eval.o
OPTS = gcc -Wall -Wextra -g -std=c99 -ggdb3

all: eval

eval: types.o lexeme.o lexer.o main.o environment.o parser.o eval.o pretty.o
	$(OPTS) -o eval types.o lexeme.o lexer.o main.o environment.o parser.o eval.o pretty.o

types.o: types.c types.h
	$(OPTS) -c types.c

lexeme.o: types.h lexeme.h lexeme.c
	$(OPTS) -c lexeme.c

lexer.o: lexer.c lexer.h types.h lexeme.h
	$(OPTS) -c lexer.c

environment.o: environment.h lexeme.h types.h environment.c
	$(OPTS) -c environment.c

parser.o: parser.c parser.h lexer.h types.h lexeme.h environment.h
	$(OPTS) -c parser.c

pretty.o: pretty.c pretty.h types.h lexeme.h lexer.h parser.h
	$(OPTS) -c pretty.c

eval.o: eval.c eval.h types.h lexeme.h lexer.h parser.h
	$(OPTS) -c eval.c

main.o: main.c lexeme.h pretty.h parser.h
	$(OPTS) -c main.c

error1:
	cat error1

error1x:


error2:
	cat error2

error2x:


error3:
	cat error3

error3x:


error4:
	cat error4.txt

error4x:
	@./eval error4.txt||:

error5:
	cat error5

error5x:


arrays:
	cat arrays

arraysx:


conditionals:
	cat condititonals

conditionalsx:


recursion:
	cat recursion

recursionx:


iteration:
	cat iteration

iterationx:


functions:
	cat functions

functionsx:


lambda:
	cat lambda

lambdax:


objects:
	cat objects

objectsx:


clean: 
	rm -f *.o eval

