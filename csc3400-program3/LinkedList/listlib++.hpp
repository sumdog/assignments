/***************************************
 *CLinkList class - a linked list
 *   wrapper for our C functions
 *CListIterator - a way to iterate 
 *   though our list
 *
 * see listlib++.cpp for functions 
 ***************************************/

#ifndef LISTLIB__H
#define LISTLIB__H

#include "listlib.h"


class CListIterator {
public:
  CListIterator(list_t *l);
  ~CListIterator();
  atom_t getElement();
  void operator++();
  bool hasMore();

private:
  list_t *list;
  struct node *current;
};


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
  CListIterator getIterator();

private:
  list_t *list;
  CLinkList(list_t *l);

};

#endif
