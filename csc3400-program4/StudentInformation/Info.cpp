#include "Info.hpp"
#include <stdio.h>

//---------------Begin Name Implementation----------------

/**************************************************
 *Name() - constructor
 *
 *PARAMS:     first and last name as string objects
 *            and a middle initial
 **************************************************/

Name::Name(string first, string last, char mi) {
  this->first = new string(first);
  this->last = new string(last);
  this->mi = mi;
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

  char retval[42];
  
  snprintf(&retval[0],sizeof(retval),"%20.20s%c%20.20s",f_ptr,mi,l_ptr);

  return string(retval);
}

Name::Name(Name &n) {
  this->first = new string(*(n.first));
  this->last  = new string(*(n.last));
  this-> mi = n.mi;
}

//--------end Name class-------------------------------


//------data implementation

/************************************
 *Date()  - constructor
 *
 *Param:     month, date and year
 ************************************/
Date::Date(unsigned short month, unsigned short day, unsigned short year) :
  month(month), day(day), year(year) {}


Date::Date(Date &d) : month(d.month), day(d.day), year(d.year) {}



/***************************************
 *getDate() - returns a formated date
 *
 *RETURN:     8 char long string
 *            representation of date
 *Example:
 *        MMDDYYYY
 ***************************************/
string Date::getDate() {
  char temp[9];
  snprintf(&temp[0], sizeof(temp), "%2d%2d%4d",month,day,year);
  return string(temp);
}

//-------end date


//---Being Person

/****************************************
 *Person() - constructor
 *
 *PARMAS:    name and birthday 
 */
Person::Person(Name name, Date birthday) {
  this->name = new Name(name);
  this->birthday = new Date(birthday);
}

/***************************************
 *~Person() - destructor (virtual)
 *
 *            frees memeory allocated to
 *            a person object
 */
Person::~Person() {
  delete name;
  delete birthday;
}

/**************************************************
 *createRecord() - ouputs a string record (virtual)
 *
 *RETURNS:   a formated record of length 28:
 *           NamexxxxxxBirthdayxxxxxx
 *************************************************/
string Person::createRecord() {
  return (name->getName() + birthday->getDate());
}


Person::Person(string s) {
  const char *data = s.c_str();
  
}

//---end Person-------------------------

//----start Student (extends Person)----

Student::Student(Name name, Date birthday, unsigned long ssn, float gpa) :
  Person(name,birthday), ssn(ssn), gpa(gpa) {}

Student::~Student() {}

string Student::createRecord() {
  
  string super = Person::createRecord();
  
  char mine[14];

  snprintf(&mine[0], sizeof(mine), "%9d%4lf",ssn,gpa);

  return (super + mine);
  
}

//--end Student
