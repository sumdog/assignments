#ifndef INFO_H
#define INFO_H
#include <string>
using std::string;

class Name {
public:
  Name(string *first, string *last, char mi);
  ~Name();
  string getName();
private:
  string *first;
  string *last;
  char mi;
};

class Date {
public:
  Date(unsigned short month, unsigned short day, unsigned short year);
private:
  unsigned short month, day, year;

};

class Person {

public:
  Person(Name name, Date birthday);
  ~Person();
  Name getName();
  void setName(Name*);
  Date getBirthday();
  void setBirthday(Date*);
  virtual string createRecord();

private:
  Name *name;  
  Date *birthday;
};


class Student : public Person {
  
public:
  Student(Name name, Date birthday, 

};



#endif //INFO_H
