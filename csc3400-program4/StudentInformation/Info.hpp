/**************************************************************
 *  CSC3400  ---- Program Set 4, Problem 1 --- Sumit Khanna
 *
 *  Info.hpp -- header file containing definitions for classes
 *              needed in database
 *
 *  see Info.cpp for Implementation
 **************************************************************/
#ifndef INFO_H
#define INFO_H
#include <string>
using std::string;

#define NAME_LENGTH 42

class Name {
public:
  Name(string first, string last, char mi);
  ~Name();
  Name(Name &n);
  string getName();
  unsigned long getLength();
  string printRecord();
private:
  string *first;
  string *last;
  char mi;
};

#define DATE_LENGTH 9

class Date {
public:
  Date(unsigned short month, unsigned short day, unsigned short year);
  Date(Date &d);
  string getDate();
  unsigned long getLength();
  string printRecord();
private:
  unsigned short month, day, year;

};

class Person {

public:
  Person(Name name, Date birthday);
  Person(char *record);
  virtual ~Person();
  virtual string createRecord();
  virtual unsigned long getLength();
  virtual string printRecord();

private:
  Name *name;  
  Date *birthday;
};

#define STUDENT_LENGTH 14

class Student : public Person {
  
public:
  Student(Name name, Date birthday, unsigned long ssn, float gpa);
  Student(char *record);
  ~Student();
  string createRecord();
  string printRecord();
  unsigned long getLength();

private:
  unsigned long ssn;
  float gpa;

};



#endif //INFO_H
