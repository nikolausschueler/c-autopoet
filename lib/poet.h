#ifndef POET_H
#define POET_H

/**
 * @file
 * An ADT for the Poet-Algorithm. This algorithm was once upon
 * a time described in "Computer-Kurzweil" in "Spektrum der Wissenschaft".
 * You can also find this algorithm implemented in emacs, as
 * "dissociated-press".
 */

/**
 * 
 * This is an ADT, that means you cant see the innards of that struct.
 * (Of course you can look into the sources.)
 */
typedef struct Poet_T Poet;

Poet* Poet_new(char* text, int wordLength);
void Poet_free(Poet** poet);
int Poet_getWordLength(Poet* poet);
BOOL Poet_hasNext(Poet* poet);
char Poet_next(Poet* poet);
char* Poet_output(Poet* poet);

#endif // POET_H
