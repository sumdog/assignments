#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include "CServer.h"

CServer::CServer(char* hostname, unsigned short port) {

  local_addr = new sockaddr_in;
  remote_addr = new sockaddr_in;

  sockfd = socket(AF_INET,SOCK_STREAM,0);

  local_addr->sin_family = AF_INET;
  local_addr->sin_port = htons(port);
  
  
}

CServer::~CServer() {
  delete local_addr;
  delete remote_addr;
}
