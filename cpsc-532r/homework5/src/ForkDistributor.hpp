#ifndef FORKDISTRIBUTE_H
#define FORKDISTRIBUTE_H

#include <unistd.h>
#include <sys/types.h>

template <class C>
class ForkDistributor : public Distributor<C> {
	public:
		ForkDistributor(ComLink<C> *c, unsigned int setsize);
};



template <class C>
ForkDistributor<C>::ForkDistributor(ComLink<C> *c, unsigned int setsize) : Distributor<C>(c,setsize) {
 if(fork()) {
    this->com->setSide(PARENT);
    DataSet<int32_t> *ds = new DataSet<int32_t>(INT32_MAX,INT32_MIN,setsize);
    this->com->setDataSet(ds);
	ds->printDataSet();
    this->com->sendDataSet(0,setsize);
    //ds->sortSet(0,10);
    //com->recoverSet(11,20);
 }
  else {
    this->com->setSide(CHILD);
	DataSet<int32_t> *ds = new DataSet<int32_t>(INT32_MAX,INT32_MIN,setsize);
	//this->com->setDataSet(ds);
    this->com->buildDataSet();
	this->com->getDataSet()->printDataSet();
    //com->getDataSet()->printDataSet();
    //com->getDataSet()->sortSet(0,10);
    //com->sendDataSet(0,10);
	 
 }
}

#endif /* FORKDISTRIBUTE_H */
