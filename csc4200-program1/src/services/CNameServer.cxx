#include "CNameServer.h"
#include <cctype>
#include <string>

CNameServer::CNameServer(char* ip, unsigned short port, long backlog) : CServer(ip,port,backlog) {

  servicemap = new servicemap_t();
 
  /* 
  service_t a, b;
 
  servicemap->insert( make_pair ( string("Bob"),a) );

  servicemap_t::iterator it = servicemap->find( "Bob" );

  if( it == servicemap->end() ) {
    //not found
  }
  else {
    b = it->second;
  }
  */
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
      
      //lookup entry
      servicemap_t::iterator it = servicemap->find(string(sname));
      if( it == servicemap->end() ) {
	strcpy(retval,"E:Unknown Serivce\n");
      }
      else {
	service_t *s = it->second;
	sprintf(retval,"A:%s:%d",s->host,s->port);
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
      servicemap->insert( make_pair ( string(sname),current) );
      
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
