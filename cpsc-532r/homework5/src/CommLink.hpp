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
  void buildDataSet();
  void sendDataSet(unsigned int start, unsigned int end);
  virtual void recoverSet(unsigned int start, unsigned int end);
protected:
  DataSet<C> *ds;
  bool established,data,side;
  ifstream reader;
  ofstream writer;
  stdio_filebuf<char> *stdfbi;
  stdio_filebuf<char> *stdfbo;
};


template <class C>
void ComLink<C>::sendDataSet(unsigned int start, unsigned int end) {
  ds->transmitDataSet(&writer,start,end);
}

template <class C>
void ComLink<C>::buildDataSet() {
  ds = new DataSet<C>(&reader);
}

template <class C>
void ComLink<C>::recoverSet(unsigned int start, unsigned int end) {
	ds->recollectSet(start,end,&reader);
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
