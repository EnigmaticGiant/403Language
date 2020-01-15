OBJS = types.o lexeme.o main.o environment.o
OPTS = gcc -Wall -Wextra -g -std=c99 -ggdb3

all: environment

environment: types.o lexeme.o main.o environment.o
	$(OPTS) -o environment types.o lexeme.o main.o environment.o

types.o: types.c types.h
	$(OPTS) -c types.c

lexeme.o: types.h lexeme.h lexeme.c
	$(OPTS) -c lexeme.c

environment.o: environment.h lexeme.h types.h environment.c
	$(OPTS) -c environment.c

main.o: main.c environment.h
	$(OPTS) -c main.c

clean: 
	rm -f *.o recognizer

