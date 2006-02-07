#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef HAVE_WC

#include "count.h" 
#include <stdlib.h>
#include <string.h>


void checkLine(char *line, count_t *counter) {
  int x;
  for(x=0; x<strlen(line);x++) {
    
    char cur = line[x];
    
    /* Deal with Characters */
    counter->characters++;

    /* Deal with lines*/
    if(cur == '\n') {
      counter->lines++;
    }
    /* Deal with words
     *  Note: I define a word as anything
     *  that begins and ends with either a 
     *  space or new line
     */

    if(cur != '\n' && cur != ' ' && cur != '\t' && counter->wtoke == 0) {
      counter->words++;
      counter->wtoke = 1;
    }
    else if(cur != '\n' && cur != ' ' && cur != '\t' && counter->wtoke == 1)  {
      
    }
    else {
      counter->wtoke = 0;
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
  count->wtoke = 0;
  
  while( fgets (buff,BUFFER_SIZE,fd) != NULL ) {
    checkLine(buff,count);
  }
  return count;
}

#endif /* HAVE_WC */
