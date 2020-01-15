#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "environment.h"


//five basic operations


//1.create

lexeme *create(){
    lexeme *new = cons(ENV,cons(VALUES,NULL,NULL), NULL);
    return new;
}

//2.lookup

lexeme *lookup(lexeme *variable, lexeme *env){
    while (env != NULL)
        {
        lexeme *vars = car(car(env));
        lexeme *vals = cdr(car(env));
        while (vars != NULL)
            {
            if (sameVariable(variable,car(vars)))
                {
                return car(vals);
                }
            vars = cdr(vars);
            vals = cdr(vals);
            }
        env = cdr(env);
    }
    fprintf(stdout, "variable %s is not found\n", getLexemeType(variable));
    exit(-1);
}

//3.update

//like lookup, only setCar is used to set the car pointer of values list

lexeme *update(lexeme *variable, lexeme *env, lexeme *new){
    while (env != NULL){
        //printf("toggle env\n");
        lexeme *vars = car(car(env));
        lexeme *vals = cdr(car(env));
        while (vars != NULL){
            //printf("toggle vars\n");
            if (sameVariable(variable,car(vars)))
                {
                    setcar(vals, new);
                    return car(vals);
                }
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(env);
    }
    fprintf(stdout, "variable %s is not found\n", getLexemeType(variable));
    exit(-1);
}

//4.insert
lexeme *insert(lexeme *var, lexeme *val, lexeme *env){
    setcar(car(env),cons(I,var,car(car(env))));
    setcdr(car(env),cons(V,val,cdr(car(env))));
    return val;
}

//5.extend

lexeme *extend(lexeme *variables, lexeme *values, lexeme *env){
    lexeme *ex = cons(ENV,cons(VALUES,variables,values), env);
    return ex;
}


void displayEnv(lexeme *env){
        int count = 0;
        while(env != NULL){
            printf("TABLE %d:\n", count);
            lexeme *table = car(env);
            lexeme *vars = car(table);
            lexeme *vals = cdr(table);
            while(vars != NULL){
                printf("    %s = %s;\n", getLexemeType(car(vars)), getLexemeType(car(vals)));

                vars = cdr(vars);
                vals = cdr(vals);
            }
            env = cdr(env);
            ++count;
        }
}

bool sameVariable(lexeme *l, lexeme *r){
    return (strcmp(getLexemeType(l), getLexemeType(r)) == 0);
}