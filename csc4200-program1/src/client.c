#include "client.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

ns_t* getNameserver(char *config) {

  //variables we need
  char *cfg = malloc(sizeof(char)*BUFFER);
  char *temp;
  ns_t * ns = malloc(sizeof(ns_t));

  //config files
  if(config == NULL) {
    temp = malloc(sizeof(char)*strlen(getenv("HOME"))+1);
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
  temp = malloc(sizeof(char)*BUFFER+1);
  if( fgets(temp,BUFFER,fd) != NULL) {
    ns->nshost = malloc(sizeof(char)*strlen(temp)+1);
    strcpy(ns->nshost,temp);
    ns->nshost[strlen(ns->nshost)-1] = '\0'; //trim newline
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

  //return nameserver struct
  return ns;
}


void freeNameserver(ns_t *t) {
  free(t);
}

void freeCommand(cmd_t *t){
  free(t->service);
  free(t->command);
  if(t->host != NULL) {
    free(t->host);
  }
  free(t);
}

cmd_t* promptUser(){
  
  //struct to return and other vars
  cmd_t *retval = malloc(sizeof(cmd_t));
  retval->host = NULL;
  char *temp = malloc(sizeof(char)*BUFFER);
  char *t;
  
  while(1) {    
    //interactive prompt
    if(isatty(fileno(stdin))) {
      printf(">>>");
    }
    
    //user input
    if( fgets(temp,BUFFER,stdin) == NULL) {
      return NULL;
    }
    
    //service and command
    if( (t = strtok(temp," ")) != NULL ) {
      retval->service = malloc(sizeof(char)*strlen(t)+1);
      strcpy(retval->service,t);
      if( (t = strtok(NULL,"")) != NULL) {
	retval->command = malloc(sizeof(char)*strlen(t)+1);
	strcpy(retval->command,t);
	break;
      }
    }
    
    //invlaid command
    printf("Invalid Command\n");

  }//end while()

  //clean up mess
  free( temp );

  //done
  return retval;
}


//Return 0 on success
//       -1 = invalid hostname
//       -2 = cound not connect
//       -3 = I/O error
short socketConnect(char *host,unsigned short port,char *sendbuf,char *recievebuf, long rbufsize) {
  //get host
  struct hostent *hostname = gethostbyname(host);
  if(hostname == NULL) { return -1; }

  //connection struct
  struct sockaddr_in nameserver;
  nameserver.sin_family = AF_INET;
  nameserver.sin_port   = htons(port);
  nameserver.sin_addr   = *((struct in_addr*)hostname->h_addr);
  memset(nameserver.sin_zero,'\0',8);

  //connect to name server
  long sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if( connect(sockfd, (struct sockaddr *)&nameserver, sizeof(struct sockaddr)) == -1 ) {
    return -2; 
  }
  
  //open file stream;
  FILE *nstream = fdopen(sockfd,"r+");
  if(nstream == NULL) {
    close(sockfd); 
    return -3;
  }

  //send request
  printf("%s333\n",sendbuf);
  if( fputs(sendbuf,nstream) == EOF) {
    fclose(nstream);
    close(sockfd);
    return -3;
  }

  //get response
  if( fgets(recievebuf,rbufsize,nstream) == NULL ) {
    fclose(nstream);
    close(sockfd);
    return -3;
  }

  //close the conncetion (we're done with it)
  fclose(nstream);
  close(sockfd);
  return 0;

}

//Return 0 on success
//       -1 on invalid nameserver hostname
//       -2 could not connect to server
//       -3 error during lookup
//       -4 invalid data from nameserver
//       -5 unknown service
short serviceLookup(cmd_t *cmd, ns_t *ns){

  //setup I/O buffers
  char sndbuf[BUFFER];
  char recbuf[BUFFER];
  sprintf(sndbuf,"L:%s\n",cmd->service);  
 
  //send/recieve information from service
  short c = socketConnect(ns->nshost,ns->nsport,&sndbuf[0],&recbuf[0],BUFFER);
  if(c != 0) { return c; } //error

  //parse response
  char *i = strtok(&recbuf[0],":\n"); //response type
  if(i == NULL) { return -4; }
  if(strcmp(i,"A") != 0) { return -5; }
  i = strtok(NULL,":\n"); //hostname
  if(i == NULL) { return -4; }
  cmd->host = malloc(sizeof(char)*strlen(i)+1);
  strcpy(cmd->host,i);
  i = strtok(NULL,":\n"); //port
  if(i == NULL) { return -4; }
  cmd->port = (unsigned short) atol(i);

  //cleanup
  return 0; 
}


short runCommand(cmd_t *cmd, char *output, long bufsize){

  char recvbuf[BUFFER];
  char sendbuf[BUFFER];
  sprintf(sendbuf,"I:%s",cmd->command);
  
  short c = socketConnect(cmd->host,cmd->port,&sendbuf[0],&recvbuf[0],BUFFER);
  if(c != 0) { return c; } //error

  printf("2%s2\n",&recvbuf[0]);

  return 0;
}


