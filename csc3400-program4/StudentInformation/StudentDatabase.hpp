/**************************************************************
 *  CSC3400  ---- Program Set 4, Problem 1 --- Sumit Khanna
 *
 *  StudentDatabase.hpp -- definitions for class used to
 *                         manage reading and writing to 
 *                         indexed file
 *
 * see StudentDatabase.cpp for implementation
 *
 **************************************************************/
#ifndef SDATABASE_H
#define SDATABASE_H

#include <stdio.h>
#include <string>
using std::string;
#include "Info.hpp"

class SDatabase {

public:
  SDatabase(string filename);
  ~SDatabase();
  void writeRecord(unsigned long index, Student s);
  Student listRecord(unsigned long index);
  bool deleteRecord(unsigned long index);

private:
  FILE *file;
  long fd;

};




#endif // SDATABASE_H
