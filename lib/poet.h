#ifndef POET_H
#define POET_H

/**
 * \file An ADT for the Poet-Algorithm. This algorithm was once upon
 * a time described in "Computer-Kurzweil" in "Spektrum der Wissenschaft".
 * You can also find this algorithm implemented in emacs, as
 * "dissociated-press".
 */

typedef Poet_T Poet;

/**
 * Make a new Poet, initialized with <code>text</code>. 
 * <code>text</code> must be a NULL-terminated string.
 */
Poet* Poet_new(char* text);

/** 
 * Return the word-length used by Poet.
 */
int Poet_getWordlength(Poet* poet);

/**
 * Indicates if Poet can proceed or if it has reached the end of the
 * text.
 * @return <code>TRUE</code> if Poet can proceed, 
 * <code>FALSE</code> if end of text has been reached.
 */
BOOL Poet_hasNext(Poet* poet);

/**
 * Return the next char. This function is mainly intended to do output
 * for animation purposes, for example by sleeping several milliseconds
 * and the showing the next letter.
 * If code was compiled with assertions enabled and end of text has been
 * reached already (Poet_hasNext() returns <code>FALSE</code>), calling
 * this function makes an assertion fail and stops the program.
 * @remarks Should the return type be <code>char*</code>, so the interface 
 * remains the same if i one day enhance this to handle whole words
 * instead of single characters? 
 */
char Poet_next(Poet* poet);

/**
 * This returns the whole output at once.
 * @todo Document interactions between Poet_next() and Poet_output().
 */
char* Poet_output(Poet* poet);

/**
 * Set the word-length used by this Poet.
 */
void Poet_setWordLength(Poet* poet, int wordlen);

#endif // POET_H
