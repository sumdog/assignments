#include "Int.hpp"
#include "stdlib.h"

Integer::Integer(size_t varsize, bool signedval) {

  /* yea yea, I know..using malloc in C++, but
   * the new keyword needs a type. We just have a 
   * size of a type
   */
  data = malloc(varsize);
}

Integer::~Integer() {
  free(data);
}


Int32::Int32(bool signedval) : Integer(sizeof(int32_t),signedval) {
  
}

Int32::~Int32() {

}

void Int32::generateRandom(bool signedval) {

  int32_t *cdata = static_cast<int32_t*>(data);

  *cdata = (INT32_MAX * ((float)rand() / (float) (RAND_MAX)));
  if(signedval) {
    if((rand()%2)) {
      *cdata = *cdata * -1;
    }
  }
}

Int64::Int64(bool signedval) : Integer(sizeof(int64_t),signedval) {
}

Int64::~Int64() {
}

void Int64::generateRandom(bool signedval) {

  int64_t *cdata = static_cast<int64_t*>(data);
  
  *cdata = (INT64_MAX * ((float)rand() / (float) (RAND_MAX)));
  if(signedval) {
    if((rand()%2)) {
      *cdata = *cdata * -1;
    }
  }
}
