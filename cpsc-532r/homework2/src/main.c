#include <stdio.h>
#include "count.h"

int main() {

  if(isatty(fileno(stdin))) {
    printf("CPSC-532r Char/Word/Line Counter\n");
    printf("\tSumit Khanna\n");
  }

   count_t *counter = parseFile(stdin);
   printf("Number of Characters:%d\n",counter->characters);
   printf("Number of Words:%d\n",counter->words);
   printf("Number of Lines:%d\n",counter->lines);
}
