/* Versuch ueber einen automatischen Schriftsteller. Die Resultate sind
 * jedoch mit denen eines echten nicht zu vergleichen.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nik/base.h>
//#include <misc_c.h>

#define SAME 0

int main(int argc, char **argv)
{
  int wordLen = 0;
  FILE *fpin;
  
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

  //?? For starters, let function print directly to screen. Later, return
  // complete string or return a char with every call.
  poet(fpin, wordLen);

  return 0;
}			 		
