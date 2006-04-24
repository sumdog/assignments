#ifndef DISTRIBUTE_H
#define DISTRIBUTE_H


template <class C>
class Distributor {
	public:
		Distributor(ComLink<C> *c,unsigned int setsize);
		~Distributor();
	protected:
		unsigned int setsize;
		ComLink<C> *com;	
	  
};

template <class C>
Distributor<C>::Distributor(ComLink<C> *c, unsigned int size) {
	com = c;
	setsize = size;
}

template <class C>
Distributor<C>::~Distributor() {
}



#endif  /* DISTRIBUTE_H */
