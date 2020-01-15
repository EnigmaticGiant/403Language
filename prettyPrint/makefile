OBJS = types.o lexeme.o main.o environment.o
OPTS = gcc -Wall -Wextra -g -std=c99 -ggdb3

all: pretty

pretty: types.o lexeme.o lexer.o main.o environment.o parser.o pretty.o
	$(OPTS) -o pretty types.o lexeme.o lexer.o main.o environment.o parser.o pretty.o

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

main.o: main.c lexeme.h pretty.h parser.h
	$(OPTS) -c main.c

clean: 
	rm -f *.o pretty

