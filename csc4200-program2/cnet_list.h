#ifndef CNET_LIST
#define CNET_LIST
#include <cnet.h>

typedef struct sequence {
  CnetAddr address;
  unsigned long sequence;
  struct sequence *next;
} sequence_t;


unsigned long getSequence(CnetAddr addr);

void addAddress(CnetAddr addr, unsigned long sequence);

void setSequence(CnetAddr addr, unsigned long sequence);

#endif /* CNET_LIST */
