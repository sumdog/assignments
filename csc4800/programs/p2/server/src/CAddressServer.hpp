#ifndef CADDRESS_H
#define CADDRESS_H

#include "CServer.hpp"
#include <string>
#include <map>
#include <pthread.h>
using std::string;
using std::map;

typedef struct entry {
  /* int ssn; */
  string *fname;
  string *lname;
  int housenum;
  string *street;
  int zip;
  string *city;
  string *state;
} entry_t;

typedef map<int,entry_t*> addressbook_t;

class CAddressServer : public CServer {
private:
  addressbook_t *book;
  pthread_mutex_t lock;
  bool isNumeric(char *s);
  bool isAlpha(char *s, bool spaces);
  bool isAlphaNumeric(char *s);
public:
  CAddressServer(unsigned short port, long backlog);
  ~CAddressServer();
protected:
  bool processRequest(command_t *t, char* retval);
};




#endif /* CADDRESS_H */
