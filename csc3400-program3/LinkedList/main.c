#include <stdio.h>
#include <unistd.h>
#include "listlib.h"

#define BUF_SIZE 100

int main() {

  int tty = isatty(fileno(stdin)); //< indicates if we're interactive

  //prompt user
  if(tty) {
    printf("Linked List -- Interactive Mode\n");
    printf("Enter a list, one integer per line\n");
    printf("Exit with ^D\n");
    printf(">>>");
  }

  //setup list
  list_t *list = lst_null(new_node());

  //read list
  char buffer[BUF_SIZE];
  while( fgets(&buffer[0], BUF_SIZE, stdin) != NULL ) {
    lst_add(list,(atom_t) atol(buffer));
    if(tty) { printf(">>>"); }
  }

  //display list
  printf("\nLinked List:\n");
  lst_display(list);
  printf("Number of Elements: %d\n",lst_count(list));
  printf("\n");

  //if interactive, we can ask them to delete 
  //entries too
  if(tty) {
    list_t *deleted = lst_null(new_node());
    lst_copy(list,deleted);
    printf("Linked List -- Interactive Mode\n");
    printf("Enter a list of integers to be deleted\n");
    printf("One per line. End with ^D\n>>>");
    
    while( fgets(&buffer[0], BUF_SIZE, stdin) != NULL ) {
      list_t *templist = lst_null(new_node());
      lst_delete((atom_t) atol(buffer),deleted,templist);
      lst_free(deleted);
      deleted = lst_null(new_node());
      lst_copy(templist,deleted);
      lst_free(templist);
      printf(">>>");
    }
    
    printf("\n\nOriginal Linked List:\n");
    lst_display(list);
    printf("Number of Elements: %d\n",lst_count(list));
    printf("\n");
    printf("New Linked List:\n");
    lst_display(deleted);
    printf("Number of Elements: %d\n",lst_count(deleted));
    printf("\n");
    printf("Lists are ");
    if(lst_equal(list,deleted) == 0 ) {
      printf("not ");
    }
    printf("equal.\n\n");
    printf("Concatinated Linked List:\n");
    list_t *cat = lst_null(new_node());
    lst_concat(list,deleted,cat);
    lst_display(cat);
    lst_free(deleted);
    lst_free(cat);
  }//end concatinated list



  //clean up mess
  lst_free(list);
}
