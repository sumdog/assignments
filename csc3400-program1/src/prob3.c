/**\file prob3.c
 *Functions for problem 3: homebrewn 
 *string comparison and copy function
 */
#include "prob3.h"

/**
 *\fn short p3strcmp(const char *a, const char *b)
 *Compares string a to string b
 */
short p3strcmp(const char *a, const char *b) {
  short retval = 0;
  while( 1 ) {
    if(*a == '\0' && *b == '\0') { //equal string and length
      retval = 0;
      break;
    }
    if(*a == '\0' && *b != '\0') { //b is shorter than a
      retval -1;
      break;
    }
    if(*a != '\0' && *b == '\0') {
      retval = 1;
      break;
    }
    if(*a < *b ) {
      retval = 1; 
      break;
    }
    if(*b < *a ) {
      retval = -1;
      break;
    }
    if( *a == *b ) { //go to the next char
      a++;
      b++;
    }
  }
  return retval;
}

/**
 *\fn void p3strcpy(char *to, char *from)
 *Copies a string from one pointer into another.
 *Make sure you have memory allocated for both pointers.
 */
void p3strcpy(char *to, char *from) {
  //while there's still more to copy
  while(*from != '\0') {
    *to = *from;
    to++;
    from++;
  }
  //null terminate the string
  *to++ = '\0';
}
