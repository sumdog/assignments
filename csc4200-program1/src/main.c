#include "client.h"
#include <unistd.h>
#include <string.h>
#include <malloc.h>

int main(int argc,char **argv) {

  //variables we need
  char *config = NULL, op;
  ns_t *nameserver;
  cmd_t *command;

  //command line arguments
  while( (op = getopt(argc,argv,"f:")) != -1) {
    switch(op) {
    case 'f':
      config = malloc(sizeof(char)*strlen(optarg));
      strcpy(config,optarg);
    }
  }
  
  //get config data (It will exit here on error)
  nameserver = getNameserver(config);

  //prompt on interactive mode
  if(isatty(fileno(stdin))) {
    printf("CSC 4200 Networking Program #1 Client\n");
    printf(" Sumit Khanna -- (Interactive Mode)\n");
  }

  //user input loop
  while(1) {

    //read a command
    if( (command = promptUser()) == NULL) {
      if(isatty(fileno(stdin))) {printf("\nGoodbye\n"); }
      exit(0); //user send EOF
    }

    //lookup service
    switch(serviceLookup(command,nameserver)) {
    case 0: //successful connect to name service
      break;
    case -1:
      printf("Error: Invalid Nameserver\n");
      break;
    case -2:
      printf("Error: Could Not Connect to Nameserver\n");
      break;
    case -3:
      printf("Error: I/O Failure with Nameservice\n");
      break;
    case -4:
      printf("Error: Invalid Response from Nameservice\n");
      break;
   }

 
    //done with this command
    freeCommand(command);
  }
  


  //clean up
  freeNameserver(nameserver);
  exit(0);
}
