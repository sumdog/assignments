#include "CServer.h"
#include "except/EServer.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <errno.h>
#include <unistd.h>


void usage() {
  cerr << "\nCSC4200-program1\n\nUsage: main -[c:s:n] <options> [-p] <port> [-i] <interface>\n\n";
  cerr << "\t[-s] <service_name> -- Starts a service\n";
  cerr << "\n";
  exit(1);
}

int main(int argc, char **argv) {

  //setup vars for getopt
  //  (iface is allocated becasue 
  //   we may pass it to a class)
  int op;
  unsigned short port = 0;
  char *iface = new char[12], sname[20];
  //set to null for checking later
  iface[0] = '\0'; 
  sname[0] = '\0';
  CServer *service = NULL;
  bool fser=false, fclient=false, fname=false;

  //parse command line arguments
  while( (op = getopt(argc,argv,"s:p:i:")) != -1) {
    switch(op) {
    case 's': //service to run
      strcpy(sname, optarg);
      fser=true;
      break;
    case 'p': //port to use
      port = (unsigned short) atol(optarg);
      break;
    case 'i': //interface to use
      strcpy(iface, optarg);
      break;
    }
  }

  if(fser==true && fclient==false && fname==false) {
    
  }

  /*
  CServer *test = new CServer(NULL,8001,20);
  try {
    test->runService();
  }
  catch(EServer e) {
//    perror(NULL);

}*/
}
