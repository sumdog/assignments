#include "listlib.h"
#include <malloc.h>

struct node* new_node() {
  return malloc(sizeof(struct node));
}
