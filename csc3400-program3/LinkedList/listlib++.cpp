/*****************************************
 *These LinkList and ListIterator classes
 *are implemented as wrappers for the C
 *classes by abstracting data using 
 *private fields. They are linked to the C
 *shared object files (.so) at compile time
 ******************************************/

#include "listlib.h"
#include "listlib++.hpp"
#include <cstdlib>

CLinkList::CLinkList() {
  list = lst_null(new_node());
}

CLinkList::CLinkList(list_t *l) {
  list = l;
}

CLinkList::~CLinkList(){
  lst_free(list);
}

bool CLinkList::operator==(CLinkList l) {
  return (lst_equal(this->list,l.list) == 0) ? false : true;
}

bool CLinkList::operator!=(CLinkList l) {
  return !(*this == l);
}

CLinkList CLinkList::operator+(CLinkList l) {
  list_t *cat = lst_null(new_node());
  lst_concat(this->list,l.list,cat);
  return CLinkList(cat);
}

void CLinkList::addElement(atom_t a) {
  lst_add(list,a);
}

void CLinkList::deleteElement(atom_t a) {
  list_t *temp = lst_null(new_node());
  lst_delete(a,list,temp);
  lst_free(list);
  list = temp;
}

unsigned long CLinkList::numelements() {
  return lst_count(list);
}

CListIterator CLinkList::getIterator() {
  return CListIterator(list);
}

CListIterator::CListIterator(list_t *l) {
  list = lst_null(new_node());
  lst_copy(l,list);
  current = list->head->next;
}

CListIterator::~CListIterator() {
  lst_free(list);
}

atom_t CListIterator::getElement(){
  return current->element;
}

void CListIterator::operator++() {
  current = current->next;
}

bool CListIterator::hasMore() {
  return (current->next == NULL) ? false : true;
}
