#include "CStr.hpp"
#include <iostream>
#include <string.h>

CStr::CStr() {
  str = new char[strlen("")+1];
  strcpy(str,"");
}


CStr::CStr(const char* in) {
  str = new char[strlen(in)+1];
  strcpy(str,in);
}

CStr::~CStr() {
  //delete[] str ;
}

CStr CStr::catString(CStr s) {
  return *this + s;
}

bool CStr::equals(CStr s) {
  return *this == s;
}


CStr CStr::operator+(CStr s) {
  char i[strlen(s.str) + strlen(str) + 2];
  strcpy(&i[0],str);
  strcat(&i[0],s.str);
  return CStr(&i[0]);
}

bool CStr::operator==(CStr s) {
  return strcmp(str,s.str);
}

bool CStr::operator!=(CStr s) {
  return !(*this == s);
}


unsigned long CStr::length() {
  return strlen(str);
}

std::ostream& operator<<(std::ostream& os, CStr& s) {
  os << s.str;
  return os;
}
