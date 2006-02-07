#ifdef USE_WC
#include "count.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

count_t* parseFile(FILE *fd) {

  /* Initalize our buffers and data types */
  char *buff = malloc(sizeof(char)*BUFFER_SIZE);
  count_t *retval = malloc(sizeof(count_t));
  count->characters = 0;
  count->words = 0;
  count->lines = 0;

  /* Establish pipes */
  int pin[2];
  int pout[2];
  if(pipe(pin)) {
    perror("pipe");
    exit(2);
  }
  if(pipe(pout)) {
    perror("pipe");
    exit(3);
  }

  int forkid = fork();
  if(forkid == -1) {
    perror("fork");
    exit(4);
  }

  /* Parent fork() (read from stdin) */
  if(forkid) {

    /* pump everything into wc */
    while( fgets(buff,BUFFER_SIZE,fd) != NULL ) {
      fputs(buff,pin);
    }
    /* pull results from wc */
    fgets(buff,BUFFER_SIZE,pout);
    printf("%s",buff);

  }
  /* Child fork() (*/
  else {
    exec();
  }

  return retval;

}

#endif /* USE_WC */
