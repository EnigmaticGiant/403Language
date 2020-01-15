OBJS = types.o lexeme.o lexer.o scanner.o main.o parser.o
OPTS = gcc -Wall -Wextra -g -std=c99 -ggdb3

all: recognizer

recognizer: types.o lexeme.o lexer.o main.o parser.o
	$(OPTS) -o recognizer types.o lexeme.o lexer.o parser.o main.o 

lexical.o: lexical.c lexical.h
	$(OPTS) -c lexical.c

types.o: types.c types.h
	$(OPTS) -c types.c

lexeme.o: types.h lexeme.h lexeme.c
	$(OPTS) -c lexeme.c

lexer.o: lexer.c lexer.h types.h lexeme.h
	$(OPTS) -c lexer.c

parser.o: parser.c parser.h lexer.h types.h lexeme.h
	$(OPTS) -c parser.c

main.o: main.c parser.h
	$(OPTS) -c main.c

clean: 
	rm -f *.o recognizer

test1: recognizer
	./recognizer test1
