#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

class EServer {

 private:
  std::string message;

 public:
  EServer(std::string msg) : message(msg){};
  std::string getMsg();

};


class ERegister {

 private:
  std::string message;

 public:
  ERegister(std::string msg) : message(msg){};
  std::string getMsg();

};

#endif /** EXCEPTIONS_H **/
