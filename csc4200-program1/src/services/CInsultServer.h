#ifndef CINSULT_H
#define CINSULT_H

#include "CServer.h"

 
class CInsultServer : public CServer {

 private:
  char **insults;

 protected:
  virtual void processRequest(command_t *t, char* retval);

 public:
  CInsultServer(unsigned short port, long backlog);
  ~CInsultServer();

};


#endif /** CINSULT_H*/
