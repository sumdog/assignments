#ifndef LISTLIB__H
#define LISTLIB__H

#include "listlib.h"

class CLinkList {
  
public:
  CLinkList();
  CLinkList(CLinkList l1, CLinkList l2);
  ~CLinkList();
  void addElement(atom_t a);
  void deleteElement(atom_t a);
  bool isEqual(CLinkList ll);
  unsigned long numelements();

private:
  list_t *list;
  
protected:

}




#endif
