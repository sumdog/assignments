/********************************
 *CStr - Class to handle strings
 *  see CStr.cxx for function
 *  discriptions
 ********************************/
#ifndef CSTR_H
#define CSTR_H
#include <string.h>
#include <iostream>

class CStr {

 private:
  char *str;

 public:
  CStr();
  CStr(const char* in);
  ~CStr();

  CStr  catString(CStr s);
  bool  equals(CStr s);
  unsigned long length();

  CStr operator+(CStr s);
  bool operator==(CStr s);
  bool operator!=(CStr s);

  friend std::ostream& operator<<(std::ostream& os, CStr& s);
  
};


#endif
