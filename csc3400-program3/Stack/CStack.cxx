#include "CStack.hpp"
#include "EStack.hpp"


/****************************************
 *CStack()  - Constrcuts a stack
 *PARAM:      number of elements)
 ****************************************/
CStack::CStack(unsigned long elements) {

  maxsize = elements;
  stack = new char[elements];
  stack_top = &stack[0];
  numelements = 0;

}

/****************************************
 *~CStack() - Frees memory allocated to
 *            a stack
 ****************************************/
CStack::~CStack() {

  delete[] stack;

}

/****************************************
 *pop() - removes the top elements from 
 *        the stack
 *RETURNS: the poped element
 ****************************************/  
char CStack::pop() {
  
  if(numelements == 0) {
    throw EStack("Empty Stack");
  }

  char temp = *stack_top;
  stack_top--;
  numelements--;

  return temp;
}

/*****************************************
 *peek() - view the item on top 
 *RETURNS: the item on top of the stack
 *         without removing it
 *****************************************/
char CStack::peek() {

  if(numelements == 0) {
    throw EStack("Empty Stack");
  }

  return *stack_top;
}

/*****************************************
 *push() - adds character to stack
 *PARAM:   char to add to stack
 ****************************************/
void CStack::push(char c) {

  if(numelements == maxsize) {
    throw EStack("Stack Full");
  }

  numelements++;
  stack_top++;
  *stack_top = c;
}

/********************************************
 *isEmpty() - indicates if the stack is empty
 *RETURNS:    boolean indicating empty status
 *            of stack
 ********************************************/
bool CStack::isEmpty() {

  return (numelements == 0) ? true : false;

}

/********************************************
 *isEmpty() - indicates if the stack is full
 *RETURNS:    boolean indicating if theres 
 *            room left for more elements in
 *            the stack
 ********************************************/
bool CStack::isFull() {
  return (numelements == maxsize);
}

