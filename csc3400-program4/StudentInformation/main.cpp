/**************************************************************
 *  CSC3400  ---- Program Set 4, Problem 1 --- Sumit Khanna
 *
 *  main.cpp -- driver
 *
 **************************************************************/
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::string;

#include "StudentDatabase.hpp"
#include "Info.hpp"

//List header for listing entry
void listHeader() {

  cout << "----------First Name-M------------Last Name---Birthday-------SSN--GPA" << endl;

}

//Lists all records
void listRecords(SDatabase *db) {

  for(int x=0; x>=0; x++) {
    try {
      Student s = db->listRecord(x);
      if(&s != NULL) {
	cout << s.printRecord() << endl;
      }
    }
    catch(char a) {
      if(a == 'A') {
	break;
      }
    }
  }

}

//deletes a record
void deleteRecord(SDatabase *db) {

  unsigned long index;
  cout << "Index of Record to delete: ";
  cin >> index;
  if( db->deleteRecord(index) ) {
    cout << "Record Deleted" << endl;
  }
  else {
    cout << "Invalid Record ID" << endl;
  }
}

//read a single record
void readRecord(SDatabase *db) {

  unsigned long index;
  cout << "Index of Record to read: ";
  cin >> index;
  try {
    Student s = (db->listRecord(index));
    listHeader();
    cout << s.printRecord() << endl;
  }
  catch(...) {
    cout << "Invalid Record ID" << endl;
  }
}

//add a record
void addRecord(SDatabase *db) {
  
  unsigned long record, ssn;
  string fname, lname;
  char mi;
  float gpa;
  unsigned short bmonth, bday, byear;
  
  cout << "Record Number:";
  cin >> record;
  cout << "First Name:";
  cin >> fname;
  cout<< "Last Name:";
  cin >> lname;
  cout << "Middle Initial:";
  cin >> mi;
  cout << "Birthday (Month, 1-12):";
  cin >> bmonth;
  cout << "Birthday (Day, 1-31):";
  cin >> bday;
  cout << "Birthday (Year, 0000-9999):";
  cin >> byear;
  cout << "Social Security Number:";
  cin >> ssn;
  cout << "Grade Point Average:";
  cin >> gpa;
  
  Name temp_name(fname,lname,mi);
  Date temp_date(bmonth,bday,byear);
  Student fuck(temp_name,temp_date,ssn,gpa);
  
  db->writeRecord(record,fuck);
  
}

//help menu
void helpMenu() {
  cout << "Help Menu" << endl;
  cout << "--------------------" << endl;
  cout << "? - Help Menu" << endl;
  cout << "a - Add/Change Record" << endl;
  cout << "d - Delete Record" << endl;
  cout << "l - List record" << endl;
  cout << "r - List all records" << endl;
  cout << "q - Quit" << endl;
}

//main entry point
int main() {

  string filename;
  
  cout << "Name of Database File:" << endl;
  
  cin >> filename;
  
  SDatabase *dbase = new SDatabase(filename);
  
  while(true) {
    
    char input;
    
    cout << "(? for help)>>>";
    cin >> input;
    
      switch(input) {
      case 'a': 
	addRecord(dbase);
	break;
      case 'l':
	readRecord(dbase);
	break;
      case 'r':
	listHeader();
	listRecords(dbase);
	break;
      case '?': 
	helpMenu();
	break;
      case 'q':
	exit(0);
	break;
      case 'd':
	deleteRecord(dbase);
	break;
      default:
	cout << "Invalid Command" << endl;
	break;
      }//end switch()
      
  }
  
  
  //clean up memory
  delete dbase;
  
}//end main()
