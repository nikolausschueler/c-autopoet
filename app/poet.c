#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nik/base.h>

#include "poet.h"

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
  FILE *fpout = NULL;
  String* str;
  Poet* poet;

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
      printf("usage: %s [options] < filename\n", argv[0]);
      printf("where options are as follows:\n");
      printf("-f --file filename\n");
      printf("\tName of input file. Without this option, input is read from stdin.\n");
      printf("-h -? --help\n");
      printf("\tDisplay help for this program and exit.\n");
      printf("-o --output filename\n");
      printf("\tName of output file. Without this option, output is written to stdout.\n");
      printf("-s --seed random seed\n");
      printf("\tA seed for the random number generator.\n");
      printf("\tDifferent seeds result in different output.\n");
      printf("--sleep sleep time\n");
      printf("\tTime to sleep before next letter is displayed.\n");
      printf("\tValues for this may be different for every OS, you have to try it.\n");
      printf("-t --typewriter\n");
      printf("\tA preset for sleep time as specified for sleep.\n");
      printf("\tThis sets an output speed like on those beeping terminals\n");
      printf("\tyou see in older science fiction films.\n");
      printf("-w --wordlen wordLength\n");
      printf("\tThe word length to be used.\n");
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
