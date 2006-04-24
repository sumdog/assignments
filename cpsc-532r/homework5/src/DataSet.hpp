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
  void transmitDataSet(FILE *stream);
  ~DataSet();
  void printDataSet();
  void printDataSet(char *file);
  void sortSet();
  void recollectSet(FILE *stream);
  
private:
  T max;
  T min;
  T *set;
  unsigned int setsize;
  static int sortCmp(const void* a, const void*b) {
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
void DataSet<T>::sortSet() {
  qsort(&set[0],setsize,sizeof(T),sortCmp);
}

template <class T>
void DataSet<T>::recollectSet(FILE *stream) {
  char buffer[128];
  unsigned int insize;

  fgets(&buffer[0],128,stream);
  insize = strtoul(&buffer[0],NULL,0);

  
  T *newset = new T[setsize+insize];
  T curin;
  fgets(&buffer[0],127,stream);
  if(sizeof(T) == sizeof(int32_t)) {
    curin = atol(&buffer[0]);
  }
  if(sizeof(T) == sizeof(int64_t)) {
    curin = atoll(&buffer[0]);
  }
  
  unsigned int localset = 0;
  unsigned int remoteset = 0;
  for(unsigned int x=0; x < setsize+insize; x++) {
    if( curin >= set[localset] ){
      newset[x] = set[localset];
      if(localset < setsize-1) {
	localset++;
      }
      
    }
    else if ( curin < set[localset] ) {
      newset[x] = curin;
      if(remoteset < insize) {
	fgets(&buffer[0],128,stream);  
	if(sizeof(T) == sizeof(int32_t)) {
	  curin = atol(&buffer[0]);
	}
	if(sizeof(T) == sizeof(int64_t)) {
	  curin = atoll(&buffer[0]);
	}
	remoteset++;

      }
      
    }
  }
  
  delete[] set;
  set = newset;
  setsize = setsize + insize;
  
}

template <class T>
void DataSet<T>::transmitDataSet(FILE *stream) {

  fprintf(stream,"%u\n",setsize);
  
  /* send data */
  for(unsigned int x=0; x<setsize; x++) {
    if(sizeof(T) == sizeof(int32_t)) {
      fprintf(stream,"%d\n",set[x]);
    }
    if(sizeof(T) == sizeof(int64_t)) {
      fprintf(stream,"%lld\n",set[x]);
    }
  }
  
}


template <class T>
DataSet<T>::DataSet(T mx, T mn, unsigned int size) {
  max = mx;
  min = mn;
  set = new T[size];
  setsize = size;
  
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
void DataSet<T>::printDataSet(char *file) {
  FILE *stream = fopen(file,"w");
  for(unsigned int x=0; x<setsize; x++) {
    if(sizeof(T) == sizeof(int32_t) ){
      fprintf(stream,"%u:\t%d\n",x,set[x]);
    }
    if(sizeof(T) == sizeof(int64_t) ) {
      fprintf(stream,"%u\t%lld\n",x,set[x]);
    }
  }
  fclose(stream);
}

template <class T>
DataSet<T>::~DataSet() {
  delete[] set;
}
#endif /* DATASET_H */
