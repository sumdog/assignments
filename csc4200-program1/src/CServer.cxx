#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include "CServer.h"
#include "except/EServer.h"
#include <pthread.h>
#include "unistd.h"
#include <string>
#include <stdio.h>

CServer::CServer(char* ip, unsigned short port, long backlog) {

  //setup class variables
  local_addr = new sockaddr_in;
  remote_addr = new sockaddr_in;
  this->backlog = backlog;

  //socket file discriptor
  sockfd = socket(AF_INET,SOCK_STREAM,0);

  //serup socket structs
  local_addr->sin_family = AF_INET;
  local_addr->sin_port = htons(port);
  local_addr->sin_addr.s_addr = INADDR_ANY;
  memset(&(local_addr->sin_zero), '\0',8);
}

CServer::~CServer() {
  delete local_addr;
  delete remote_addr;
}

void CServer::processRequest(command_t *t, char* retval) {
  strcpy(retval,"Override this method to implement\n");
}

void CServer::deleteCommand(command_t *t) {
  //delete all strings
  char **i;
  short x;
  for(x=0, i=t->argv;  x<t->argc;   x++,i++) {
    delete *i;
  }
  delete t->argv;
  
  //delete struct
  delete t;

  //all gone!
}

command_t* CServer::parseCommand(char *cmd) {
  
  //struct for returning data
  command_t *retval = new command_t;
  retval->argc=0;
  retval->argv = new (char*)[MAX_ARGS];
  
  //break tokens on spaces and ':'
  char *token = strtok(cmd,": ");

  //the first letter of token is our type
  //(e.g. A:, I:, R:, etc.)
  retval->type = *token;

  //get the rest of the tokens
  for(char **i=retval->argv; (token = strtok(NULL,": ")) && retval->argc < MAX_ARGS; i++,retval->argc++) {
    *i = new char[strlen(token)];
    strcpy(*i,token);
  }
  
  //return our struct
  return retval;
}

void* CServer::serverThread(void* cserver) {
  std::cout << "\nServer Thread\n";

  //get our server information
  serverinfo_t *server = (serverinfo_t*) cserver;
  
  //open our file discriptor
  FILE *filesocket = fdopen(server->fd,"r+");


  //buffer for data
  char *input = new char[BUFFER_SIZE];
  char *retval= new char[BUFFER_SIZE]; 

  std::cout << "\nquarter way though\n";

  //read a command
  fgets(input,BUFFER_SIZE,filesocket);

  std::cout << "\nhafl way through\n";

  //parse the command into a struct
  command_t *cmd = server->server->parseCommand(input);

  //process request and copy it into buffer
  std::cout << 1 << std::endl;
  retval,server->server->processRequest(cmd,retval);
  std::cout << 2 << std::endl;

  //send user buffer
  fputs(retval,filesocket);

  //clean up our mess
  fclose(filesocket);
  close(server->fd);
  server->server->deleteCommand(cmd);
  delete server, input, retval;
  std::cout << "\nFinished Cleaning Up\n";
  pthread_exit(0);
}

void CServer::runService() {

  //bind to socket
  if( bind(sockfd,(struct sockaddr*) local_addr,sizeof(struct sockaddr)) != 0 ){
    throw EServer(std::string("Could Not Bind to Port"));
  }

  //listen to port
  if( listen(sockfd, backlog) != 0) {
    throw EServer(std::string("Could Not Listen on Port"));
  }

  while(true) {
    //create a data struct for thread
    serverinfo_t *info = new serverinfo_t;
    info->server = this;

    //start blocking 
    info->fd = accept(sockfd,(struct sockaddr*) &remote_addr,&(info->sin_size));
    
    //we've got a connection, now start a thread
    pthread_t sock_thread;
    long res = pthread_create(&sock_thread, NULL,static_cast<void*(*)(void*)>(serverThread), (void*) info);
  }

}


