#include "CINumber.h"


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


bool CINumber::operator==(CINumber num) {
  
  if(this->real_part == num.real_part && this->i_part == num.i_part) {
    return true;
  }

  return false;

}

bool CINumber::operator!=(CINumber num) {
  return !( *this == num );
}
