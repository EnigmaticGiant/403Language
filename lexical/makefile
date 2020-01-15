OBJS = types.o lexeme.o lexer.o scanner.o
OPTS = gcc -Wall -Wextra -g -std=c99 -ggdb3

all: scanner

scanner: types.o lexeme.o lexer.o scanner.o
	$(OPTS) -o scanner types.o lexeme.o lexer.o scanner.o

lexical.o: lexical.c lexical.h
	$(OPTS) -c lexical.c

types.o: types.c types.h
	$(OPTS) -c types.c

lexeme.o: types.h lexeme.h lexeme.c
	$(OPTS) -c lexeme.c

lexer.o: lexer.c lexer.h types.h lexeme.h
	$(OPTS) -c lexer.c

scanner.o: scanner.c scanner.h lexer.h lexeme.h types.h
	$(OPTS) -c scanner.c

clean: 
	rm -f *.o scanner

test1: scanner
	./scanner test1

test2: scanner
	./scanner test2

test3: scanner
	./scanner test3

test4: scanner
	./scanner test4

test5: scanner
	./scanner test5