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
  cerr << "\nCSC4200-program1\n\nUsage: server -[c:s] <options>\n\n";
  cerr << "\t[-s] <service_name> -- Starts a service\n";
  cerr << "\t            default -- debuging service\n";
  cerr << "\t               name -- Starts a name service\n";
  cerr << "\t                pal -- Starts a Palindrome testing service\n";
  cerr << "\t               ping -- Starts a ping service              \n";
  cerr << "\t             insult -- Starts an insulting service        \n";
  cerr << "\t                                                          \n";
  cerr << "\t          <options> -- [-p] port [-r] nameserver [-f] filename \n";
  cerr << "\t                       port to listen on                  \n";
  cerr << "\t                       nameserver (optional) to register  \n";
  cerr << "\t                          with in the format: hostname:port  \n";
  cerr << "\t                       filename (optional) uses a file to \n";
  cerr << "\t                          determine nameserver and port     \n";
  cerr << "\t                          If no name is given, $HOME/.4200p1rc\n";
  cerr << "\t                          is assumed.\n";
  cerr << "\t                          (1st line of file is hostname     \n";
  cerr << "\t                        and 2nd is port)                  \n";
  cerr << "\t                       If -f and -r are specified, -r\n";
  cerr << "\t                           takes precedence            \n";
  cerr << "Examples:\n";
  cerr << "\t./server -s ping -p 5000 -r localhost:5000\n";
  cerr << "\t./server -s pal  -p 6001 -f ./nameserver.txt\n";
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
    case 'f': {//file to get host info from
      if(rname != NULL) { //-f takes presedence over -r
	delete rname;
	rport = -1;
      }
      ns_t *k = getNameserver(optarg);
      rname = new char[strlen(k->nshost)+1];
      strcpy(rname,k->nshost);
      rport = k->nsport;
      freeNameserver(k);
      break;
    }
    case 's': {//service to run
      sname = new char[strlen(optarg)+1];
      strcpy(sname, optarg);
      fser=true;
      break;
    }
    case 'p': {//port to use
      port = atol(optarg);
      break;
    }
    case 'h': {//interface to use
      host = new char[strlen(optarg)+1];
      strcpy(host, optarg);
      break;
    }
    case 'r': {//name service to register with
      temp = new char[strlen(optarg)+1];
      strcpy(temp,optarg);
      char *p = strtok(temp,":");
      rname = new char[strlen(p)+1];
      strcpy(rname,p);
      p = strtok(NULL,":");
      rport = atol(p);
      delete temp;
      break;
    }
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
	delete[] rname;	
      }

      //start service
      server->runService();

      //cleanup
      delete[] host;
      delete[] sname;
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


ns_t* getNameserver(char *config) {

  //variables we need
  char *cfg = (char*) malloc(sizeof(char)*BUFFER);
  char *temp;
  ns_t * ns = (ns_t*) malloc(sizeof(ns_t));

  //config files
  if(config == NULL) {
    temp = (char*) malloc(sizeof(char)*strlen(getenv("HOME")));
    strcpy(temp,getenv("HOME"));
    strcpy(cfg,temp);
    strcat(cfg,"/");
    strcat(cfg,CONFIG);
  }
  else {
    if(*config != '/') {
      getcwd(cfg,BUFFER - strlen(config));
      strcat(cfg,"/");
      strcat(cfg,config);
    }
    else {
      strcpy(cfg,config);
    }
  }

  //open config file
  FILE *fd = fopen(cfg,"r");
  if(!fd) {
    fprintf(stderr,"Error: Could not open config file %s\n",cfg);
    exit(10);
  }

  //read hostname
  temp = (char*) malloc(sizeof(char)*BUFFER);
  if( fgets(temp,BUFFER,fd) != NULL) {
    ns->nshost = (char*) malloc(sizeof(char)*strlen(temp)+1);
    strcpy(ns->nshost,temp);
    ns->nshost[strlen(ns->nshost)-1] = '\0'; //trim newline
  }
  else {
    fprintf(stderr,"Error: Could not read hostname from config file %s\n",cfg);
    exit(10);
  }

  //read port
  if( fgets(temp,BUFFER,fd) != NULL ) {
    ns->nsport = (unsigned short) atol(temp); 
  }
  else {
    fprintf(stderr,"Error: Could not read port from file %s\n",cfg);
    exit(10);
  }

  //clean up our mallocing
  free(temp);
  free(cfg);

  //return nameserver struct
  return ns;
}


void freeNameserver(ns_t *t) {
  free(t);
}
