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
#include "ERegister.h"
#include <unistd.h>

CServer::CServer(unsigned short port, long backlog) {

  //setup class variables
  local_addr = new sockaddr_in;
  remote_addr = new sockaddr_in;
  this->backlog = backlog;
  strcpy(name,"default");
  this->port = port;

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
  strcpy(retval,"A:Override this method to implement\n");
}

void CServer::deleteCommand(command_t *t) {
  //delete all strings
  char **i;
  short x;
  for(x=0, i=t->argv;  x<t->argc;   x++,i++) {
    delete[] *i;
  }
  delete[] t->argv;
  
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
    *i = new char[strlen(token)+1];
    strcpy(*i,token);
  }
  
  //return our struct
  return retval;
}

void* CServer::serverThread(void* cserver) {
  
  //get our server information
  serverinfo_t *server = (serverinfo_t*) cserver;
  
  char *input = new char[BUFFER_SIZE];
  char *retval= new char[BUFFER_SIZE];
  
  //open our stream
  FILE *stream = fdopen(server->fd,"r+");
  
  //read user request
  fgets(input,BUFFER_SIZE,stream);

  command_t *cmd = server->server->parseCommand(input);

  //process request and copy it into buffer
  retval,server->server->processRequest(cmd,retval);

  //send user buffer
  fputs(retval,stream);

  //clean up our mess
  fclose(stream);
  close(server->fd);
  
  delete[] input, retval;
  delete server;
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
    info->sin_size = sizeof(struct sockaddr_in);
    info->fd = accept(sockfd,(struct sockaddr*) remote_addr,&(info->sin_size));
 
    if(info->fd != -1) { 
      //we've got a connection, now start a thread
      pthread_t sock_thread;
      long res = pthread_create(&sock_thread, NULL,static_cast<void*(*)(void*)>(serverThread), (void*) info);
    }
    else {
      printf("%d\n",sockfd);
      throw EServer(std::string("Accept Call Failed"));
    }
  }

}


void CServer::registerService(char* host, unsigned short port) {
  //who am i
  char me[100];
  gethostname(&me[0],100);

  //resolve hostname
  struct hostent *hostname = gethostbyname(host);
  if(!hostname) {
    //error looking up host
    throw ERegister(std::string("Invalid Nameserver Hostname"));
  }

  //fill our our socket connection struct
  struct sockaddr_in nameserver;
  nameserver.sin_family = AF_INET;
  nameserver.sin_port   = htons(port);
  nameserver.sin_addr   = *((struct in_addr*)hostname->h_addr);
  memset(nameserver.sin_zero,'\0',8);

  //connect to name server
  long sfd = socket(AF_INET, SOCK_STREAM, 0);
  if( connect(sfd, (struct sockaddr *)&nameserver, sizeof(struct sockaddr)) == -1 ) {
    throw ERegister(std::string("Could Not Connect To Nameserver"));
  }
  else {
    //send our registration data
    char regdata[BUFFER_SIZE];
    sprintf(regdata,"R:%s:%s:%d\n",name,me,this->port);
    
    FILE *stream = fdopen(sfd,"w");
    fputs(regdata,stream);
    //sendAll(sockfd,regdata);
    
    fclose(stream);
    close(sfd);
  }
}


bool CServer::sendAll(long fd, char* buffer) {

  //here, we'll makre sure all our data is sent
  long total = 0;    
  long length = strlen(buffer);
  long bytesleft = length;
  long n;

        while(total < length) {
            n = send(fd, buffer+total, bytesleft, 0);
            if (n == -1) { break; }
            total += n;
            bytesleft -= n;
        }

        return (n == -1) ? false : true; 
}
