#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <nik/base.h>

#include "poet.h"
#include "getoptions.h"

#define SAME 0

int main(int argc, char* argv[]) {

  int sleeptime = 0;
  int wordLen = 0;
  char* infileName = NULL;
  char* outfileName = NULL;
  char* text = NULL;
  FILE *fpin = NULL;
  FILE *fpout = NULL;
  String* str;
  Poet* poet;

  wordLen = 3;

  getOptions(argc, argv, &infileName, &outfileName, &wordLen, &sleeptime); 

  if(infileName) {
    if((fpin = fopen(infileName, "r")) == NULL) {
      fprintf(stderr, "Cannot open input file\n");
      exit(1);
    }
  }
  else fpin = stdin;

  text = toBuf(fpin);

  poet = Poet_new(text, wordLen);

  /*:-O
   * If outfile is set, write the whole shebang to it. Else write
   * the whole stuff to the console; if sleeptime is set, write
   * in "demo mode", else simply write the whole output.
   */
  if(outfileName) {
    if((fpout = fopen(outfileName, "w")) == NULL) {
      fprintf(stderr, "Cannot open output file\n");
      exit(1);
    }
    fprintf(fpout, "%s\n", Poet_output(poet));
  }
  else {
    if(sleeptime == 0) {
      printf("%s\n", Poet_output(poet));
    }
    else {
      while(Poet_hasNext(poet)) {
        printf("%c", Poet_next(poet));
        fflush(stdout);
        usleep(sleeptime);
      }
      printf("\n");
    }
  }
  Poet_free(&poet);
  return 0;
}
