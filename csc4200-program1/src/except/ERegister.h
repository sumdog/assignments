#ifndef EREG_H
#define EREG_H

#include <string>

class ERegister {

 private:
  std::string message;

 public:
  ERegister(std::string msg) : message(msg){};
  std::string getMsg();

};

#endif /** EREG_H */
