/* Versuch ueber einen automatischen Schriftsteller. Die Resultate sind
 * jedoch mit denen eines echten nicht zu vergleichen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nik/base.h>
//#include <misc_c.h>

#define SAME 0

void poet(FILE* fpin, int wordLen)
{
  char c;
  char* word = NULL;
  char* text = NULL;
  int fileLen = 0;
  int randNum = 0;
  int i = 0;
  Vector* successors;

  successors = Vector_new();

  word = (char*) calloc(wordLen, sizeof(char));
  fileLen = getlen(fpin);
  text = toBuf(fpin);

  /* Startwort setzen. */ 
  for(i = 0; i < wordLen; i++) {
    word[i] = text[i];
    putchar(word[i]);
  }
  
  while(1) {
    Vector_clear(successors);

    for(i = 0; i < fileLen - wordLen; i++) {
      if(strncmp(text + i, word, wordLen) == SAME) {
	Vector_add(successors, text + i + wordLen);
      }
    }
    randNum = (int) (Vector_size(successors) * (double) random()/ RAND_MAX);
    c = *((char*) (Vector_elem(successors, randNum)));

    /* Fuer logging:
    for(i = 0; i < successors->size; i++) {
      printf("%c", *((char*) successors->elems[i]));
    }
    printf("\n");
    */

    /* Wenn der Text zuende ist, aussteigen. */
    if(c == EOF) {
      printf("\n\n");
      exit(0);
    }
    putchar(c);
    fflush(stdout);
    shiftstr(word, c);
  }
}			 		
