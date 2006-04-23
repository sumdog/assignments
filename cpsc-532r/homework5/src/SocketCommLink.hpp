#ifndef SOCKETCOMLINK_H
#define SOCKETCOMLINK_H
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string>
#include "CommLink.hpp"
#define BACKLOG 5
#define PORT 8533

template <class C>
class SocketComLink : public ComLink<C> {
public:
  SocketComLink();
  ~SocketComLink();
  void setSide(ComLinkSide_t c);
  void buildDataSet();
  void sendDataSet(unsigned int start, unsigned int end);
private:
  struct sockaddr_in *local_addr;
  struct sockaddr_in *remote_addr;
  long sockfd;
};

template <class C>
SocketComLink<C>::SocketComLink() {

  local_addr = new sockaddr_in;

  //serup socket structs
  local_addr->sin_family = AF_INET;
  local_addr->sin_port = htons(PORT);
  memset(&(local_addr->sin_zero), '\0',8);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

template <class C>
SocketComLink<C>::~SocketComLink() {
  delete local_addr;
  delete remote_addr;
}

template <class C>
void SocketComLink<C>::setSide(ComLinkSide_t c) {
  switch(c) {
  case PARENT:
    local_addr->sin_addr.s_addr = INADDR_ANY;

    //bind to socket
    if( bind(sockfd,(struct sockaddr*) local_addr,sizeof(struct sockaddr)) != 0 ){
	  std::cerr << "Parent could not bind to port" << std::endl;
	  exit(11);
      //throw std::string("Could Not Bind to Port");
    }

    //listen to port
    if( listen(sockfd, BACKLOG) != 0) {
	  std::cerr << "Parent could not listen on port" << std::endl;
	  exit(12);
      //throw std::string("Could Not Listen on Port");
    }

    //only accept one connection
    //from the child process
	socklen_t ssize;
    int fd = accept(sockfd,(struct sockaddr*) remote_addr,&ssize);
    FILE *pfo = fdopen(sockfd,"w");
	FILE *pfi = fdopen(sockfd,"r");
	
	this->stdfbo = new stdio_filebuf<char>(pfo,std::ios::out);
	this->stdfbi = new stdio_filebuf<char>(pfi,std::ios::out);
	
    this->writer.std::ios::rdbuf(this->stdfbo);
	this->reader.std::ios::rdbuf(this->stdfbi);

    break;
  case CHILD:
    struct hostent *hostname = gethostbyname("localhost");
    local_addr->sin_addr = *((struct in_addr*)hostname->h_addr);
    while(true) {
		cout << "Attempting to connect\n" << endl;
      if( connect( sockfd, (struct sockaddr *)local_addr,sizeof(struct sockaddr)) == 1){
        cout << "connection established\n" << endl;
	    FILE *cfo = fdopen(sockfd,"w");
	    FILE *cfi = fdopen(sockfd,"r");
	
	    this->stdfbo = new stdio_filebuf<char>(cfo,std::ios::out);
  	    this->stdfbi = new stdio_filebuf<char>(cfi,std::ios::out);
	
        this->writer.std::ios::rdbuf(this->stdfbo);
	    this->reader.std::ios::rdbuf(this->stdfbi);
		break;
      }
	  else {
		continue;
	  }
    }
    //else {
	//  std::cerr << "Child could not contact parent" << std::endl;
	//  exit(10);
      //throw std::string("Child could not contact parent");
    //}
    break;
  } //end switch
}//end setSide()



#endif /* SOCKETCOMLINK_H */
