#ifndef CPAL_H
#define CPAL_H

#include "CServer.h"

 
class CPalServer : public CServer {

 private:
  bool testPalindrome(char *c);

 protected:
  virtual void processRequest(command_t *t, char* retval);

 public:
  CPalServer(unsigned short port, long backlog);

};


#endif /** CPAL_H*/
