/************************************
 *CStack - a class to handle a stack
 *  see CStack.cxx for function
 *  discriptions
 ***********************************/

#ifndef CSTACK_H
#define CSTACK_H


class CStack {

 public:
  CStack(unsigned long elements);
  ~CStack();
  bool isEmpty();
  bool isFull();
  char pop();
  char peek();
  void push(char c);

 private:
  char *stack;
  char *stack_top;
  unsigned long numelements;
  unsigned long maxsize;

};

#endif
