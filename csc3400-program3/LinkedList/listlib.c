#include "listlib.h"
#include <malloc.h>
#include <stdio.h>

/*******************************************
 * new_node() - allocates memory for a node
 * PARAMS:      none
 * RETURNS:     a pointer to an allocated
 *              node
 *******************************************/ 
struct node* new_node() {
  return malloc(sizeof(struct node));
}

/*******************************************
 * delete_node() - frees memory for a node
 * PARAMS:      pointer to node
 * RETURNS:     none
 *******************************************/ 
void delete_node(struct node *node) {
  free(node);
}

/*******************************************
 * lst_null()   - allocates memory for a list
 * PARAMS:      pointer to an node that was
 *              returned from new_node()
 * RETURNS:     list_t* containing one node
 *              with it's contents zeroed out
 *******************************************/ 
list_t* lst_null(struct node *node) {
  list_t *temp = malloc(sizeof(list_t));
  node->element = 0;
  node->next = NULL;
  temp->head = node;
  temp->numelements = 0;
  return temp;
}


/*******************************************
 * lst_add()    - adds atom to list
 * PARAMS:      Pointer to a list previously
 *              created with lst_null() and
 *              an atom_t (long 32-bit int).
 * RETURNS:     nothing
 * ALGROTHYM:   Calls new_node(), places
 *              the atom inside it and 
 *              resets the head, tail and 
 *              next pointers to insert the 
 *              new node into the list.
 *******************************************/ 
void lst_add(list_t *ll, atom_t a) {
  
  //find end of list
  struct node *eol = ll->head; //<end of list
  while(eol != NULL && eol->next != NULL) {
    eol = eol->next;
  }

  //create new node to add
  struct node *temp = new_node();
  temp->element = a;
  temp->next = NULL;

  //add the node
  if(eol == NULL) {
    ll->head = temp;
  }
  else {
    eol->next = temp;
  }

  //increment num elements
  ll->numelements++;
}

/*******************************************
 * lst_display() - displays the list
 * PARAMS:      Pointer to a list 
 * RETURNS:     nothing
 * ALGROTHYM:   Iterates through each node
 *              until the next node is a 
 *              null pointer
 *******************************************/ 
void lst_display(list_t *ll) {
  printf("{ ");
  struct node *element = ll->head->next;
  while(element != NULL) {
    printf("%d ",element->element);
    element = element->next;
  }
  printf("}\n");
}

/*******************************************
 * lst_count() - returns number of elements
 * PARAMS:      Pointer to a list 
 * RETURNS:     number of elements in list
 * ALGROTHYM:   returns an instance variable
 *              that's updated on every 
 *              addition to the list
 *******************************************/ 
unsigned long lst_count(list_t *ll) {
  return ll->numelements;
}

list_t* lst_copy(list_t *l1, list_t *l2) {
  
  //get our start pointers
  struct node *el1 = l1->head->next;
  struct node *el2 = l2->head;

  while(el1 != NULL) {
    struct node *temp = new_node();
    temp->element = el1->element;
    temp->next = NULL;
    el2->next = temp;
    el2 = temp;
    el1 = el1->next;
    l2->numelements++;
  }
  
  //return the copy of the list
  return l2;
}

void lst_free(list_t *ll) {
  struct node *iter = ll->head;
  while(iter != NULL) {
    struct node *temp = iter;
    iter = iter->next;
    free( temp );
  }
  free(ll);
}

void lst_delete(atom_t a, list_t *l1, list_t *l2) {
  
  //grab starting point of list one
  struct node *elm1 = l1->head->next;

  //grab ending point of list two
  struct node *elm2 = l2->head;
  while( elm2->next != NULL) {
    elm2 = elm2->next;
  }

  //iterate through list one, removing 
  //the offending atom and copying 
  //everything else into list two
  while(elm1 != NULL) {
    if(elm1->element != a) {
      //create our temp node and copy into it
      struct node *temp = new_node();
      temp->next = NULL;
      temp->element = elm1->element;
      //put this node at the end of list two
      elm2->next = temp;
      elm2 = temp;
      l2->numelements++;
    }
     
    //increment out list
    elm1 = elm1->next;
  }
}


int lst_equal(list_t *l1, list_t *l2) {

  struct node *cp1 = l1->head;
  struct node *cp2 = l2->head;

  while(cp1 != NULL || cp2 != NULL) {
    //return false if one list is longer
    //than the other
    if(cp1 == NULL || cp2 == NULL) {
      return 0;
    }
    if(cp1->element != cp2->element) {
      return 0;
    }
    cp1 = cp1->next;
    cp2 = cp2->next;
  }

  return 1;
}


list_t* lst_concat(list_t *l1, list_t *l2, list_t *l3) {

  //setup initial pointers
  struct node *start1 = l1->head->next;
  struct node *start2 = l2->head->next;
  struct node *end3   = l3->head;
  while(end3->next != NULL) { end3 = end3->next; }

  while(start1 != NULL) {
    struct node *temp = new_node();
    temp->next = NULL;
    temp->element = start1->element;
    end3->next = temp;
    end3 = end3->next;
    start1 = start1->next;
  }
  while(start2 != NULL) {
    struct node *temp = new_node();
    temp->next = NULL;
    temp->element = start2->element;
    end3->next = temp;
    end3 = end3->next;
    start2 = start2->next;
  }
  return l3;
}
