#include "CNameServer.h"
#include <cctype>
#include <string>
#include <stdio.h>

CNameServer::CNameServer(unsigned short port, long backlog) : CServer(port,backlog) {

  servicemap = new servicemap_t();
  strcpy(name,"name");
}

void CNameServer::processRequest(command_t *t, char* retval) {
  //iteratorion vars
  char **v = t->argv;

  //bufferes for I/O
  char sname[BUFFER_SIZE];
  char shost[BUFFER_SIZE];
  unsigned short sport;

  //what type of respons (Lookup or Request)
  switch(t->type) {
  case CMD_LOK: //Lookup

    if(t->argc == 1) {
      //parse single argument
      strcpy(sname,*(t->argv));
      //trim the f#$%@ing new line off the string
      sname[strlen(sname)-1] = '\0';

      //lookup entry
      service_t *t = (*servicemap)[sname];

      if( t == NULL ) {
	strcpy(retval,"E:Unknown Serivce\n");
      }
      else {
	sprintf(retval,"A:%s:%d\n",t->host,t->port);

      }
    }
    else {
      strcpy(retval,"E:Invalid Number of Arguments\n");      
    }

    break;
  case CMD_REQ: //Request to be listed

    if( t->argc == 3) {
      //parse arguments
      strcpy(sname,*v++);
      strcpy(shost,*v++);
      sport = (unsigned short) atol( *v );

      //make struct for storage in map
      service_t *current = new service_t;
      current->host = new char[strlen(shost)];
      strcpy(current->host,shost);
      current->port = sport;

      //store it in the map (tree data structure)
      (*servicemap)[sname] = current;

      //return value
      strcpy(retval,"A:SUCCESS\n");
    }
    else {
      strcpy(retval,"E:Invalid Number of Arguments\n");
    }

    break;
    default:
      strcpy(retval,"E:Invalid Request Type\n");
      break;
  }
  
}
