#include "CStr.hpp"
#include <iostream>
#include <string.h>

/****************************************
 *CStr()  -  Constructs an empty string
 ****************************************/
CStr::CStr() {
  str = new char[strlen("")+1];
  strcpy(str,"");
}


/****************************************
 *CStr()  -  Constructs a string
 *
 *PARAM:     char* to make string from
 ****************************************/
CStr::CStr(const char* in) {
  str = new char[strlen(in)+1];
  strcpy(str,in);
}

/****************************************
 *~CStr() - Frees Memory Allocated for
 *          string
 ****************************************/
CStr::~CStr() {
  //delete[] str ;
}

/****************************************
 *catString() - joins two string together
 *
 *PARAM:        string to join to myself
 *RETURNS:      joined string
 ****************************************/
CStr CStr::catString(CStr s) {
  return *this + s;
}

/****************************************
 *equals()      - checks for equality
 *
 *PARAM:        stright to compare to
 *RETURNS:      boolean indicating equality
 ****************************************/
bool CStr::equals(CStr s) {
  return *this == s;
}

/****************************************
 *operator+     - joins two strings
 *
 *PARAM:        string to join to myself
 *RETURNS:      joined string
 ****************************************/
CStr CStr::operator+(CStr s) {
  char i[strlen(s.str) + strlen(str) + 2];
  strcpy(&i[0],str);
  strcat(&i[0],s.str);
  return CStr(&i[0]);
}

/****************************************
 *operator==    - checks for equality
 *
 *PARAM:        stright to compare to
 *RETURNS:      boolean indicating equality
 ****************************************/
bool CStr::operator==(CStr s) {
  return strcmp(str,s.str);
}

/****************************************
 *operator==    - checks for inequality
 *
 *PARAM:        stright to compare to
 *RETURNS:      boolean indicating equality
 ****************************************/
bool CStr::operator!=(CStr s) {
  return !(*this == s);
}

/****************************************
 *length()      -indicates length of string
 *
 *PARAM:        none
 *RETURNS:      length of the string
 ****************************************/
unsigned long CStr::length() {
  return strlen(str);
}

std::ostream& operator<<(std::ostream& os, CStr& s) {
  os << s.str;
  return os;
}
