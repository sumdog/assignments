#include "client.h"
#include <unistd.h>
#include <string.h>
#include <malloc.h>

int main(int argc,char **argv) {

  char *config = NULL, op;

  while( (op = getopt(argc,argv,"f:")) != -1) {
    switch(op) {
    case 'f':
      config = malloc(sizeof(char)*strlen(optarg));
      strcpy(config,optarg);
    }
  }
  
  getNameserver(config);

}
