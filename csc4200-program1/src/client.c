#include "client.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

void runClient(char *config) {

  //variables we need
  char *cfg = malloc(sizeof(char)*BUFFER);
  char *temp;
  ns_t * ns = malloc(sizeof(ns_t));

  //config files
  if(config == NULL) {
    temp = malloc(sizeof(char)*strlen(getenv("HOME")));
    strcpy(temp,getenv("HOME"));
    strcpy(cfg,temp);
    strcat(cfg,"/");
    strcat(cfg,CONFIG);
  }
  else {
    if(*config != '/') {
      getcwd(cfg,BUFFER - strlen(config));
      strcat(cfg,"/");
      strcat(cfg,config);
    }
    else {
      strcpy(cfg,config);
    }
  }

  //open config file
  FILE *fd = fopen(cfg,"r");
  if(!fd) {
    fprintf(stderr,"Error: Could not open config file %s\n",cfg);
    exit(10);
  }

  //read hostname
  temp = malloc(sizeof(char)*BUFFER);
  if( fgets(temp,BUFFER,fd) != NULL) {
    ns->nshost = malloc(sizeof(char)*strlen(temp));
    strcpy(ns->nshost,temp);
  }
  else {
    fprintf(stderr,"Error: Could not read hostname from config file %s\n",cfg);
    exit(10);
  }

  //read port
  if( fgets(temp,BUFFER,fd) != NULL ) {
    ns->nsport = (unsigned short) atol(temp); 
  }
  else {
    fprintf(stderr,"Error: Could not read port from file %s\n",cfg);
    exit(10);
  }

  //clean up our mallocing
  free(temp);
  free(cfg);
}


void freeCommand(cmd_t *t){}

cmd_t* promptUser(){}

ns_t* getNameserver(char *file){}

short serviceLookup(cmd_t *cmd, ns_t *ns){}

void runCommand(cmd_t *cmd, char *output, long bufsize){}


