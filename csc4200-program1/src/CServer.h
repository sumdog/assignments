#include <sys/types.h>
#include <sys/socket.h>

class CServer {

 private:
  struct sockaddr_in *local_addr;
  struct sockaddr_in *remote_addr;
  long sockfd;
  long backlog;

  static void* server_thread(void* cserver);


 public:
  CServer(char* ip, unsigned short port, long backlog);
  ~CServer();
  void runService();
  virtual char* processRequest(char *arg, unsigned short argc, char **argv);
};


typedef struct serverinfo {
  socklen_t sin_size;
  long fd; 
  CServer *server;
} serverinfo_t;



