/**
 *\file prob6.c
 *This file contains the functions used
 *for problem 6, calculation of the fibonacci sequence
 */
#include "prob6.h"

/**
 *\fn long p6fib(double num)
 *This function calculates element n in the 
 *fibonacci sequence using a long 32-bit signed
 *integer to store its data.
 */
long p6fib(double num) {

  long total, prev, swap; 
  double cur;

  for(cur=0,total=0 ; cur < num; cur++ ) {
    if( cur == 0 ) {
      total = 1; 
      prev  = 0;
    }
    else {
      swap = total;
      total = total + prev;
      prev = swap;
    }
      
  }

  return total;
}

/**
 *\fn double p6doublefib(double num)
 *This function calculates element n in the
 *fibonacci sequence using a double to store
 *its data.
 */
double p6doublefib(double num) {

  double total, cur, prev, swap; 

  for(cur=0,total=0 ; cur < num; cur++ ) {
    if( cur == 0 ) {
      total = 1; 
      prev  = 0;
    }
    else {
      swap = total;
      total = total + prev;
      prev = swap;
    }
  }
  return total;
}
