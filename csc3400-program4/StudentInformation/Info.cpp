/**************************************************************
 *  CSC3400  ---- Program Set 4, Problem 1 --- Sumit Khanna
 *
 *  Info.cpp -- Implemention of classes needed to store
 *              student information
 **************************************************************/
#include "Info.hpp"
#include <stdio.h>
#include <string.h>
#include <cstdlib>

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
  //  delete first;
  //  delete last;
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

  char retval[NAME_LENGTH];
  
  snprintf(&retval[0],sizeof(retval),"%20.20s%c%20.20s",f_ptr,mi,l_ptr);

  return string(retval);
}

/**
 *Name() - Copy constructor
 *
 *         ensures that a object is copied correctly
 */
Name::Name(Name &n) {
  this->first = new string(*(n.first));
  this->last  = new string(*(n.last));
  this-> mi = n.mi;
}

/**
 *getLength() - returns length
 *
 *      returns length of Name record
 */
unsigned long Name::getLength() {
  return NAME_LENGTH;
}

/**
 *printRecord() - prints a formated record
 *
 *      returns a record formated for an indexed file
 */
string Name::printRecord() {
  const char *f_ptr = first->c_str(), *l_ptr = last->c_str();

  char retval[NAME_LENGTH+3];
  
  snprintf(&retval[0],sizeof(retval),"%20.20s %c %20.20s ",f_ptr,mi,l_ptr);

  return string(retval);
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

string Date::printRecord() {
  char temp[11];
  snprintf(&temp[0], sizeof(temp), "%2.2d/%2.2d/%4.4d",month,day,year);
  string retval("");
  retval.append(temp);
  return retval;
}

/***************************************
 *getDate() - returns a formated date
 *
 *RETURN:     8 char long string
 *            representation of date
 *Example:
 *        MMDDYYYY
 ***************************************/
string Date::getDate() {
  char temp[DATE_LENGTH];
  snprintf(&temp[0], sizeof(temp), "%2d%2d%4d",month,day,year);
  return string(temp);
}

/**
 *getLength()  - returns record length
 *
 *            length needed for storing records
 */
unsigned long Date::getLength() {
  return DATE_LENGTH;
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
  //delete name;
  //delete birthday;
}

/**
 *printRecord() - prints formatted record
 *
 *         record in human readable format
 */
string Person::printRecord() {

  return name->printRecord() + birthday->printRecord();

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

/**
 *Person() - constructs record from string
 *
 *PARAMS:    record that was originally output
 *           using createRecord()
 */
Person::Person(char *record) {
 

  char fname[22];
  fname[21] = '\0';
  char lname[22];
  lname[21] = '\0';
  char mi;
  char month[3];
  month[2] = '\0';
  char date[3];
  date[2] = '\0';
  char year[5];
  year[4] = '\0';

  memcpy(fname,record+sizeof(char),20);
  memcpy(lname,record+sizeof(char)*22,21);
  mi = record[21];
  memcpy(month,record+sizeof(char)*42,2);
  memcpy(date,record+sizeof(char)*44,2);
  memcpy(year,record+sizeof(char)*46,4);
  
  this->name = new Name(string(&fname[0]),string(&lname[0]),mi);
  this->birthday = new Date(atol(month),atol(date),atol(year));
  
}

/**
 *getLength() -- record length
 *
 *          length needed for indexed file storage
 */
unsigned long Person::getLength() {
  return name->getLength() + birthday->getLength();
}

//---end Person-------------------------

//----start Student (extends Person)----

/**********************************************
 *Studnet()  - creates a student class
 *
 *PARAMS:      person's name, birthday, social security number
 *             and grade point average
 */
Student::Student(Name name, Date birthday, unsigned long ssn, float gpa) :
  Person(name,birthday), ssn(ssn), gpa(gpa) {}

/**********************************************
 *~Student()  - deconstructor
 *
 *              doesn't do anything since we
 *              didn't "new" anything to begin
 *              with
 **********************************************/
Student::~Student() {}

/**********************************************
 *createRecord() - creates a record
 *
 *                 outputs a string representation
 *                 of the student record
 */
string Student::createRecord() {
  
  string super = Person::createRecord();
  
  char mine[STUDENT_LENGTH];

  snprintf(&mine[0], sizeof(mine), "%9d%4lf",ssn,gpa);

  return (super + mine);
  
}

/**
 *getLength()  -- returns length of record
 *
 *         length needed for indexed file storage
 */
unsigned long Student::getLength() {
  return Person::getLength() + STUDENT_LENGTH;
}

/**
 *Student()  - constructs Student from record
 *
 *PARAMS:      record generated by createRecord()
 */
Student::Student(char *record) : Person(record) {

  char cssn[11];
  cssn[10] = '\0';
  char cgpa[6];
  cgpa[5] =  '\0';

  memcpy(&cssn[0],record+sizeof(char)*50,9);
  memcpy(&cgpa[0],record+sizeof(char)*59,4);
  
  ssn = atol(cssn);
  gpa = atof(cgpa);
  
}

/**
 *printRecord() - prints human readable record
 *
 *        prints human readable version of Student class
 */
string Student::printRecord() {
  
  char cssn[10];
  char cgpa[5];
  snprintf(&cssn[0],sizeof(cssn),"%9.9d",ssn);
  snprintf(&cgpa[0],sizeof(cgpa),"%4.4lf",gpa);
  string retval("");
  retval += Person::printRecord();
  retval.append(" ");
  retval.append(cssn);
  retval += " ";
  retval.append(cgpa);
  return retval;
}

//---------------------end Student
