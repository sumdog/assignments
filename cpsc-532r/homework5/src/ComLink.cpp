#include <unistd.h>
#include "ComLink.hpp"

ComLink::ComLink(DataSet *data) {
  ds = data;
}

PipeComLink::PipeComLink(DataSet *data) : ComLink(data) {

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

PipeComLink::~PipComLink() {
  delete writer;
  delete reader;
}
