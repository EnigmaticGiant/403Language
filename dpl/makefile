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
	cat error1.txt

error1x:
	@./eval error1.txt||:

error2:
	cat error2.txt

error2x:
	@./eval error2.txt||:

error3:
	cat error3.txt

error3x:
	@./eval error3.txt||:

error4:
	cat error4.txt

error4x:
	@./eval error4.txt||:

error5:
	cat error5.txt

error5x:
	@./eval error5.txt||:

arrays:
	cat arrays.txt

arraysx:
	./eval arrays.txt

conditionals:
	cat conditionals.txt

conditionalsx:
	./eval conditionals.txt

recursion:
	cat recursion.txt

recursionx:
	./eval recursion.txt

iteration:
	cat iteration.txt

iterationx:
	./eval iteration.txt

functions:
	cat functions.txt

functionsx:
	./eval functions.txt

lambda:
	cat lambda.txt

lambdax:
	./eval lambda.txt

objects:
	cat objects.txt

objectsx:
	./eval objects.txt

clean: 
	rm -f *.o eval

