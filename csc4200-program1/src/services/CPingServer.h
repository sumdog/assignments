#ifndef CPING_H
#define CING_H

#include "CServer.h"

 
class CPingServer : public CServer {

 protected:
  virtual void processRequest(command_t *t, char* retval);

 public:
  CPingServer(unsigned short port, long backlog);

};


#endif /** CPING_H*/
