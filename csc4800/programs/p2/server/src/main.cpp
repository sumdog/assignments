/*
  CSC4800/3400 - Program 2 - Sumit Khanna
  
  This program is the main driver for my 
  multithreaded C++ server. It takes one argument
  on startup: its port number.

  Exit 2: No port given
  Exit 3: Invalid Port
  Exit 4: Server Error

*/


#define BACKLOG 100

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;

#include "CAddressServer.hpp"
#include "exceptions.hpp"

void usage() {
  cerr << "\nCSC4800-program2\n\nUsage: server [port]\n\n";
  cerr << "\t[port] - port to listen on [1024-65535]\n\n ";
}

int main(int argc, char **argv) {


  if(argc < 2) {
    cerr << "Pleace specify a port!";
    usage();
    exit(2);
  }
  
  int port = atol(argv[1]);
  if(port < 1024 || port > 65535) {
    cerr << "Invalid Port!";
    usage();
    exit(3);
  }

  CServer *server;

  try {
    server = new CAddressServer(port,BACKLOG);
    server->runService();
  }
  catch(EServer e) {
    cerr << "Error:" << e.getMsg() << endl;
    exit(4);
  }

}
