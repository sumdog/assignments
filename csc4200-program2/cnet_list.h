#ifndef CNET_LIST
#define CNET_LIST
#include <cnet.h>

typedef struct sequence {
  CnetAddr address;
  unsigned long sequence;
  struct sequence *next;
} sequence_t;

static unsigned long getSequence(CnetAddr addr);

static void addAddress(CnetAddr addr, unsigned long sequence);

static void setSequence(CnetAddr addr, unsigned long sequence);

#endif /* CNET_LIST */
