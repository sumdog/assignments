#define BACKLOG 20

//#include "CServer.h"
#include "EServer.h"
#include "CNameServer.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <unistd.h>
#include <string>


void usage() {
  cerr << "\nCSC4200-program1\n\nUsage: main -[c:s:n] <options> [-p] <port> [-h] <hostname>\n";
  cerr << "\t[-s] <service_name> -- Starts a service\n";
  cerr << "\t               name -- Starts a name service\n";
  cerr << "\n";
  exit(1);
}

int main(int argc, char **argv) {

  //setup vars for getopt
  //  (iface is allocated becasue 
  //   we may pass it to a class)
  int op;
  long port = -1;
  char *host = NULL, *sname = NULL;
  //set to null for checking later
  CServer *service = NULL;
  bool fser=false, fclient=false, fname=false;

  //parse command line arguments
  while( (op = getopt(argc,argv,"s:p:h:")) != -1) {
    switch(op) {
    case 's': //service to run
      sname = new char[strlen(optarg)];
      strcpy(sname, optarg);
      fser=true;
      break;
    case 'p': //port to use
      port = atol(optarg);
      break;
    case 'h': //interface to use
      host = new char[strlen(optarg)];
      strcpy(host, optarg);
      break;
    }
  }

  //Server mode
  if(fser==true && fclient==false && fname==false) {

    CServer *server;

    //check for valid arguments
    if(port < 0 || port > 65535 || sname == NULL) {
      cerr << "\nPlease Specify a Valid Port and Service Name" << endl;
      usage();
    }

    try {
      if( strcmp(sname,"default") == 0 ) {
	server = new CServer(host,port,BACKLOG);
      }
      else if( strcmp(sname,"name") == 0) {
	server = new CNameServer(host,port,BACKLOG);
      }
      else {
	cerr << "\nUnknown Service\n";
	 exit(6);
      }

      server->runService();

      delete host;
      delete sname;
    }
    catch(EServer e) {
      cerr << "Error: " << e.getMsg() << endl;
      exit(5);
    }
  }
  else {
    usage();
  }



}
