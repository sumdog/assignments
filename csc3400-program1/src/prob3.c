#include "prob3.h"

short p3strcmp(const char *a, const char *b) {
  short retval = 0;
  while( *a != *b ) {
    if(*a == '\0' ) { //
    }
}

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
