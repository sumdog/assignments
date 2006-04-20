#ifndef COMLINK_H
#define COMLINK_H
#include <unistd.h>
#include "DataSet.hpp"


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
