#ifndef COMLINK_H
#define COMLINK_H
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <ext/stdio_filebuf.h>
#include "DataSet.hpp"
using std::ifstream;
using std::ofstream;
using __gnu_cxx::stdio_filebuf;

typedef enum ComLinkSide { PARENT = 0, CHILD = 1  } ComLinkSide_t;

template <class C>
class ComLink {
  
public:
  virtual void setSide(ComLinkSide_t c) = 0;
  void setDataSet(DataSet<C> *d);
  DataSet<C>* getDataSet();
  void sendDataSet();
  virtual void recoverSet();
protected:
  DataSet<C> *ds;
  FILE *fin;
  FILE *fout;
};


template <class C>
void ComLink<C>::sendDataSet() {
  ds->transmitDataSet(fout);
}


template <class C>
void ComLink<C>::recoverSet() {
  ds->recollectSet(fin);
}

template <class C>
DataSet<C>* ComLink<C>::getDataSet() {
  return ds;
}

template <class C>
void ComLink<C>::setDataSet(DataSet<C> *d) {
   ds = d;
}



#endif
