#include "Info.hpp"
#include <stdio.h>

//---------------Begin Name Implementation----------------

/**************************************************
 *Name() - constructor
 *
 *PARAMS:     first and last name as string objects
 *            and a middle initial
 **************************************************/

Name::Name(string *first, string *last, char mi) {
  this->first = new string(*first);
  this->last = new string(*last);
  this->mi - mi;
}

/************************************************
 *~Name() - deconstructor
 *
 *          Frees memeory allocated for
 *          first and last name
 ************************************************/
Name::~Name() {
  delete first;
  delete last;
}


/************************************************
 *getName() - returns a formated name
 * 
 *PARAMS:     none
 *RETURN:     a string containing the first name,
 *            last name and middle initial
 *            formated to 18 chars per name
 *            and 2 chars for the MI for a total
 *            record length of 20 chars. Example:
 *
 *    FirstNamexxxxxxxxxxxMxLastNamexxxxxxxxxxxx
 *
 *    (x == spaces)
 ************************************************/
string Name::getName() {
  
  const char *f_ptr = first->c_str(), *l_ptr = last->c_str();

  char retval[20];
  
  snprintf(&retval[0],sizeof(retval),"%20s%c%20s",f_ptr,mi,l_ptr);

  return string(retval);
}

//--------end Name class-------------------------------
