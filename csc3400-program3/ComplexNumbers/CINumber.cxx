/***********************************************************
 *File: CINumbers.cxx
 *
 *  Sumit Khanna - CSC3400 - Rama
 *
 *Contains: Implementation of CINumber class
 *
 *See:      CINumbers.hpp - for class definition
 ***********************************************************/
#include "CINumber.hpp"
#include <iostream>
using std::cout;
using std::endl;

/** CINumber Constructor
 *  PARAM: real - real part of complex number
 *  PARAM: i    - imaginary part of complex number
 */
CINumber::CINumber(long real, long i) {
  real_part = real;
  i_part = i;
}

/** (+)operator - will add CINumbers together
 *  PARAM:     CINumber num - number to add to myself
 *  RETURNS:   CINumber result of addition
 *
 *  ALGORITHM: Adds real and imaginary parts
 */
CINumber CINumber::operator+(CINumber num) {

  long r = real_part + num.real_part;
  long i = i_part + num.i_part;

  return CINumber(r,i);

}


/** (-)operator - will subtract CINumbers from each other
 *  PARAM:     CINumber num - number to subtract from myself
 *  RETURNS:   CINumber result of subtraction
 *
 *  ALGORITHM: Subtracts real and imaginary parts
 */
CINumber CINumber::operator-(CINumber num) {

  long r = real_part - num.real_part;
  long i = i_part - num.i_part;

  return CINumber(r,i);

}

/** (*)operator - will multiply two CINumbers together
 *  PARAM:     CINumber num - number to multiply by
 *  RETURNS:   CINumber which is the result of multiplication
 *
 *  ALGORITHM: The two complex numbers are multipled using
 *             a simplification of the FOIL method 
 *             (FOIL = First, Inner, Outer, Last). 
 */
CINumber CINumber::operator*(CINumber num) {

  long r = (this->real_part * num.real_part) - (this->i_part * num.i_part);
  long i = (this->i_part * num.real_part) + (this->real_part * num.i_part);

  return CINumber(r,i);

}

/** (==)operator - will test to see if two CINumbers are equal
 *  PARAM:     CINumber num - number to test for equality
 *  RETURNS:   bool indicating if CINumbers are equal
 *
 *  ALGORITHM: Compares the real and imaginary fields
 *             of the two classes
 */
bool CINumber::operator==(CINumber num) {
  
  if(this->real_part == num.real_part && this->i_part == num.i_part) {
    return true;
  }

  return false;

}

/** (!=)operator - will test to see if two CINumbers are not equal
 *  PARAM:     CINumber num - number to test for inequality
 *  RETURNS:   bool indicating if CINumbers are not equal
 *
 *  ALGORITHM: Returns the negation of ==operator
 */
bool CINumber::operator!=(CINumber num) {
  return !( *this == num );
}

/** printNumber() - will print the number to standard out
 *  PARAM:     none
 *  RETURNS:   none
 *  ALGORITHM: outputs real and i parts in the format a + bi to
 *             standard out using the cout objects and newline
 */
void CINumber::printNumber() {
  cout << this->real_part << " + " << this->i_part << "i"  << endl;
}
