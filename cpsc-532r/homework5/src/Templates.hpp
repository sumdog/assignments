#ifndef DATASET_H
#define DATASET_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

template <class T>
class DataSet {
public:
  DataSet(T max, T min, unsigned int size);
  DataSet(T man, T min, ifstream *stream);
  void transmitDataSet(ofstream *stream, unsigned int start, unsigned int end);
  ~DataSet();
  void printDataSet();
  
private:
  T max;
  T min;
  T *set;
  unsigned int setsize;
};

template <class T>
DataSet<T>::DataSet(T mx, T mn, ifstream *stream) {
  max = mx;
  min = mn;

  /* get size of dataset */  
  *stream >> setsize;
  set = new T[setsize];

  /* load set data */
  for(unsigned int x=0; x< setsize; x++) {
    *stream >>set[x]; 
  }
}

template <class T>
void DataSet<T>::transmitDataSet(ofstream *stream, unsigned int start, unsigned int end) {
  
  /* send size of set */
  *stream << (start - end) << endl;

  /* send data */
  for(unsigned int x=start; x<end && x<setsize; x++) {
    stream << set[x] << endl;
  }
}


template <class T>
DataSet<T>::DataSet(T mx, T mn, unsigned int size) {
  max = mx;
  min = mn;
  set = new T[size];
  setsize = size;
  srand(time(0));
  for(unsigned int i=0; i<size; i++) {
    set[i] = (T) (mx * ((float)rand() / (float) (RAND_MAX)));
    /* if unsigned, randomly negate */
    if(mn < 0) {
      if((rand()%2)) {
        set[i] = set[i] * -1;
      }
    }
  }
}

template <class T>
void DataSet<T>::printDataSet() {
  for(unsigned int x=0; x<setsize; x++) {
    cout << x << ":\t" << set[x] << endl;
  }
}

template <class T>
DataSet<T>::~DataSet() {
  delete[] set;
}


typedef enum ComLinkSide { PARENT = 0, CHILD = 1  } ComLinkSide_t;

template <class C>
class ComLink {

public:
  virtual void setSide(ComLinkSide_t c) = 0;

protected:
  ComLink(DataSet<C> *data);  
  DataSet *ds;
};

template <class D>
class PipeComLink : public ComLink {
public:
  PipeComLink(DataSet<D> *data);
  ~PipeComLink();
  void setSide(ComLinkSide_t c);
private:
  int tochild[2],fromchild[2];
  ifstream *reader;
  ofstream *writer;
};


template <class C>
ComLink::ComLink(DataSet<C> *data) {
  ds = data;
}

template <class D>
PipeComLink::PipeComLink(DataSet<D> *data) : ComLink(data) {

  /* establish 2 way pipes */
  if(pipe(tochild)) {
    perror("pipe");
    exit(2);
  }
  if(pipe(fromchild)) {
    perror("pipe");
    exit(3);
  }
  
}

template <class D>
PipeComLink::setSide(ComLinkSide_t c) {
  switch(c) {
  case PARENT:
    close(tochild[0]);
    close(fromchild[1]);
    
    writer = new ifstream(tochild[1]);
    reader = new ofstream(fromchild[0]);

    break;
  case CHILD:
    close(tochild[1]);
    close(fromchild[0]);

    writer = new ifstream(fromchild[1]);
    reader = new ofstream(tochild[0]);
    
    break;
  }
}

template <class D>
PipeComLink::~PipComLink() {
  delete writer;
  delete reader;
}


#endif
