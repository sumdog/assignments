class CServer {

 private:
  struct sockaddr_in *local_addr;
  struct sockaddr_in *remote_addr;
  long sockfd;

 public:
  CServer(char* hostname, unsigned short port);
  ~CServer();

 protected:



};
