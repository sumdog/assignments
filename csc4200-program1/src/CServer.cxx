#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include "CServer.h"
#include "except/EServer.h"
#include <pthread.h>
#include "unistd.h"

//using std::cout;

CServer::CServer(char* hostname, unsigned short port, long backlog) {

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

char* CServer::processRequest(char *arg, unsigned short argc, char **argv) {
  return "Override this method to implement";
}

void* CServer::server_thread(void* cserver) {
  //get our server information
  serverinfo_t *server = (serverinfo_t*) cserver;

 
  //kill ourself
  close(server->fd);
  pthread_exit(0);
}

void CServer::runService() {

  //bind to socket
  if( bind(sockfd,(struct sockaddr*) local_addr,sizeof(struct sockaddr)) != 0 ){
    throw EServer("Could Not Bind to Port");
  }

  //cout << "here";

  //listen to port
  if( listen(sockfd, backlog) != 0) {
    throw EServer("Could Not Listen on Port");
  }

  while(true) {
    //create a data struct for thread
    serverinfo_t *info = new serverinfo_t;
    info->server = this;

    //start blocking 
    long remotefd = accept(sockfd,(struct sockaddr*) &remote_addr,info->sin_size);
    
    //we've got a connection, now start a thread
    pthread_t sock_thread;
    long res = pthread_create(&sock_thread, NULL, &server_thread, (void *)info);
  }

}
