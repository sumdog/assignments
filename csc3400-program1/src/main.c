#include "problems.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage() {
  printf("\nCSC 3400: Program 1\n");
  printf("\nUsage: program1 [1-6] <program flags>\n");
  printf("\nPrograms\n--------\n");
  printf("1 Takes input from standard in to form\n");
  printf("  two sets and preform calculations on them\n");
  printf("5 [-s] string -- Takes a String and determines\n");
  printf("  if it is a palindrome while ignoring spaces, \n");
  printf("  punctuation, and all ASCII values between 65 and 122.\n");
  printf("6 [-n] [n] [-t] [1-2] -- Calculates the fibonacci\n");
  printf("  sequence of n using a 32-bit integer for '-t 1'\n");
  printf("  and a double for '-t 2'\n");
  printf("\n");
  exit(2);
}

int main(int argc, char** argv) {
  
  int op, prob=0, p6type=-1;
  double p6n = -1;
  char *p5 = NULL;
  

  while( (op = getopt(argc,argv,"t:n:s:")) != -1) {
    switch(op) {
      //type for prob 6
    case 't':
      p6type = atoi(optarg);
      break;
      //number to cal for prob 6
    case 'n':
      p6n = atof(optarg);
      break;
    case 's':
      p5      = (char*) malloc(sizeof(char)*(strlen(optarg)));
      strcpy(p5, optarg);
      break;
    case ':':
      usage();
    case '?':
      usage();
    }
  }
  
  //figure out which program to run
  if( optind < argc ) {
    prob = atoi( argv[optind] );
  }

  switch(prob) {
  case 1:
    runProblemOne();
    exit(0);
  case 5:
    if(p5 == NULL) {
      usage(); 
    }
    else {
      if(runProblemFive(p5) == 1) {
	printf("Input is a Palindrome\n");
      }
      else {
	printf("Input is not a Palindrome\n");
      }
      free(p5);
      exit(0);
    }
  case 6:
    if(p6n > 0 && (p6type == 1 || p6type == 2)  ) {
      runProblemSix( p6n, p6type );
      exit(0);
    }
    else {
      usage();
    }
  default:
    usage();
  }
}
