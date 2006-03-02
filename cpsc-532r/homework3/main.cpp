/*
 * Sumit Khanna <Sumit-Khanna@utc.edu>
 *
 * cpsc-532r / Homework #3 / Harris
 *
 * This program is intended to emulate the "yes"
 * program in Linux coreutils with the addition
 * of intercepting signals for Interrurpt (^C), 
 * Stop (^Z) and losing the tty. 
 *
 * The easiest way to actually stop this program 
 * is to use ^\ or you can also send it 
 * the kill -9 signal like so:
 * 
 *   killall -9 cpsc-532r-hw3
 *
 */
#include <string>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

/* Globals needed for signal handling */

int gSigInt;
int gSigStop;


/* Output functions */

void printString(string s) {

  while(true) {
    if(gSigInt == 1) {
      cout << "^C Interrurpt" << endl;
      gSigInt = 0;
      sleep(5);
    }
    else if (gSigStop == 1) {
      cout << "^Z Stop" << endl;
      gSigStop = 0;
      sleep(5);
    }
    else {
      cout << s << endl;
    }
  }
  
}

void printUsage() {

  cout << "Usage: yes <string>" <<endl;
  cout << "   or: yes <option>" <<endl <<endl;
  cout << "Optins: --help     displays this and exits" << endl;
  cout << "        --version  outputs version information and exits" << endl;

}

void printVersion() {
  cout << "yes - Written by Sumit Khanna for CPSC-532r/Harris/UTC" << endl;
}

/* Signal Handlers */

void hSigInt(int a) {
  //toggle our global to indicate a ctrl+c
  gSigInt = 1;
}

void hSigStop(int a) {
  gSigStop = 1;
}


int main(int argc, char** argv) {

  /* establish globals */
  gSigInt = 0;
  gSigStop = 0;


  /* Deal with command line args */
  if(argc > 1) {
    if(strcmp(argv[1],"--version")==0) {
      printVersion();
      exit(0);
    }
    if(strcmp(argv[1],"--help")==0) {
      printUsage();
      exit(0);
    }
    if( argv[1][0]  == '-' ) {
      cout << "Invalid Option: " << argv[1] << endl;
      printUsage();
      exit(1);
    }
  }

  /* setup signal handlers */
  signal(SIGINT,hSigInt);
  signal(SIGTSTP,hSigStop);
  signal(SIGHUP,SIG_IGN);

  /* no command line args (print y) */
  if(argc == 1) {
    printString("y");
  }

  /* print cmd args */
  int x;
  string strout("");
  for(x=1; x<argc; x++) {
    strout = strout + argv[x];
    if(x != argc-1) {
      strout = strout + ' ';
    }
  }
  printString(strout);
}
