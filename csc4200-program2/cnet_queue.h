#ifndef CNET_QUEUE
#define CNET_QUEUE
#include <cnet.h>
#include <malloc.h>

typedef struct packet {
  CnetAddr dest;
  int length;
  char *msg;  
  struct packet *next;
  struct packet *prev;
} packet_t;

void enqueuePacket(char* msg, int length, CnetAddr dest);

packet_t dequeuePacket();
/*
void enqueuePiggyBack(CnetAddr addr, unsigned long sequence);
*/



#endif /* CNET_QUEUE */
