#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "eval.h"


lexeme *eval(lexeme *tree,lexeme *env){
	char *type = getLexemeType(tree);
	//printf("The type is ");
	//displayLexeme(tree);
	if(type == INTEGER) return tree;
	else if(type == STRING) return tree;
	else if(type == VARIABLE) return getVarVal(tree, env);
	else if(type == FUNCDEF) return evalFuncDef(tree, env);
	else if(type == PLUS || type == MINUS || type == TIMES || type == DIVIDE || type == MOD || type == LESS_THAN || type == GREAT_THAN){
		return evalSimpleOp(tree, env);
	}
	else if(type == ASSIGN) return evalAssign(tree, env);
	else if(type == VARDEF) return evalVarDef(tree, env);
	else if(type == CALL) return evalCall(tree, env);
	else if(type == PROGRAM) return evalProgram(tree, env);
	else if(type == statementList) return evalBlock(tree, env);
	else if(type == IF) return evalIf(tree, env);
	else if(type == ELSE) return evalElse(tree, env);
	else if(type == WHILE) return evalWhile(tree, env);
//	else if(type == FOR) return evalFor(tree, env);
	else if(type == LAMBDA) return evalLambda(tree, env);
	else{
		printf("type %s not implemented yet!!\n", getLexemeType(tree));
		exit(1);
	}
}

lexeme *evalProgram(lexeme *tree, lexeme *env){
	//printf("program start\n");
	lexeme *result;
	while(tree != NULL){
		result = eval(car(tree), env);
		tree = cdr(tree);
	}
	//printf("program finished\n");
	return result;
}

lexeme *evalBlock(lexeme *tree, lexeme *env){
	lexeme *result;
	while(tree !=NULL){
		if(car(tree) == NULL) break;
		result = eval(car(tree), env);
		tree = cdr(tree);
	}
	return result;
}

lexeme *evalFuncDef(lexeme *tree, lexeme *env){
	insert(car(tree), cons(CLOSURE, tree, env), env);
	//printf("FUNCDEF done!!\n");
	return env;
}

lexeme *evalVarDef(lexeme *tree, lexeme *env){
	//printf("inserting variable %s\n", getLexemeSVAL(car(tree)));

	lexeme *result = eval(cdr(tree), env);
	//printf("the type of vardef result is %s\n", getLexemeType(result));
	insert(car(tree), result, env);
	return env;
}

lexeme *getVarVal(lexeme *tree, lexeme *env){
	//printf("about to lookup for ");
	//displayLexeme(tree);
	lexeme *result = lookup(tree, env);
	return result;
}

lexeme *evalSimpleOp(lexeme *tree,lexeme *env){
		char *type = getLexemeType(tree);
		//printf("the op is %s\n", type);
        if (type == PLUS) return evalPlus(tree,env);
        else if (type == MINUS) return evalMinus(tree,env);
        else if (type == TIMES) return evalTimes(tree,env);
        else if (type == DIVIDE) return evalDivide(tree,env);
        else if (type == MOD) return evalMod(tree,env);
        else if (type == GREAT_THAN) return evalGreatThan(tree, env);
        else if (type == LESS_THAN) return evalLessThan(tree, env);
        //...
        else{
        	printf("bad operator expression\n");
        	exit(1);
        }
    return tree;
}

lexeme *evalPlus(lexeme *tree, lexeme *env){
	lexeme *left = eval(car(tree), env);
	lexeme *right = eval(cdr(tree), env);
	if(getLexemeType(left) == INTEGER && getLexemeType(right) == INTEGER)
		return newLexemeInt(getLexemeIVAL(left) + getLexemeIVAL(right));	//2 + 2
	else if(getLexemeType(left) == INTEGER && getLexemeType(right) == FLOAT)
		return newLexemeFloat(getLexemeIVAL(left) + getLexemeRVAL(right));		//2 + 2.5
	else if(getLexemeType(left) == FLOAT && getLexemeType(right) == INTEGER)
		return newLexemeFloat(getLexemeRVAL(left) + getLexemeIVAL(right));		//2.5 + 2
	else if(getLexemeType(left) == FLOAT && getLexemeType(right) == FLOAT)
		return newLexemeFloat(getLexemeRVAL(left) + getLexemeRVAL(right));		//2.3 + 2.5
	//...
	else{
		printf("cannot add these two together!!\n");
		exit(1);
	}
	    return tree;

}

lexeme *evalMinus(lexeme *tree, lexeme *env){
	lexeme *left = eval(car(tree), env);
	lexeme *right = eval(cdr(tree), env);
	if(getLexemeType(left) == INTEGER && getLexemeType(right) == INTEGER)
		return newLexemeInt(getLexemeIVAL(left) - getLexemeIVAL(right));	//2 - 2
	else if(getLexemeType(left) == INTEGER && getLexemeType(right) == FLOAT)
		return newLexemeFloat(getLexemeIVAL(left) - getLexemeRVAL(right));		//2 - 2.5
	else if(getLexemeType(left) == FLOAT && getLexemeType(right) == INTEGER)
		return newLexemeFloat(getLexemeRVAL(left) - getLexemeIVAL(right));		//2.5 - 2
	else if(getLexemeType(left) == FLOAT && getLexemeType(right) == FLOAT)
		return newLexemeFloat(getLexemeRVAL(left) - getLexemeRVAL(right));		//2.3 - 2.5
	//...
	else{
		printf("cannot subtract these two!!\n");
		exit(1);
	}
    return tree;

}

lexeme *evalTimes(lexeme *tree, lexeme *env){
	lexeme *left = eval(car(tree), env);
	lexeme *right = eval(cdr(tree), env);
	if(getLexemeType(left) == INTEGER && getLexemeType(right) == INTEGER)
		return newLexemeInt(getLexemeIVAL(left) * getLexemeIVAL(right));	//2 * 2
	else if(getLexemeType(left) == INTEGER && getLexemeType(right) == FLOAT)
		return newLexemeFloat(getLexemeIVAL(left) * getLexemeRVAL(right));		//2 * 2.5
	else if(getLexemeType(left) == FLOAT && getLexemeType(right) == INTEGER)
		return newLexemeFloat(getLexemeRVAL(left) * getLexemeIVAL(right));		//2.5 * 2
	else if(getLexemeType(left) == FLOAT && getLexemeType(right) == FLOAT)
		return newLexemeFloat(getLexemeRVAL(left) * getLexemeRVAL(right));		//2.3 * 2.5
	//...
	else{
		printf("cannot multiply these two together!!\n");
		printf("they are ");
		displayLexeme(left);
		printf(" and ");
		displayLexeme(right);
		printf("\n");
		exit(1);
	}
    return tree;
}

lexeme *evalDivide(lexeme *tree, lexeme *env){
	lexeme *left = eval(car(tree), env);
	lexeme *right = eval(cdr(tree), env);
	if(getLexemeType(left) == INTEGER && getLexemeType(right) == INTEGER)
		return newLexemeInt(getLexemeIVAL(left) / getLexemeIVAL(right));	//2 / 2
	else if(getLexemeType(left) == INTEGER && getLexemeType(right) == FLOAT)
		return newLexemeFloat(getLexemeIVAL(left) / getLexemeRVAL(right));		//2 / 2.5
	else if(getLexemeType(left) == FLOAT && getLexemeType(right) == INTEGER)
		return newLexemeFloat(getLexemeRVAL(left) / getLexemeIVAL(right));		//2.5 / 2
	else if(getLexemeType(left) == FLOAT && getLexemeType(right) == FLOAT)
		return newLexemeFloat(getLexemeRVAL(left) / getLexemeRVAL(right));		//2.3 / 2.5
	//...
	else{
		printf("Semantic error: cannot divide ");
		displayLexeme(left);
		printf(" and ");
		displayLexeme(right);
		printf("\n");
		exit(1);
	}
    return tree;
}

lexeme *evalMod(lexeme *tree, lexeme *env){
	lexeme *left = eval(car(tree), env);
	lexeme *right = eval(cdr(tree), env);
	if(getLexemeType(left) == INTEGER && getLexemeType(right) == INTEGER)
		return newLexemeInt(getLexemeIVAL(left) % getLexemeIVAL(right));	//2 % 2
	//...
	else{
		printf("cannot mod these two!!\n");
		exit(1);
	}
    return tree;
}

lexeme *evalGreatThan(lexeme *tree, lexeme *env){
	lexeme *left = eval(car(tree), env);
	lexeme *right = eval(cdr(tree), env);
	if(getLexemeType(left) == INTEGER && getLexemeType(right) == INTEGER){
		if(getLexemeIVAL(left) > getLexemeIVAL(right)){
			return newLexeme(TRUE);
		}
		else{
			return newLexeme(FALSE);
		}
	}
	else{
		printf("cannot compare these two!!\n");
	}
	return tree;
}

lexeme *evalLessThan(lexeme *tree, lexeme *env){
	lexeme *left = eval(car(tree), env);
	lexeme *right = eval(cdr(tree), env);
	if(getLexemeType(left) == INTEGER && getLexemeType(right) == INTEGER){
		if(getLexemeIVAL(left) < getLexemeIVAL(right)){
			return newLexeme(TRUE);
		}
		else{
			return newLexeme(FALSE);
		}
	}
	else{
		printf("cannot compare these two!!\n");
	}
	return tree;
}

lexeme *evalAssign(lexeme *tree,lexeme *env){
        //eval the right hand side
	//pp(tree);
	//printf("\n");
	//displayEnv(env);
    lexeme *value = eval(cdr(tree),env);
    if (getLexemeType(car(tree)) == DOT){
        lexeme *obj = eval(caar(tree), env);
        update(cdar(tree),cdr(tree), obj);
    }
    else{
    	//printf("updating variable %s\n", getLexemeSVAL(car(tree)));
        update(car(tree),value,env);
    }
    return value;
}

lexeme *evalDot(lexeme *tree, lexeme *env){
    lexeme *object = eval(car(tree), env);
    return eval(cdr(tree), object); // objects == environments!
}

lexeme *evalArgs(lexeme *args, lexeme *env){
	if(args == NULL){
		return NULL;
	}
	else{
		return cons(JUNK, eval(car(args), env), evalArgs(cdr(args), env));
	}
}

lexeme *evalCall(lexeme *tree, lexeme *env){
    //this code assumes a function call of the form f(x,y)
    lexeme *name = car(tree);
    //printf("the name of function is %s\n", getLexemeSVAL(name));
    lexeme *args = cdr(tree);
    lexeme *eargs = evalArgs(args,env);
    //if(eargs) displayLexeme(eargs);
    //check for built-in functions here
    //printf("comparing the value %s to %s\n", getLexemeSVAL(name), NEWARRAY);
    if (strcmp(getLexemeSVAL(name), PRINTLN) == 0){
    	////printf("found a println!!\n");
        evalPrintln(eargs);
    	return tree;
    }
    else if(strcmp(getLexemeSVAL(name), "newArray") == 0){
    	//printf("in the new array\n");
    	lexeme *array = evalNewArray(eargs);
    	return array;
    }
     else if(strcmp(getLexemeSVAL(name), "getArray") == 0){
    	//printf("in the get array\n");
    	lexeme *result = evalGetArray(eargs);
    	//printf("the index holds value ");
    	//displayLexeme(result);
    	//printf("\n");
    	return result;
    } 
    else if(strcmp(getLexemeSVAL(name), "setArray") == 0){
    	//printf("in the set array\n");
    	//printf("the args type is %s\n", getLexemeType(car(args)));
    	//printf("the eargs type is %s\n", getLexemeType(car(eargs)));

    	evalSetArray(eargs);
    	return tree;
    }
    else{        
    	//printf("no builtin functions\n");
        lexeme *closure = lookup(name,env);
        //printf("the closure found is %s \n", getLexemeType(car(closure)));
        //displayLexeme(closure);
        lexeme *params = car(cdr(car(closure)));
        //printf("address of params is %p\n", params);
        lexeme *body = cdr(cdr(car(closure)));
        lexeme *senv = cdr(closure);
        // printf("\nstatic environment:\n");
        //displayEnv(senv);
        lexeme *xenv = extend(params, eargs, senv);
        //printf("\nextended environment:\n");
        //displayEnv(xenv);
        return eval(body,xenv);
    }
}

void evalPrintln(lexeme *evaluatedArgList){
    while (evaluatedArgList != NULL){
        displayLexeme(car(evaluatedArgList));
        evaluatedArgList = cdr(evaluatedArgList);
    }
    fprintf(stdout, "\n");
}

lexeme *evalIf(lexeme *tree, lexeme *env){
	//printf("eval if\n");
	lexeme *condition = eval(car(tree), env);
	if(getLexemeType(condition) == TRUE){
		eval(cddr(tree), env);
	}
	else{
		if(cadr(tree) != NULL){
			eval(cadr(tree), env);
		}
	}
	return env;
}

lexeme *evalElse(lexeme *tree, lexeme *env){
	if(car(tree) == NULL){
		eval(cdr(tree), env);
	}
	else{
		eval(car(tree), env);
	}
	return env;
}

lexeme *evalWhile(lexeme *tree, lexeme *env){
	lexeme *condition = eval(car(tree), env);
	while(getLexemeType(condition) == TRUE){
		//printf("in the loop\n");
		eval(cdr(tree), env);
		condition = eval(car(tree), env);
	}
	return env;
}

lexeme *evalLambda(lexeme *tree, lexeme *env){
	lexeme *result = cons(CLOSURE, tree, env);
	//printf("the type of tree is %s\n", getLexemeType(tree));
	return result;
}

lexeme *evalNewArray(lexeme *evaluatedArgList){
    //assert(length(evaluatedArgList) == 1)  //ensure only one argument
    lexeme *size = newLexemeInt(getLexemeIVAL(car(evaluatedArgList)));
    //assert(size.type == INTEGER);          //ensure an integer argument
    lexeme *a = newLexeme(ARRAY);
    setLexemeAVALsize(a, getLexemeIVAL(size));        //allocate the array
    //assert(a.aval != NULL);                //ensure a good allocation
    return a;
}


lexeme *evalGetArray(lexeme *evaluatedArgList){
    //assert(length(evaluatedArgList) == 2);
    lexeme *a = car(evaluatedArgList);
    lexeme *i = cadr(evaluatedArgList);
    //check for valid types here
    //return a.aval[i.ival];
    return getLexemeAVAL(a, getLexemeIVAL(i));
}

lexeme *evalSetArray(lexeme *evaluatedArgList){
    //assert(length(evaluatedArgList) == 3);
    lexeme *array = car(evaluatedArgList);
    //printf("type of array is %s\n", getLexemeType(array));
    lexeme *index = cadr(evaluatedArgList);
        //printf("type of index is %s\n", getLexemeType(index));

    lexeme *value = car(cdr(cdr(evaluatedArgList)));
        //printf("type of value is %s\n", getLexemeType(value));

    //check for valid types here
    //a.aval[i.ival] = v;
    setLexemeAVAL(array, getLexemeIVAL(index), value);
    return value;                      //could also return the previous value
}


/*
lexeme *evalConstructor(closure, env){
	lexeme *senv = car(closure);
	lexeme *xenv = extend(senv, NULL, NULL);
	lexeme *body = cdr(cdr(closure));
	eval(body, xenv);
	return xenv;
}*/


/*

void evalClass(tree, env){
	insertEnv(env, car(tree), cons(OCLOSURE, env, tree));
}



*/


//readInt
//newArray
//getArray( , )
//setArray