#include "EServer.h"
#include <cstring>

EServer::EServer(char *msg) {
  message = new char[strlen(msg)];
  strcpy(message,msg);
}

EServer::~EServer() {
  delete message; 
}

char* EServer::getMsg() {
  return message;
}
  

