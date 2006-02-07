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
  retval->characters = 0;
  retval->words = 0;
  retval->lines = 0;

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
    
    /* Close ends of the pipe we can't use */
    close(pin[0]);
    close(pout[1]);

    /* Open ends of the piple we do use */
    FILE *fdin = fdopen(pin[1],"w");
    FILE *fdout = fdopen(pout[0],"r");

    /* pump everything into wc */
    while( fgets(buff,BUFFER_SIZE,fd) != NULL ) {
      fputs(buff,fdin);
    }
    fclose(fdin);

    /* pull results from wc */
    fgets(buff,BUFFER_SIZE,fdout);
    sscanf(buff,"%u %u %u",&retval->lines,&retval->words,&retval->characters);
    fclose(fdout);

    free(buff);

  }
  /* Child fork() (exec wc) */
  else {

    /* Close unused ends of pipe */
    close(pin[1]);
    close(pout[0]);

    /* Attach pipes to stdio  */
    dup2(pin[0], STDIN_FILENO);
    dup2(pout[1],STDOUT_FILENO);

    /* execute wc */
    execl("/usr/bin/wc","wc",(char *) NULL);
  }

  return retval;

}

#endif /* USE_WC */
