#include "count.h" 
#include <stdlib.h>
#include <string.h>

#ifndef USE_WC

void checkLine(char *line, count_t *counter) {
  
  int x;
  for(x=0; x<strlen(line);x++) {
    char cur = line[x];
    /* Deal with Characters */
    if(cur != ' ' && cur != '\n' ) {
      counter->characters++;
    }
    /* Deal with lines*/
    if(cur == '\n') {
      counter->lines++;
    }
    /* Deal with words
     *  Note: I define a word as anything
     *  that begins and ends with either a 
     *  space or new line
     */
    if(cur == '\n' || cur == ' ') {
      counter->words++;
    }
  }/* end for loop */
}

count_t* parseFile(FILE *fd) {
  
  /* Initalize our buffers and data types */
  char *buff = malloc(sizeof(char)*BUFFER_SIZE);
  count_t *count = malloc(sizeof(count_t));
  count->characters = 0;
  count->words = 0;
  count->lines = 0;
  
  while( fgets (buff,BUFFER_SIZE,fd) != NULL ) {
    checkLine(buff,count);
  }
  return count;
}

#endif /* USE_WC */
