/**\file problems.c
 *This file has all the master functions needed
 *to perform each problem.
 */
#include "problems.h"
#include "prob1.h"
#include "prob2.h"
#include "prob3.h"
#include "prob5.h"
#include "prob6.h"
#include <string.h>
#include <stdlib.h>
/**\def MAX_ONE
 *maximum input value for problem one
 */
#define MAX_ONE 100 

/** \fn void runPRobOne()
 *This function will ask the user for input for integer sets a and b
 *until MAX_ONE is reached and then calculate the union, intersection
 *and difference of the two sets and print the output.
 */
void runProblemOne() {

  p1DataSet *data = p1createSet(MAX_ONE);
  p1populateSet(data);
  p1CalSet *cal = p1performCalculations(data);
  p1printResults(data,cal);
  p1deleteSet(data);

}

/**\fn void runProblemSix( double n , short type)
 *This function can calculate a number in the fibonacci
 *sequence given an index and a data storage type
 */
void runProblemSix( double n , short type) {

  //counter
  double x;
  
  //runs sequences (1 = integer, 2=double)
  if(type == 1) {
    printf("fibonacci (32-bit integer)\n");
    for(x=0 ; x < n; x++) {
      printf("%d\n", p6fib(x));
    }
  }
  else if (type == 2) {
    printf("fibonacci (double)\n");
    for(x=0 ; x < n; x++) {
      printf("%lf\n", p6doublefib(x));
    }
  }
}


/**\fn short runProblemFive(char *s)
 *This function determines if the given string
 *is a palindrome (a word that is the same spelled
 *backwards). A single letter IS a palindrome.
 */ 
short runProblemFive(char *s) {
  return p5testPalindrome(s);
}

/**\fn void runProblemTwo()
 *This function takes user input and calculates
 *sales totals.
 */
void runProblemTwo(){
  p2sales();
}


/**
 *\fn void runProblemThree(char* s1, char* s2)
 *This function will take in the two strings
 *and makes a copy of s1 and then compares s1 to
 *s2.
 */
void runProblemThree(char *s1, char *s2) {

  short compare = p3strcmp(s1,s2);

  char *copy = (char*) malloc(sizeof(char));
  p3strcpy(copy, s1);

  if(compare == 0 ){
    printf("%s and %s are equal",s1,s2);
  }
  else if(compare > 0) {
    printf("%s is greater than %s",s1,s2);

  }
  else if(compare < 0) {
    printf("%s is less than %s",s1,s2);
  }

  printf("\nString 1: %s\tMemory Address: %p",s1,s1);
  printf("\nCopy    : %s\tMemory Address: %p",copy,copy);
  printf("\n");
}
