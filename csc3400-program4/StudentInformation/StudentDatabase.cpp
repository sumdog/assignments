/**************************************************************
 *  CSC3400  ---- Program Set 4, Problem 1 --- Sumit Khanna
 *
 *  StudentDatabase.cpp -- implementation of class used to
 *                         manage database
 *
 **************************************************************/
#include "StudentDatabase.hpp"

//needed for open(), close(), ftruncate()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define RECORD_LENGTH 65

/**
 *SDatabase() - constructs Database handler
 *
 *PARAMS:     - string containing name of datafile
 */
SDatabase::SDatabase(string filename) {

  fd = open(filename.c_str(), O_RDWR | O_CREAT );
  file = fdopen(fd,"w+");
}

/**
 *~SDatabase() - deconstructs database
 *
 *    closes/flushes files
 */
SDatabase::~SDatabase() {
  fclose(file);
  close(fd);
}


/**
 *writeRecord() - writes Record to datafile
 *
 *PARAMS:       index - location to write record
 *                  s - student object to write
 */
void SDatabase::writeRecord(unsigned long index,Student s) {
  
  //offset is the length of the record plus our status byte
  unsigned  long offset = index * (s.getLength() + 1);

  //go to location in file
  fseek(file,offset, SEEK_SET);

  //setup our record
  string record = "2" + s.createRecord();

  //write record
  fputs(record.c_str(),file);

  //flush stream
  fflush(file);
}

/**
 *listRecord() - list record from database
 *
 *PARAMS:      index - location to retieve record from
 *RETURNS:     Student object from database
 *THROWS:      'A' if index is greater than file length
 *             'B' if record doesn't exist or was deleted
 */
Student SDatabase::listRecord(unsigned long index) {

  unsigned long offset = index * (RECORD_LENGTH +1);
  
  char buffer[RECORD_LENGTH +1];

  struct stat stat_buf;

  fstat(fd, &stat_buf);

  if(stat_buf.st_size < offset) {
    throw 'A';
  }

  fseek(file,offset,SEEK_SET);
  
  fgets(&buffer[0], sizeof(buffer), file);

  //deleted record
   if(buffer[0] != '2') {
    throw 'B';
  }

  return Student(&buffer[0]);

}

/**
 *deleteRecord -- deletes a record
 *
 *PARAMS:      index - location of record to delete
 *RETURNS:     true on successful delete
 *             false if record doesn't exist
 *HOW:         sets the fist byte of the record 
 *             from 2 (indicates valid record)
 *             to 0 (indicates invalid record)
 */
bool SDatabase::deleteRecord(unsigned long index) {

  unsigned long offset = index * (RECORD_LENGTH +1);
  
  char buffer[RECORD_LENGTH +1];

  struct stat stat_buf;

  fstat(fd, &stat_buf);

  if(stat_buf.st_size < offset) {
    return false;
  }

  fseek(file,offset,SEEK_SET);
  
  fgets(&buffer[0], sizeof(buffer), file);

  if(buffer[0] == '2') {
    fseek(file,offset,SEEK_SET);
    fputs("0",file);
    fflush(file);
    return true;
  }
  else {
    return false;
  }
  
  return false;

}
