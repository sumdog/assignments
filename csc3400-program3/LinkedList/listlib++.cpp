#include "listlib.h"
#include "listlib++.hpp"

CLinkList::CLinkList() {
  list = lst_null(new_node());
}

CLinkList::CLinkList(CLinkList l1, CLinkList l2) {
  
}

CLinkList::~CLinkList(){
  lst_free(list);
}

void CLinkList::addElement(atom_t a) {
  lst_add(list,a);
}

void CLinkList::deleteElement(atom_t a) {
  
}

bool CLinkList::isEqual(CLinkList l1) {

}

unsigned long CLinkList::numelements() {
  return lst_count(list);
}
