#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nik/base.h>
#include "poet.h"

#define SAME 0

struct Poet_T 
{
  Vector* successors;
  char* word;
  char* text;
  int textlen;
  int wordlen;
  BOOL hasNext;
  // This counts how many character have already been processed.
  int count;
};

static char next(Poet* poet);

Poet* Poet_new(char* text, int wordLength)
{
  int i = 0;
  Poet* poet = calloc(1, sizeof(Poet));

  //?? Do strdup() here? Text is not manipulated, so there is no need to
  // You must free the text passed into here anyway outside of poet, so in
  // principle you shouldnt care. If Poet doesn't strdup, it simply must
  // not free in Poet_free. Thats the benefit of Poet being an ADT.
  poet->text = text;
  poet->textlen = strlen(text);

  poet->word = (char*) calloc(wordLength, sizeof(char));
  poet->wordlen = wordLength;

  /*:-O 
   * Set the start word. This leaves "word" unterminated, but thats okay. 
   */ 
  strncpy(poet->word, text, wordLength);

  poet->successors = Vector_new();
  poet->hasNext = TRUE;

  return poet;
}

void Poet_free(Poet** poet)
{
  assert(*poet);
  
  Vector_free(&((*poet)->successors));
  free((*poet)->word);
  free(*poet);
  *poet = NULL;
}

int Poet_count(Poet* poet)
{
  assert(poet);
  
  return poet->count;
}

int Poet_getWordLength(Poet* poet)
{
  assert(poet);

  return poet->wordlen;
}

BOOL Poet_hasNext(Poet* poet)
{
  assert(poet);
  
  return poet->hasNext;
}

char Poet_next(Poet* poet)
{
  char c;
  int randNum = 0;
  int i = 0;

  assert(poet);
  assert(poet->hasNext == TRUE);
  
  if(poet->count < poet->wordlen) {
    c = poet->word[poet->count];
    poet->count++;
    return c;
  }
  else return next(poet);
}			 		

char* Poet_output(Poet* poet)
{
  char c;
  String* s = NULL;
  
  assert(poet);
  
  s = String_new();
  while(Poet_hasNext(poet)) {
    c = Poet_next(poet);
    String_add(s, c);
  }
  return String_toChars(s);
}

static char next(Poet* poet)
{
  //?? What would be a reasonable default to initialize a char with?
  char c;
  int i = 0;
  int randNum = 0;

  assert(poet);

  Vector_clear(poet->successors);
  
  /*:-O 
   * Look for all successors of current word. This stops at "wordlen"
   * chars before the end of the string (textlen is the position of the
   * \0), so that one possible successor
   * is the \0 ending the string (and indicating that we are finished).
   */
  for(i = 0; i <= poet->textlen - poet->wordlen; i++) {
    if(strncmp(poet->text + i, poet->word, poet->wordlen) == SAME) {
      Vector_add(poet->successors, poet->text + i + poet->wordlen);
    }
  }
  /*:-O Randomly choose one of the successors. */
  randNum = (int) (Vector_size(poet->successors) * (double) random()/ RAND_MAX);
  c = *((char*) (Vector_elem(poet->successors, randNum)));
  /*:-O If end of text is reached, stop. */
  if(c == '\0') {
    poet->hasNext = FALSE;
    /*:-O 
     * If poet has reached the end of text, return end-of-string.
     */
    //??? Should we return this '\0' or an EOF?
    c = '\0';
  }
  /*:-O Else prepare for next call of this function. */
  else {
    shiftstr(poet->word, c);
    poet->count++;
  }

  return c;
}
