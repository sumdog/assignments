#include "Info.hpp"
#include <stdio.h>

StudentName::StudentName(string *first, string *last, char mi) {
  this->first = new string(*first);
  this->last = new string(*last);
  this->mi - mi;
}

StudentName::~StudentName() {
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
string StudentName::getName() {
  
  const char *f_ptr = first->c_str(), *l_ptr = last->c_str();

  char retval[20];
  
  snprintf(&retval[0],sizeof(retval),"%20s%c%20s",f_ptr,mi,l_ptr);

  return string(retval);
}