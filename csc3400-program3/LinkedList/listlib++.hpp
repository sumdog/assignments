#ifndef LISTLIB__H
#define LISTLIB__H

#include "listlib.h"

class CLinkList {
  
public:
  CLinkList();
  ~CLinkList();
  void addElement(atom_t a);
  void deleteElement(atom_t a);
  unsigned long numelements();
  CLinkList operator+(CLinkList l);
  bool operator==(CLinkList l);
  bool operator!=(CLinkList l);

private:
  list_t *list;
  CLinkList(list_t *l);

};




#endif
