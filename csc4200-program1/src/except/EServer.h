class EServer {

 private:
  char *message;

 public:
  EServer(char *msg);
  ~EServer();
  char* getMsg();

};
