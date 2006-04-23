#ifndef PIPECOMLINK_H
#define PIPECOMLINK_H
#include "CommLink.hpp"

template <class C>
class PipeComLink : public ComLink<C> {
public:
  PipeComLink();
  ~PipeComLink();
  void setSide(ComLinkSide_t c);
  //void buildDataSet();
  //void sendDataSet(unsigned int start, unsigned int end);

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

    FILE *pfo = fdopen(tochild[1],"w");
    this->stdfbo = new stdio_filebuf<char>(pfo,std::ios::out);
    this->writer.std::ios::rdbuf(this->stdfbo);

    FILE *pfi = fdopen(fromchild[0],"r");
    this->stdfbi = new stdio_filebuf<char>(pfi,std::ios::in);
    this->reader.std::ios::rdbuf(this->stdfbi);

    break;
  case CHILD:
    close(tochild[1]);
    close(fromchild[0]);

    FILE *cfo = fdopen(fromchild[1],"w");
    this->stdfbo = new stdio_filebuf<char>(cfo,std::ios::out);
    this->writer.std::ios::rdbuf(this->stdfbo);
    
    
    FILE *cfi = fdopen(tochild[0],"r");
    this->stdfbi = new stdio_filebuf<char>(cfi,std::ios::in);
    this->reader.std::ios::rdbuf(this->stdfbi);
    
    break;
  }
}

template <class C>
PipeComLink<C>::~PipeComLink() {
  //delete this->writer;
  //delete this->reader;
  delete this->stdfbi;
  delete this->stdfbo;
  delete this->ds;
}

#endif /* PIPECOMLINK_H */
