#include "CAddressServer.hpp"
#include <string>
#include <ctype.h>

CAddressServer::CAddressServer(unsigned short port, long backlog) : CServer(port,backlog) {
  //initalize service
  strcpy(name,"address");
  book = new addressbook_t();
  
  //setup pthread locking
  pthread_mutex_init(&lock,NULL);
}

CAddressServer::~CAddressServer() {
  //clean up Mess
  delete book;
  pthread_mutex_destroy(&lock);
}

bool CAddressServer::isNumeric(char *s) {
  char i;
  int j;
  for(i = *s, j = strlen(s); j > 0; i = *(++s), j--) {
    if(!isdigit(i)) { return false; }
  }
  return true;
}

bool CAddressServer::isAlphaNumeric(char *s) {
  char i;
  int j;
  for(i = *s, j = strlen(s); j > 0; i = *(++s), j--) {
    if(!isalnum(i) && !isspace(i)) { return false; }
  }
  return true;
}

bool CAddressServer::isAlpha(char *s,bool spaces=false) {
  char i;
  int j;
  for(i = *s, j = strlen(s); j > 0; i = *(++s), j--) {
    if(spaces) {
      if(!isalpha(i) && !isspace(i)) { return false;}
    }
    else {
      if( !isalpha(i) )  { return false; }
    }
  }
  return true;
}

bool CAddressServer::processRequest(command_t *t, char* retval) {

  bool errflg = false;
  string errstr("E:");

  switch(t->type) {
  case GET_SOC_SEC_NO: {
    addressbook_t::const_iterator it;
    bool found = false;
    string li("A:");
    for(it = book->begin(); it != book->end(); it++) {
      if(strcmp( it->second->lname->c_str() , t->argv[0] ) == 0) {

	
	char *tempchar = new char[100];
	sprintf(tempchar,"%d",it->first);
	
	li += tempchar;
	li += ":";
	delete tempchar;
	found = true;
      }
    }
    if(!found) {
      strcpy(retval,"E:No Entries Found By That Name");
      return true;
    }
    else {
      li += "\n";
      strcpy(retval,li.c_str());
      return true;
    }
    break;
  }
  case GET_STREET: {
    entry_t *temp = (*book)[atol(t->argv[0])];
    if(temp == NULL) {
      strcpy(retval,"E:Entry Not Found\n");
      return true;
    }
    string s("A:");
    s += *(temp->street);
    s += "\n";
    strcpy(retval,s.c_str());
    return true;
    break;
  }
  case GET_HOUSE_NUM:{
    entry_t *temp = (*book)[atol(t->argv[0])];
    if(temp == NULL) {
      strcpy(retval,"E:Entry Not Found\n");
      return true;
    }
    string s("A:");
    s += (temp->housenum);
    s += "\n";
    strcpy(retval,s.c_str());
    return true;
    break;
  }
  case GET_ZIP:{
    entry_t *temp = (*book)[atol(t->argv[0])];
    if(temp == NULL) {
      strcpy(retval,"E:Entry Not Found\n");
      return true;
    }
    string s("A:");
    s += (temp->zip);
    s += "\n";
    strcpy(retval,s.c_str());
    return true;
    break;
  }
  case GET_CITY:{
    entry_t *temp = (*book)[atol(t->argv[0])];
    if(temp == NULL) {
      strcpy(retval,"E:Entry Not Found\n");
      return true;
    }
    string s("A:");
    s += *(temp->city);
    s += "\n";
    strcpy(retval,s.c_str());
    return true;
    break;
  }
  case GET_STATE:{
    entry_t *temp = (*book)[atol(t->argv[0])];
    if(temp == NULL) {
      strcpy(retval,"E:Entry Not Found\n");
      return true;
    }
    string s("A:");
    s += *(temp->state);
    s += "\n";
    strcpy(retval,s.c_str());
    return true;
    break;
  }
  case GET_NAME: {
    entry_t *temp = (*book)[atol(t->argv[0])];
    if(temp == NULL) {
      strcpy(retval,"E:Entry Not Found\n");
      return true;
    }
    string s("A:");
    s += *(temp->fname);
    s += " ";
    s += *(temp->lname);
    s += "\n";
    strcpy(retval,s.c_str());
    return true;
    break;
  }
  case ADD_PERSON:
    
    if(t->argc != 8) {
      strcpy(retval,"E:Malformed Entry\n");
      return true;
    }
    
    if(!isAlpha(t->argv[0])) {
      errstr += "Invalid Last Name:";
      errflg = true;
    }
    
    if(!isAlpha(t->argv[1])) {
      errstr += "Invalid First Name:";
      errflg = true;
    }

    if(!isNumeric(t->argv[2]) || strlen(t->argv[2])!=9 ) {
      errstr += "Invalid Social Security Number:";
      errflg = true;
    }

    if(!isAlphaNumeric(t->argv[3])) {
      errstr += "Invalid Street Name:";
      errflg = true;
    }

    if(!isNumeric(t->argv[4])) {
      errstr += "Invalid House Number:";
      errflg = true;
    }

    if(!isAlpha(t->argv[5])) {
      errstr += "Invalid City:";
      errflg = true;
    }
    
    if(!isAlpha(t->argv[6]) || strlen(t->argv[6]) != 2) {
      errstr += "Invalid State Abbreviation:";
      errflg = true;
    }

    if(!isNumeric(t->argv[7]) || strlen(t->argv[7]) != 5 )  {
      errstr += "Invalid Zip Code:";
      errflg = true;
    }

    if(errflg) {
      errstr += "\n";
      strcpy(retval,errstr.c_str());
      return true;
    }
    else {
      entry_t *e = new entry_t;
      e->lname      = new string(t->argv[0]);
      e->fname      = new string(t->argv[1]);
      e->street     = new string(t->argv[3]);
      e->housenum   = atol(t->argv[4]);
      e->city       = new string(t->argv[5]);
      e->state      = new string(t->argv[6]);
      e->zip        = atol(t->argv[7]);
      pthread_mutex_lock(&lock);
      (*book)[atol(t->argv[2])] = e;
      pthread_mutex_unlock(&lock);
      strcpy(retval,"A:Entry Successfully Added\n");
      return true;
    }

    break;
  case QUIT:
    return false;
    break;
  default:
    strcpy(retval,"E:Invalid Request\n");
    return true;
    break;
  }
  
}
