#if HAVE_CONFIG_H
#include <config.h>
#endif

#if HAVE_GETOPT_H
#include <getopt.h>
#endif

#if HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <string.h>

// If we have getopt.h, we have getopt_long, else we have only getopt. Depending
// on the value of the macros the corresponding function is defined here.

#if HAVE_GETOPT_H

void getOptions(int argc,
                char* argv[],
                char** infileName,
                char** outfileName,
                int* wordLen,
                int* sleeptime) {

  int c = 0;
  int optionIndex = 0;

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
                                          {"file", required_argument, 0, opt_infile
                                          },
                                          {"output", required_argument, 0, opt_outfile},
                                          {"wordlen", required_argument, 0, opt_wordlen},
                                          {"randseed", required_argument, 0, opt_seed},
                                          {"help", no_argument, 0, opt_help},
                                          {"sleep", required_argument, 0, opt_sleep},
                                          {"typewriter", no_argument, 0, opt_typewriter},
                                          {0, 0, 0, 0}
                                        };

  while((c = getopt_long(argc, argv, "h?f:o:r:s:tw:", long_options, &optionIndex)) != -1) {
    switch(c) {
    case 'f':
    case opt_infile:
      *infileName = strdup(optarg);
      break;
    case 'o':
    case opt_outfile:
      *outfileName = strdup(optarg);
      break;
    case 'w':
    case opt_wordlen:
      *wordLen = atoi(optarg);
      break;
    case 'r':
    case opt_seed:
      srandom(atoi(optarg));
      break;
    case 's':
    case opt_sleep:
      *sleeptime = atoi(optarg);
      break;
    case 't':
    case opt_typewriter:
      // This amount of sleeptime results in an output speed like you
      // see it on consoles in science fiction films.
      *sleeptime = 100000;
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
      printf("-r --randseed random seed\n");
      printf("\tA seed for the random number generator.\n");
      printf("\tDifferent seeds result in different output.\n");
      printf("-s --sleep sleep time\n");
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
}

#else

void getOptions(int argc,
                char* argv[],
                char** infileName,
                char** outfileName,
                int* wordLen,
                int* sleeptime) {

  int c = 0;

  while((c = getopt(argc, argv, "h?f:o:r:s:tw:")) != -1) {
    switch(c) {
    case 'f':
      *infileName = (char*) strdup(optarg);
      break;
    case 'o':
      *outfileName = strdup(optarg);
      break;
    case 'w':
      *wordLen = atoi(optarg);
      break;
    case 'r':
      srandom(atoi(optarg));
      break;
    case 's':
      *sleeptime = atoi(optarg);
      break;
    case 't':
      // This amount of sleeptime results in an output speed like you
      // see it on consoles in science fiction films.
      *sleeptime = 100000;
      break;
    case 'h':
    case '?':
      printf("usage: %s [options] < filename\n", argv[0]);
      printf("where options are as follows:\n");
      printf("-f filename\n");
      printf("\tName of input file. Without this option, input is read from stdin.\n");
      printf("-h -? \n");
      printf("\tDisplay help for this program and exit.\n");
      printf("-o filename\n");
      printf("\tName of output file. Without this option, output is written to stdout.\n");
      printf("-r random seed\n");
      printf("\tA seed for the random number generator.\n");
      printf("\tDifferent seeds result in different output.\n");
      printf("-s time\n");
      printf("\tTime to sleep before next letter is displayed.\n");
      printf("\tValues for this may be different for every OS, you have to try it.\n");
      printf("-t\n");
      printf("\tA preset for sleep time as specified for sleep.\n");
      printf("\tThis sets an output speed like on those beeping terminals\n");
      printf("\tyou see in older science fiction films.\n");
      printf("-w wordLength\n");
      printf("\tThe word length to be used.\n");
      exit(1);
      // This can never reached, but we learned in school to end a case
      // with "break".
      break;
    default:
      break;
    }
  }
}

#endif
