/* Versuch ueber einen automatischen Schriftsteller. Die Resultate sind
 * jedoch mit denen eines echten nicht zu vergleichen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nik/base.h>

#define SAME 0

struct Poet_T 
{
  Vector* successors;
  char* word = NULL;
  char* text = NULL;
  int textlen = 0;
};

Poet* Poet_new(char* text)
{
  Poet* poet = calloc(1, sizeof(Poet));

  //?? Do strdup() here?
  poet->text = text;
  poet->textlen = strlen(text);

  word = (char*) calloc(wordLen, sizeof(char));

  /*:-O Set the start word. */ 
  for(i = 0; i < wordLen; i++) {
    word[i] = text[i];
    putchar(word[i]);
  }

  poet->word = word;
  poet->successors = Vector_new();
  

}

BOOL Poet_hasNext(Poet* poet)
{
  assert(poet);
  
  return poet->hasNext();
}

char Poet_next(Poet* poet)
{
  char c;
  int randNum = 0;
  int i = 0;

  assert(poet);
  assert(poet->hasNext == TRUE);

  Vector_clear(poet->successors);
  
  for(i = 0; i < poet->textlen - poet->wordLen; i++) {
    if(strncmp(poet->text + i, poet->word, poet->wordLen) == SAME) {
      Vector_add(poet->successors, poet->text + i + poet->wordLen);
    }
  }
  randNum = (int) (Vector_size(poet->successors) * (double) random()/ RAND_MAX);
  c = *((char*) (Vector_elem(poet->successors, randNum)));
  
  /*:-O If end of text is reached, stop. */
  if(c == '\0') {
    poet->hasNext = FALSE;
  }
  shiftstr(poet->word, c);
  
  /*:-O 
   * If poet has reached the end of text, return end-of-string. 
   */
  return c;
}			 		


char* Poet_output(Poet* poet)
{
  char c;
  String* s = NULL;

  assert(poet);

  String* s = String_new();
  while(Poet_hasNext(poet))
    c = Poet_next(poet);
    String_append(s, c);
  }
  return String_toChars(s);
}
