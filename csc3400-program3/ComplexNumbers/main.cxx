/***********************************************************
 *File: main.cxx
 *
 *  Sumit Khanna - CSC3400 - Rama
 *
 *Contains: Driver for testing Complex Number Class
 *
 *See:      CINumbers.cxx for Complex Number Class functions
 *          CINumbers.hpp for Complex Number Class definition
 ***********************************************************/
#include "CINumber.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define ELEMENTS 4

int main() {

  //variables we need
  CINumber **numbers = new (CINumber*)[ELEMENTS];
  CINumber **n;
  short x;

  //read user input
  for(x=0,n=numbers ; x < ELEMENTS; x++, n++) {
    long r,i;
    cout << "Enter the First complex Number:\t";
    cout << "Real part followed by the imaginary part:\t";
    cin  >> r >> i;
    *n = new CINumber(r,i);
  }

  //display original numbers
  for(n=numbers,x=0; x < ELEMENTS; x++, n++) {
    cout << "Complex (c" << x+1 << "): \t\t";
    (*n)->printNumber();
  }

  //add two of them together
  cout << "Sum(c1 + c2):\t\t";
  (*(numbers[0]) + *(numbers[1])).printNumber();

  //subtract two of them
  cout << "Difference(c1 - c2):\t\t";
  (*(numbers[0]) - *(numbers[1])).printNumber();

  //multiply
  cout << "Product(c1 * c2):\t\t";
  (*(numbers[0]) * *(numbers[1])).printNumber();

  //test for equality
  cout << "Test for Equality(c1 == c3)\t\t";
  cout << ((*(numbers[0]) == *(numbers[1])) ? "The numbers are equal" : "The numbers are not equal");
  cout << endl;

  //test for inequality
  cout << "Test for Inequality(c2 != c4)\t\t";
  cout << ((*(numbers[0]) != *(numbers[1])) ? "The numbers are not equal" : "The numbers are equal");
  cout << endl;

  //clean up our mess
  for(n=numbers,x=0; x < ELEMENTS; x++, n++) {
    delete *n;
  }

  delete[] numbers;

}
