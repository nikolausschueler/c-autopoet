/* Versuch ueber einen automatischen Schriftsteller. Die Resultate sind
 * jedoch mit denen eines echten nicht zu vergleichen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <baselib.h>
#include <misc_c.h>

#define SAME 0

void main(int argc, char **argv)
{
  int fileLen = 0;
  int wordLen = 0;
  int i;
  int randNum;
  char c;
  char* text;
  char* word;
  struct vec* successors;
  FILE *fpin;
  
  successors = vec_new();

  if(argc < 3) {
    printf("usage: %s <filename> <wordLength> [random seed]\n", argv[0]);
    exit(1);
  }
  if((fpin = fopen(argv[1], "r")) == NULL) {
    printf("%s: Cannot open input file  %s .\n", argv[0], argv[1]);
    exit(1);
  }
  wordLen = atoi(argv[2]); /* Falsch. Nur fuer Debugger-Test. */

  // Optionales Argument
  if(argc > 3) {
    srandom(atoi(argv[3]));
  }

  word = (char*) calloc(wordLen, sizeof(char));
  fileLen = getlen(fpin);
  text = toBuf(fpin);

  /* Startwort setzen. */ 
  for(i = 0; i < wordLen; i++) {
    word[i] = text[i];
    putchar(word[i]);
  }
  
  while(1) {
    vec_clear(successors);

    for(i = 0; i < fileLen - wordLen; i++) {
      if(strncmp(text + i, word, wordLen) == SAME) {
	vec_add(successors, text + i + wordLen);
      }
    }
    randNum = (int) (successors->size * (double) random()/ RAND_MAX);
    c = *((char*) (successors->elems[randNum]));

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
