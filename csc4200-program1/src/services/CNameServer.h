#include "CServer.h"
#include <map>
#include <string>

using std::string;
using std::map;
 
//the struct to hold name information
typedef struct service {
  char *host;
  unsigned short port;
} service_t;

//strongly type our specific template
typedef map<string,service_t*> servicemap_t;

class CNameServer : public CServer {

 private:
  servicemap_t *servicemap;

 protected:
  virtual void processRequest(command_t *t, char* retval);

 public:
  CNameServer(char* ip, unsigned short port, long backlog);

};


