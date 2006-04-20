#ifndef COMLINK_H
#define COMLINK_H
#include "DataSet.hpp"

typedef enum ComLinkSide { PARENT = 0, CHILD = 1  } ComLinkSide_t;

class ComLink {

public:
  virtual void setSide(ComLinkSide_t c) = 0;

protected:
  ComLink(DataSet *data);  
  DataSet *ds;
};


class PipeComLink : public ComLink {
public:
  PipeComLink(DataSet *data);
  ~PipeComLink();
  void setSide(ComLinkSide_t c);
private:
  int tochild[2],fromchild[2];
  ifstream *reader;
  ofstream *writer;
};



#endif
