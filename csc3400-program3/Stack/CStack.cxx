#include "CStack.h"
#include "EStack.h"



CStack::CStack(unsigned long elements) {

  maxsize = elements;
  stack = new char[elements];
  stack_top = &stack[0];
  numelements = 0;

}

CStack::~CStack() {

  delete[] stack;

}

char CStack::pop() {
  
  if(numelements == 0) {
    throw EStack("Empty Stack");
  }

  char temp = *stack_top;
  stack_top--;
  numelements--;

  return temp;
}

char CStack::peek() {

  if(numelements == 0) {
    throw EStack("Empty Stack");
  }

  return *stack_top;
}

void CStack::push(char c) {

  if(numelements == maxsize) {
    throw EStack("Stack Full");
  }

  numelements++;
  stack_top++;
  *stack_top = c;
}

bool CStack::isEmpty() {

  return (numelements == 0) ? true : false;

}

bool CStack::isFull() {
  return !(isEmpty());
}

