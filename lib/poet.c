/* Versuch ueber einen automatischen Schriftsteller. Die Resultate sind
 * jedoch mit denen eines echten nicht zu vergleichen.
 */

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

  //?? Do strdup() here?
  poet->text = text;
  poet->textlen = strlen(text);

  poet->word = (char*) calloc(wordLength, sizeof(char));
  poet->wordlen = wordLength;

  /*:-O Set the start word. */ 
  for(i = 0; i < wordLength; i++) poet->word[i] = text[i];

  poet->successors = Vector_new();
  poet->hasNext = TRUE;

  return poet;
}

/*??? What to free exactly here? text? word?
void Poet_free(Poet** poet)
{
  assert(*poet);
  
  free
}
*/

int Poet_count(Poet* poet)
{
  assert(poet);
  
  return poet->count;
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
  
  for(i = 0; i < poet->textlen - poet->wordlen; i++) {
    if(strncmp(poet->text + i, poet->word, poet->wordlen) == SAME) {
      Vector_add(poet->successors, poet->text + i + poet->wordlen);
    }
  }
  randNum = (int) (Vector_size(poet->successors) * (double) random()/ RAND_MAX);
  c = *((char*) (Vector_elem(poet->successors, randNum)));
  
  /*:-O If end of text is reached, stop. */
  if(c == '\0') {
    poet->hasNext = FALSE;
  }
  shiftstr(poet->word, c);
  poet->count++;

  /*:-O 
   * If poet has reached the end of text, return end-of-string. 
   */
  return c;
}
