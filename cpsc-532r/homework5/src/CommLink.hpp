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
  DataSet<C>* getDataSet() {
    return ds;
  }
  virtual void buildDataSet() = 0;
  virtual void sendDataSet(unsigned int start, unsigned int end) = 0;
protected:
  ComLink();  
  DataSet<C> *ds;
  bool established,data,side;
};

template <class C>
class PipeComLink : public ComLink<C> {
public:
  PipeComLink();
  ~PipeComLink();
  void setSide(ComLinkSide_t c);
  void buildDataSet();
  void sendDataSet(unsigned int start, unsigned int end);

private:
  int tochild[2],fromchild[2];
  ifstream reader;
  ofstream writer;
};


template <class C>
ComLink<C>::ComLink() {

}

template <class C>
void ComLink<C>::setDataSet(DataSet<C> *d) {
   ds = d;
}

template <class C>
void PipeComLink<C>::sendDataSet(unsigned int start, unsigned int end) {
  this->ds->transmitDataSet(&writer,start,end);
}

template <class C>
void PipeComLink<C>::buildDataSet() {
  this->ds = new DataSet<C>(&reader);
  //  this->ds->printDataSet();
}

template <class C>
PipeComLink<C>::PipeComLink() : ComLink<C>() {

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

template <class C>
void PipeComLink<C>::setSide(ComLinkSide_t c) {
  
  switch(c) {
  case PARENT:
    close(tochild[0]);
    close(fromchild[1]);

    FILE *pfo = fdopen(tochild[1],"w");
    stdio_filebuf<char> *pbo = new stdio_filebuf<char>(pfo,std::ios::out);
    writer.std::ios::rdbuf(pbo);

    FILE *pfi = fdopen(fromchild[0],"r");
    stdio_filebuf<char> *pbi = new stdio_filebuf<char>(pfi,std::ios::in);
    reader.std::ios::rdbuf(pbi);

    break;
  case CHILD:
    close(tochild[1]);
    close(fromchild[0]);

    FILE *cfo = fdopen(fromchild[1],"w");
    stdio_filebuf<char> *cbo = new stdio_filebuf<char>(cfo,std::ios::out);
    writer.std::ios::rdbuf(cbo);
    
    
    FILE *cfi = fdopen(tochild[0],"r");
    stdio_filebuf<char> *cbi = new stdio_filebuf<char>(cfi,std::ios::in);
    reader.std::ios::rdbuf(cbi);
    
    break;
  }
}

template <class C>
PipeComLink<C>::~PipeComLink() {
  delete writer;
  delete reader;
  delete this->ds;
}

#endif
