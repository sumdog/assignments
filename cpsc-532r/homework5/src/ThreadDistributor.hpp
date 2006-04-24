#ifndef THREADDISTRIBUTOR_H
#define THREADDISTRIBUTOR_H
#include "Distribute.hpp"

template <class C>
class ThreadDistributor : public Distributor<C> {
public:
  ThreadDistributor(ComLink<C> *c, unsigned int setsize);
private:
  static void* child_thread(void *c);		
};

template <class C>
ThreadDistributor<C>::ThreadDistributor(ComLink<C> *c, unsigned int setsize) : Distributor<C>(c,setsize) {
  pthread_t cthread;
  pthread_create(&cthread,NULL,static_cast<void*(*)(void*)>(child_thread),(void*)this);
  this->com->setSide(PARENT);
  DataSet<int32_t> *ds = new DataSet<int32_t>(INT32_MAX,INT32_MIN,this->setsize);
  this->com->setDataSet(ds);
  ds->printDataSet();	
	
}

template <class C>
void* ThreadDistributor<C>::child_thread(void *c) {
  ThreadDistributor<C> *td = (ThreadDistributor<C> *) c;
  td->com->setSide(CHILD);
  DataSet<int32_t> *ds = new DataSet<int32_t>(INT32_MAX,INT32_MIN,td->setsize);
  td->com->setDataSet(ds);
  ds->printDataSet();
}

#endif /* THREADDISTRIBUTOR_H */
