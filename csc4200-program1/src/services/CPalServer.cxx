#include "CPalServer.h"
#include <string>
#include <stdio.h>


bool CPalServer::testPalindrome(char *c) {

  if( strlen(c) <= 1) { //base case
    return true;
  }
  else if( *c == c[strlen(c)-1]) {
    c[strlen(c)-1] = '\0';
    c++;
    //start recursive calls
    return testPalindrome(c);
  }
  else { //did not reach base case
    return false;
  }

}
  

CPalServer::CPalServer(unsigned short port, long backlog) : CServer(port,backlog) {

  strcpy(name , "palindrome" );	
  
}

void CPalServer::processRequest(command_t *t, char* retval) {

  //temporary vars
  char **v = t->argv, *word;
  char temp[BUFFER_SIZE];


  //check for the right command format
  if(t->type == CMD_IVK   &&   t->argc == 2   &&   strcmp("test",*v) == 0  ) {
 
    //get to the arg in v
    word = *(++v);

    //strip of new line
    word[strlen(word)-1] = '\0';


    //the testPalindrome function will cut this up, so let's copy it first
    strcpy(&temp[0],word);

    if(testPalindrome(&temp[0])) {
      sprintf(retval,"A:%s is a Palindrome\n",word);
    }
    else {
      sprintf(retval,"A:%s is not a Palindrome\n",word);
    }

  }  
  else {
    strcpy(retval,"E:Invalid Command. Correct Format Is \"I:test <word>\"\n");
  }
  
}
