#include "CINumber.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define ELEMENTS 4

int main() {

  //variables we need
  CINumber **numbers = new (CINumber*)[ELEMENTS];
  CINumber *n;
  short x;

  //read user input
  for(x=0,n=*numbers ; x < ELEMENTS; x++, n++) {
    long r,i;
    cout << "Enter the First complex Number:\t";
    cout << "Real part followed by the imaginary part:\t";
    cin  >> r >> i;
    n = new CINumber(r,i);
  }

  //display original numbers
  for(n=*numbers,x=0; x < ELEMENTS; x++, n++) {
    cout << n;
  }

  //clean up our mess
  for(n=*numbers,x=0; x < ELEMENTS; x++, n++) {
    delete n;
  }
  delete numbers;

}
