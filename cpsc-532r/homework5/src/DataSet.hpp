#ifndef DATASET_H
#define DATASET_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define IO_BUFFER_SIZE 1024
using std::cout;
using std::endl;

template <class T>
class DataSet {
public:
  DataSet(T max, T min, unsigned int size);
  DataSet(T man, T min, FILE *stream);
  void transmitDataSet(FILE *stream, unsigned int start, unsigned int end);
  ~DataSet();
  void printDataSet();
  
private:
  T max;
  T min;
  T *set;
  unsigned int setsize;
};

template <class T>
DataSet<T>::DataSet(T mx, T mn, FILE *stream) {
  max = mx;
  min = mn;
 
  /* get size of dataset */
  char *ibuf = new char[IO_BUFFER_SIZE+1];
  fgets(ibuf,IO_BUFFER_SIZE,stream);
  setsize = strtoul(ibuf, NULL, 10);
  set = new T[setsize];
  
  /* load set data */
  for(unsigned int x=0; x< setsize; x++) {
    fgets(ibuf,IO_BUFFER_SIZE,stream);
    set[x] = strtoul(ibuf,NULL,10);
  }

  /* clean up */
  delete[] ibuf;
}

template <class T>
void DataSet<T>::transmitDataSet(FILE *stream, unsigned int start, unsigned int end) {
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
#endif /* DATASET_H */
