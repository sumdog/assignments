#ifndef FORKDISTRIBUTE_H
#define FORKDISTRIBUTE_H

#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

template <class C>
class ForkDistributor : public Distributor<C> {
public:
  ForkDistributor(ComLink<C> *c, unsigned int setsize);
};



template <class C>
ForkDistributor<C>::ForkDistributor(ComLink<C> *c, unsigned int setsize) : Distributor<C>(c,setsize) {
  if(fork()) {
     
    srand(time(0));
     
    this->com->setSide(PARENT);
    DataSet<int32_t> *ds = new DataSet<int32_t>(INT32_MAX,INT32_MIN,setsize);
    this->com->setDataSet(ds);
    ds->sortSet();
    this->com->recoverSet();
    ds->printDataSet();
  }
  else {
      
    srand(time(0)+1000);
    this->com->setSide(CHILD);
    DataSet<int32_t> *ds = new DataSet<int32_t>(INT32_MAX,INT32_MIN,setsize);
    this->com->setDataSet(ds);
    this->com->getDataSet()->sortSet();
    this->com->sendDataSet(); 
  }
}

#endif /* FORKDISTRIBUTE_H */
