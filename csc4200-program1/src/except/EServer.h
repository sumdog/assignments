#ifndef ESVR_H
#define ESVR_H

#include <string>

class EServer {

 private:
  std::string message;

 public:
  EServer(std::string msg) : message(msg){};
  std::string getMsg();

};

#endif /** ESVR_H */
