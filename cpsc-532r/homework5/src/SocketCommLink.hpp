#ifndef SOCKETCOMLINK_H
#define SOCKETCOMLINK_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string>
#include "CommLink.hpp"
#define BACKLOG 5
#define PORT 8549

template <class C>
class SocketComLink : public ComLink<C> {
public:
  SocketComLink();
  ~SocketComLink();
  void setSide(ComLinkSide_t c);
  //void buildDataSet();
  //void sendDataSet(unsigned int start, unsigned int end);
private:
  //server
  struct sockaddr_in *local_addr;
  struct sockaddr_in *remote_addr;
  socklen_t *sin_size;
  long server_sockfd;
  
  //client
  long client_sockfd;
  struct sockaddr_in *client_addr;
	  
};

template <class C>
SocketComLink<C>::SocketComLink() {

}

template <class C>
SocketComLink<C>::~SocketComLink() {
  //delete local_addr;
  //delete remote_addr;
}

template <class C>
void SocketComLink<C>::setSide(ComLinkSide_t c) {
  switch(c) {
  case PARENT:
    
    local_addr = new sockaddr_in;
    remote_addr = new sockaddr_in;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //serup socket structs
    local_addr->sin_family = AF_INET;
    local_addr->sin_port = htons(PORT);
    local_addr->sin_addr.s_addr = INADDR_ANY;
    memset(&(local_addr->sin_zero), '\0',8);
    
    
    
    
    //bind to socket
    if( bind(server_sockfd,(struct sockaddr*) local_addr,sizeof(struct sockaddr)) != 0 ){
      std::cerr << "Parent could not bind to port" << std::endl;
      exit(11);
      //throw std::string("Could Not Bind to Port");
    }
    
    //listen to port
    if( listen(server_sockfd, BACKLOG) != 0) {
      std::cerr << "Parent could not listen on port" << std::endl;
      exit(12);
      //throw std::string("Could Not Listen on Port");
    }
    
    //only accept one connection
    //from the child process
    //sin_size = new socklen_t;
    sin_size = new socklen_t;
    *sin_size = sizeof(sockaddr_in);
    int fd = accept(server_sockfd,(struct sockaddr*) remote_addr,sin_size);
    this->fin = fdopen(server_sockfd,"r");
    this->fout = this->fin;
    
    
    break;
  case CHILD:
    struct hostent *hostname = gethostbyname("localhost");
		
    client_addr = new sockaddr_in;
    client_addr->sin_family = AF_INET;
    client_addr->sin_port = htons(PORT);
    client_addr->sin_addr = *((struct in_addr*)hostname->h_addr);
    memset(client_addr->sin_zero,'\0',8);
	
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
      
    while(connect( client_sockfd, (struct sockaddr *)client_addr,sizeof(struct sockaddr)) == -1) {
    }	

    this->fout = fdopen(client_sockfd,"w");
    this->fin = this->fout;


    break;
  } //end switch
}//end setSide()



#endif /* SOCKETCOMLINK_H */
