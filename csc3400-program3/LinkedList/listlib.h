/*******************************************
 *C Functions to handle a linked list
 *
 * exter "C" is defined when a c++ compiler
 * is used to make these functions avaiable 
 * to c++ classes
 *******************************************/
#ifndef LISTLIB_C
#define LISTLIB_C

#if defined __cplusplus
extern "C" {
#endif

typedef long atom_t;

struct node {
  atom_t element;
  struct node *next;
};

typedef struct {
  struct node *head;
  long numelements;
} list_t;

struct node* new_node();

void lst_free(list_t *ll);

int lst_equal(list_t *l1, list_t *l2);

list_t* lst_copy(list_t *l1, list_t *l2);

list_t* lst_concat(list_t *l1, list_t *l2, list_t *l3);

unsigned long lst_count(list_t *ll);

void delete_node(struct node *node);

list_t* lst_null(struct node *node);

void lst_add(list_t *ll, atom_t a);

void lst_display(list_t *ll);

void lst_delete(atom_t a, list_t *l1, list_t *l2);

#if defined __cplusplus
}
#endif

#endif
