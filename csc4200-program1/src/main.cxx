#define BACKLOG 20

#include "CServer.h"
#include "EServer.h"
#include "ERegister.h"
#include "CNameServer.h"
#include "CPalServer.h"
#include "CPingServer.h"
#include "CInsultServer.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <unistd.h>
#include <string>
#include "client.h"

void usage() {
  cerr << "\nCSC4200-program1\n\nUsage: main -[c:s] <options>\n\n";
  cerr << "\t[-s] <service_name> -- Starts a service\n";
  cerr << "\t            default -- debuging service\n";
  cerr << "\t               name -- Starts a name service\n";
  cerr << "\t                pal -- Starts a Palindrome testing service\n";
  cerr << "\t               ping -- Starts a ping service              \n";
  cerr << "\t             insult -- Starts an insulting service        \n";
  cerr << "\t                                                          \n";
  cerr << "\t          <options> -- [-p] port [-r] nameserver          \n";
  cerr << "\t                       port to listen on                  \n";
  cerr << "\t                       nameserver (optional) to register  \n";
  cerr << "\t                       with in the format: hostname:port  \n";
  cerr << "\n";
  exit(1);
}

int main(int argc, char **argv) {

  //setup vars for getopt
  //  (iface is allocated becasue 
  //   we may pass it to a class)
  int op;
  long port = -1, rport = -1;
  char *host = NULL, *sname = NULL, *rname = NULL, *temp;
  //set to null for checking later
  CServer *service = NULL;
  bool fser=false, fclient=false;

  //parse command line arguments
  while( (op = getopt(argc,argv,"s:p:r:f:c")) != -1) {
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
    case 'r': //name service to register with
      temp = new char[strlen(optarg)];
      strcpy(temp,optarg);
      char *p = strtok(temp,":");
      rname = new char[strlen(p)];
      strcpy(rname,p);
      p = strtok(NULL,":");
      rport = atol(p);
      delete temp;
      break;
    }
  }

  //Server mode
  if(fser==true && fclient==false) {

    CServer *server;

    //check for valid arguments
    if(port < 0 || port > 65535 || sname == NULL) {
      cerr << "\nPlease Specify a Valid Port and Service Name" << endl;
      usage();
    }

    try {
      if( strcmp(sname,"default") == 0 ) {
	server = new CServer(port,BACKLOG);
      }
      else if( strcmp(sname,"name") == 0) {
	server = new CNameServer(port,BACKLOG);
      }
      else if( strcmp(sname,"pal") == 0) {
	server = new CPalServer(port,BACKLOG);
      }
      else if( strcmp(sname,"ping") == 0) {
	server = new CPingServer(port,BACKLOG);
      }
      else if( strcmp(sname,"insult") == 0) {
	server = new CInsultServer(port,BACKLOG);
      }
      else {
	cerr << "\nUnknown Service\n";
	 exit(6);
      }

      //register with name service
      if(rname) { //if a nameserver was given to register with
	try{
	  server->registerService(rname,rport);
	}
	catch(ERegister e) {
	  cerr << "Warning: " << e.getMsg() << endl;
	}
	delete rname;	
      }

      //start service
      server->runService();

      //cleanup
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
