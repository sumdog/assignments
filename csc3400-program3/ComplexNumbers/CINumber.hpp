/***********************************************************
 *File: CINumbers.hpp
 *
 *  Sumit Khanna - CSC3400 - Rama
 *
 *Contains: Definition of CINumber class for
 *          handeling complex numbers
 *
 *See:      CINumbers.cxx for function discriptions
 ***********************************************************/
#ifndef CINUMBER
#define CINUMBER

class CINumber {


 public:
  CINumber(long real, long i);
  CINumber operator+(CINumber num);
  CINumber operator-(CINumber num);
  CINumber operator*(CINumber num);
  bool     operator==(CINumber num);
  bool     operator!=(CINumber num);
  void     printNumber();

 private:
  long real_part;
  long i_part;

};

#endif
