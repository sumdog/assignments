#ifndef PIPECOMLINK_H
#define PIPECOMLINK_H
#include "CommLink.hpp"

template <class C>
class PipeComLink : public ComLink<C> {
public:
  PipeComLink();
  ~PipeComLink();
  void setSide(ComLinkSide_t c);

private:
  int tochild[2],fromchild[2];
};



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

    this->fout = fdopen(tochild[1],"w");
    this->fin = fdopen(fromchild[0],"r");

    break;
  case CHILD:
    close(tochild[1]);
    close(fromchild[0]);

    this->fout = fdopen(fromchild[1],"w");
    this->fin = fdopen(tochild[0],"r");
    
    break;
  }
}

template <class C>
PipeComLink<C>::~PipeComLink() {

}

#endif /* PIPECOMLINK_H */
