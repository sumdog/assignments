#ifndef INFO_H
#define INFO_H
#include <string>
using std::string;

class StudentName {
public:
  StudentName(string *first, string *last, char mi);
  ~StudentName();
  string getName();
private:
  string *first;
  string *last;
  char mi;
};

class Birthday {
public:
  Birthday(unsigned short month, unsigned short day, unsigned short year);
private:
  unsigned short month, day, year;

};

class Info {

public:
  StudentName *name;
private:
  
};


#endif //INFO_H
