#include <string>

class EServer {

 private:
  std::string message;

 public:
  EServer(std::string msg) : message(msg){};
  std::string getMsg();

};
