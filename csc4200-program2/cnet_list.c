#include "cnet_list.h"
#include <cnet.h>
#include <malloc.h>

/* head of linked list */
static sequence_t *head = NULL;

/* current position in list */
static sequence_t *current = NULL;

/* Gets the sequence number of a given address */
static unsigned long getSequence(CnetAddr addr) {

  sequence_t *temp = head;
  
  while(temp != NULL) {
    if( temp->address == addr ) {
      return temp->sequence;
    }
    else {
      temp = temp->next;
    }
  }
  return -1;
}

/* adds and address to our linked list */
static void addAddress(CnetAddr addr, unsigned long sequence) {
  
  /* first element to add to list (special case) */
  if( head == NULL ) {
    head = malloc(sizeof(sequence_t));
    head->address = addr;
    head->sequence = sequence;
    head->next = NULL;
    current = head;
  }
  else {
    sequence_t *temp;
    temp = malloc(sizeof(sequence_t));
    temp->address = addr;
    temp->sequence = sequence;
    temp->next = NULL;
    current->next = temp;
    current = temp;
  } 
}

/* sets an address's sequence number */
static void setSequence(CnetAddr addr, unsigned long sequence) {

  sequence_t *temp = head;
  
  while(temp != NULL) {
    if( temp->address == addr ) {
      temp->sequence = sequence;
    }
    else {
      temp = temp->next;
    }
  }
}
