#include <stdbool.h>
#include "lexeme.h"
#include "types.h"

//five basic operations


//1.create

extern lexeme *create();

//2.lookup

extern lexeme *lookup(lexeme *, lexeme *);

//3.update

//like lookup, only setCar is used to set the car pointer of values list

extern lexeme *update(lexeme *, lexeme *, lexeme *);

//4.insert

extern lexeme *insert(lexeme *, lexeme *, lexeme *);

//5.extend

extern lexeme *extend(lexeme *, lexeme *, lexeme *);

extern void displayEnv(lexeme *);

extern bool sameVariable(lexeme *, lexeme *);