#include "CPingServer.h"
#include <string>

CPingServer::CPingServer(unsigned short port, long backlog) : CServer(port,backlog) {
  strcpy(name,"ping"); 
}

void CPingServer::processRequest(command_t *t, char* retval) {

  //check for the right command format
  if(t->type == CMD_IVK   &&   t->argc == 1   &&   strcmp("ping",*(t->argv)) == 0  ) {
    strcpy(retval,"A:Pong!\n");
  }
  else {
    strcpy(retval,"E:Invalid Command\n");
  }
}
