#ifndef LISTLIB_C
#define LISTLIB_C

typedef long atom_t;

typedef struct node {
  atom_t element;
  struct node *next;
} node_t;

typedef struct {
  struct node *head;
  struct node *tail;
  long numelements;
} list_t;

struct node* new_node();

//void 1st_null(struct node *node)

#endif
