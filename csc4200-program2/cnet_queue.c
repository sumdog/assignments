#include "cnet_queue.h"
#include <string.h>
#include <cnet.h>

static packet_t *head = NULL;
static packet_t *curr = NULL;

void enqueuePacket(char* msg, int length, CnetAddr dest) {

  if( head == NULL ) {
    head = malloc(sizeof(packet_t));
    curr = head;
    curr->prev = NULL;
  }
  else {
    curr->next = malloc(sizeof(packet_t));
    curr->next->prev = curr;
    curr = curr->next;
  }

  curr->length = length;
  curr->next = NULL;
  curr->msg = malloc(sizeof(char)*length);
  
  memcpy(curr->msg, msg, length);
}


packet_t dequeuePacket() {

  packet_t retval;

  if ( curr == NULL ) {
    retval.length = -1;
    return retval;
  }
    
  retval.next = NULL;
  retval.prev = NULL;
  retval.length = curr->length;
  
  retval.msg = malloc(sizeof(char)*curr->length);
  
  memcpy(retval.msg, curr->msg, retval.length); 
  

  packet_t *temp = curr;
  if( curr == head ) {
    head = NULL;
  }
  curr = curr->prev;
  free( temp->msg );
  free( temp );

  return retval;
}
