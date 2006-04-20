#ifndef DISTRIBUTE_H
#define DISTRIBUTE_H

typedef enum commember { PARENT, CHILD } AS commember_t;

template <class C>
Class Communicator {
	public:
	  Communicator();
	  ~Communicator();
	  setDestination(commember_t t);
	  sendChunk(C *data, unsigned int size);
	  
}


template <class T>
Class Seperator {
	public:
	  Seperator(T *data, unsigned int size, unsigned int procs, Communicator *com);
	  ~Seperator();
	  virtual void spawn();

	private:
	  T *data;
	  unsigned int size;
	  unsigned int procs;
	  Communicator *com
}


template <class T>
Seperator<T>::Seperator(T *data, unsigned int size, unsigned int procs, Communicator *com) {
	this->data  = data;
	this->size  = size;
	this->procs = procs;
	this->com = com;
}

template<class t>
Seperator<T>::~Seperator() {
}

template<class t>
Seperator<T>::spawn() {
}


#endif  /* DISTRIBUTE_H */
