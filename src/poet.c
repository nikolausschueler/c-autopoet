/* Versuch ueber einen automatischen Schriftsteller. Die Resultate sind
 * jedoch mit denen eines echten nicht zu vergleichen.
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nik/base.h>

//??? Hotfix. It should not be necessary to use an explicit path here.
#include "../lib/poet.h"

#define SAME 0

int main(int argc, char **argv)
{
  int c = 0;
  int optionIndex = 0;
  int sleeptime = 0;
  int wordLen = 0;
  char* infileName = NULL;
  char* outfileName = NULL;
  char* text = NULL;
  FILE *fpin = NULL;

  /*
   * Use numbers > 256 here, so they dont get confused with the 
   * acsii character codes getopt() returns for the single letter
   * options.
   */
  enum { 
    opt_infile = 300,
    opt_outfile = 301,
    opt_wordlen = 302,
    opt_seed = 303,
    opt_help = 304,
    opt_sleep = 305,
    opt_typewriter = 306
  };
  
  static struct option long_options[] = {
    {"file", required_argument, 0, opt_infile},
    {"output", required_argument, 0, opt_outfile},
    {"wordlen", required_argument, 0, opt_wordlen},
    {"seed", required_argument, 0, opt_seed},
    {"help", no_argument, 0, opt_help},
    {"sleep", required_argument, 0, opt_sleep},
    {"typewriter", no_argument, 0, opt_typewriter},
    {0, 0, 0, 0}
  };

  wordLen = 3;

  while((c = getopt_long(argc, argv, "h?f:o:s:tw:", long_options, &optionIndex)) != -1) {
    switch(c) {
    case 'f':
    case opt_infile:
      infileName = strdup(optarg);
      break;
    case 'o':
    case opt_outfile:
      outfileName = strdup(optarg);
      break;
    case 'w':
    case opt_wordlen:
      wordLen = atoi(optarg);
      break;
    case 's':
    case opt_seed:
      srandom(atoi(optarg));
      break;
    case opt_sleep:
      sleeptime = atoi(optarg);
      break;
    case 't':
    case opt_typewriter:
      // This amount of sleeptime results in an output speed like you
      // see it on consoles in science fiction films.
      sleeptime = 100000;
      break;
    case 'h':
    case '?':
    case opt_help:
      //??? This is not the complete usage. How to put out usage? Write 
      // some framework as i did for Java?
      printf("usage: %s < filename -w wordLength -s [random seed]\n", argv[0]);
      exit(1);
      // This can never reached, but we learned in school to end a case 
      // with "break".
      break;
    default:
      break;
    }
  } 
  
  if(infileName) {
    if((fpin = fopen(infileName, "r")) == NULL) {
      fprintf(stderr, "Cannot open input file\n");
      exit(1);
    }
  }
  else fpin = stdin;

  text = toBuf(fpin);
  Poet* poet = Poet_new(text, wordLen);
  if(sleeptime == 0) {
    printf("%s", Poet_output(poet));
  }
  else {
    while(Poet_hasNext(poet)) {
      printf("%c", Poet_next(poet));
      usleep(sleeptime);
    }
  }
  //??? outfile is not considered in the moment, because poet() writes
  // directly to screen.
  
  //??? Implement: Poet_free(&poet);
  return 0;
}			 		
