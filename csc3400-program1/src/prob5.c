/**\file prob5.c
 *This file contains the functions needed
 *for problem 5, the palindrome test. This test will
 *also remove all spaces an puncuation (ASCII values
 *between 65 and 122).
 */
#include "prob5.h"
#include <string.h>

/**\fn short p5testPalindrome(char* s)
 *Checks to see if null terminated string is
 *a palindrone. Also skips over puncuation
 *and invalid characters (ASCII 0 to 65 and
 *122 to 127).
 */
short p5testPalindrome(char* s) {
    printf("");
  //loops to check the beginng and end
  //for "bad char" (spaces, puncuation, etc)
  while(1) {
    if ( ((int) *s) < 65 || ((int) *s) > 122 ) {
      s++;
    }
    else {
      break;
    }
  }
  while(1) {
    if( strlen(s) == 1 ) {
      break;
    }
    else if ( ((int) s[strlen(s)-1]) < 65 || ((int) s[strlen(s)-1]) > 122 ) {
      s[strlen(s)-1] = '\0';
    }
    else {
      break;
    }
  }
  if( strlen(s) <= 1) { //base case
    return 1;
  }
  else if( *s == s[strlen(s)-1]) {
    s[strlen(s)-1] = '\0';
    s++;
    //start recursive calls
    return p5testPalindrome(s);
  }
  else { //did not reach base case
    return 0;
  }
  
}
