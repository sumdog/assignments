/***************************
 *driver to test CStr class
 ***************************/


#include "CStr.hpp"
#include <iostream>
using std::cout;
using std::endl;

int main() {

  //our test CStr clases
  CStr str1("Hello"), str2("World"), str3("GoodBye"), str4("World");

  //operations we perform on them
  CStr str5 = str1 + str2;
  CStr *equals = (str1==str4) ? new CStr("The two strings are not equal") : new CStr("The two strings are equal");
  CStr *noequals = (str2 != str4) ? new CStr("The two strings are equal") : new CStr("The two strings are not equal");

  //output
  cout << "String 1:            " << str1 << endl;
  cout << "String 2:            " << str2 << endl;
  cout << "String 3:            " << str3 << endl;
  cout << "String 4:            " << str4 << endl;
  cout << "String1 and String2: " << str5 << endl;
  cout << "String1  == String4: " << *equals << endl;
  cout << "String2  != String4: " << *noequals << endl;

  //clean up mess
  delete equals;
  delete noequals;
 
}
