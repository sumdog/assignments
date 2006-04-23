#ifndef DATASET_H
#define DATASET_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

template <class T>
class DataSet {
public:
  DataSet(T max, T min, unsigned int size);
  DataSet(ifstream *stream);
  void transmitDataSet(ofstream *stream, unsigned int start, unsigned int end);
  ~DataSet();
  void printDataSet();
  void sortSet(unsigned int start, unsigned int end) {
    qsort(&set[start],(end-start),sizeof(T),sortCmp);
  }
  void recollectset(ifstream *stream) {
    unsigned int insize;
    stream >> insize;
    /*    T *newset = new T[insize+this->setsize];
    for(unsigned int l=0, unsigned int r=0;
	l < this->setsize || r < this->setsize;
	) {
      
	}*/
  }
  
private:
  T max;
  T min;
  T *set;
  unsigned int setsize;
  static int sortCmp(const void* a, const void*b) {
    //    return  (*((*T)a) - *((*T)b) );
    if (*(T*)a > *(T*)b ) {
      return 1;
    }
    else if (*(T*)a < *(T*)b ) {
      return -1;
    }
    else {
      return 0;
    }
  }
};

template <class T>
DataSet<T>::DataSet(ifstream *stream) {

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
  *stream << (end-start) << endl;

  /* send data */
  for(unsigned int x=start; x<end && x<setsize; x++) {
    *stream << set[x] << endl;
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
#endif /* DATASET_H */
