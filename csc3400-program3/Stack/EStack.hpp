/***************************
 *EStack - Stack Exception
 ***************************/
#ifndef ESTACK_H
#define ESTACK_H


#include <string>

class EStack {

 private:
  std::string message;

 public:
  EStack(std::string msg) : message(msg) {};
  std::string getMsg();
};

#endif
