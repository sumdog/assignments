#ifndef THREADDISTRIBUTOR_H
#define THREADDISTRIBUTOR_H
#include "Distribute.hpp"

template <class C>
class ThreadDistributor : public Distributor<C> {
public:
  ThreadDistributor(ComLink<C> *c, unsigned int setsize, char *filename);
private:
  static void* child_thread(void *c);		
};

template <class C>
ThreadDistributor<C>::ThreadDistributor(ComLink<C> *c, unsigned int setsize, char *filename) : Distributor<C>(c,setsize,filename) {

  C Min, Max;
  if(sizeof(C) == sizeof(int64_t)) {
    Min = INT64_MIN;
    Max = INT64_MAX;
  }
  if(sizeof(C) == sizeof(int32_t)) {
    Min = INT32_MIN;
    Max = INT32_MAX;
  }



  srand(time(0));
  pthread_t cthread;
  pthread_create(&cthread,NULL,static_cast<void*(*)(void*)>(child_thread),(void*)this);
  this->com->setSide(PARENT);
  DataSet<C> *ds = new DataSet<C>(Max,Min,this->setsize);
  this->com->setDataSet(ds);
  ds->sortSet();
  this->com->recoverSet();
  ds->printDataSet(this->file);
}

template <class C>
void* ThreadDistributor<C>::child_thread(void *c) {

  C Min, Max;
  if(sizeof(C) == sizeof(int64_t)) {
    Min = INT64_MIN;
    Max = INT64_MAX;
  }
  if(sizeof(C) == sizeof(int32_t)) {
    Min = INT32_MIN;
    Max = INT32_MAX;
  }


  ThreadDistributor<C> *td = (ThreadDistributor<C> *) c;
  td->com->setSide(CHILD);
  DataSet<C> *ds = new DataSet<C>(Max,Min,td->setsize);
  td->com->setDataSet(ds);
  td->com->getDataSet()->sortSet();
  td->com->sendDataSet();
}

#endif /* THREADDISTRIBUTOR_H */
