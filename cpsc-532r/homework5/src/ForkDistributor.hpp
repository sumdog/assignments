#ifndef FORKDISTRIBUTE_H
#define FORKDISTRIBUTE_H

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
using std::cout;

template <class C>
class ForkDistributor : public Distributor<C> {
public:
  ForkDistributor(ComLink<C> *c, unsigned int setsize, char *filename);
};



template <class C>
ForkDistributor<C>::ForkDistributor(ComLink<C> *c, unsigned int setsize, char *filename) : Distributor<C>(c,setsize,filename) {

  C Min, Max;
  if(sizeof(C) == sizeof(int64_t)) {
    Min = INT64_MIN;
    Max = INT64_MAX;
  }
  if(sizeof(C) == sizeof(int32_t)) {
    Min = INT32_MIN;
    Max = INT32_MAX;
  }

  if(fork()) {
     
    srand(time(0));
     
    this->com->setSide(PARENT);

    DataSet<C> *ds = new DataSet<C>(Max,Min,setsize);

    this->com->setDataSet(ds);
    time_t start = time(0);
    ds->sortSet();
    this->com->recoverSet();
    time_t end = time(0);
    cout << "Time Elapsed(fork):" << end-start << " sec\n" << std::flush;
    ds->printDataSet(this->file);
  }
  else {
      
    srand(time(0)+1000);
    this->com->setSide(CHILD);

    DataSet<C> *ds = new DataSet<C>(Max,Min,setsize);

    this->com->setDataSet(ds);
    this->com->getDataSet()->sortSet();
    this->com->sendDataSet(); 
  }
}

#endif /* FORKDISTRIBUTE_H */
