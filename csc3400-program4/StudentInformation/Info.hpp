#ifndef INFO_H
#define INFO_H
#include <string>
using std::string;

class Name {
public:
  Name(string first, string last, char mi);
  ~Name();
  Name(Name &n);
  string getName();
private:
  string *first;
  string *last;
  char mi;
};

class Date {
public:
  Date(unsigned short month, unsigned short day, unsigned short year);
  Date(Date &d);
  string getDate();
private:
  unsigned short month, day, year;

};

class Person {

public:
  Person(Name name, Date birthday);
  Person(string s);
  virtual ~Person();
  virtual string createRecord();

private:
  Name *name;  
  Date *birthday;
};


class Student : public Person {
  
public:
  Student(Name name, Date birthday, unsigned long ssn, float gpa);
  ~Student();
  string createRecord();

private:
  unsigned long ssn;
  float gpa;

};



#endif //INFO_H
