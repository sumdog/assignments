#ifndef CSVR_H
#define CSVR_H

#include <sys/types.h>
#include <sys/socket.h>

#define NAME_SIZE 20
#define BUFFER_SIZE 256
#define MAX_ARGS 50
#define CMD_ERR 'E'
#define CMD_IVK 'I'
#define CMD_ANS 'A'
#define CMD_REQ 'R'
#define CMD_LOK 'L'


typedef struct command {
  char type;
  short argc;
  char **argv;
} command_t;

class CServer {

 private:
  struct sockaddr_in *local_addr;
  struct sockaddr_in *remote_addr;
  long sockfd;
  long backlog;
  unsigned short port;

  static void* serverThread(void* cserver);
  command_t* parseCommand(char *cmd);
  void deleteCommand(command_t *t);

 protected:
  virtual void processRequest(command_t *t, char *retval);
  char name[NAME_SIZE];

 public:
  CServer(unsigned short port, long backlog);
  ~CServer();
  void runService();
  void registerService(char* host, unsigned short port);
};

typedef struct serverinfo {
  socklen_t sin_size;
  long fd; 
  CServer *server;
} serverinfo_t;




#endif /** CSVR_H */
