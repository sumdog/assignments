#ifndef INT_H
#define INT_H
#include <stdlib.h>
#define __STDC_LIMIT_MACROS
#include <stdint.h>

class Integer {

public:
  /*
  virtual friend bool operator<(Integer a,Integer b) = 0;
  virtual friend bool operator>(Integer a,Integer b) = 0;
  virtual friend bool operator<=(Integer a,Integer b) = 0;
  virtual friend bool operator>=(Integer a,Integer b) = 0 ;
  virtual friend bool operator==(Integer a, Integer b) = 0;
  */
protected:
  Integer(size_t varsize, bool signedval);
  ~Integer();
  void *data;
  virtual void generateRandom(bool signedval) = 0;

};

class Int32 : public Integer {
public:
  Int32(bool signedval);
  ~Int32();
protected:
  void generateRandom(bool signedval);
  
};

class Int64 : public Integer {
public:
  Int64(bool signedval);
  ~Int64();
protected:
  void generateRandom(bool signedval);
};



#endif /* INT_H */
