#ifndef DISTRIBUTE_H
#define DISTRIBUTE_H


template <class C>
class Distributor {
public:
  Distributor(ComLink<C> *c,unsigned int setsize,char *filename);
  ~Distributor();
protected:
  unsigned int setsize;
  ComLink<C> *com;	
  char *file;
};

template <class C>
Distributor<C>::Distributor(ComLink<C> *c, unsigned int size, char *filename) {
  com = c;
  setsize = size;
  file = filename;
}

template <class C>
Distributor<C>::~Distributor() {
}



#endif  /* DISTRIBUTE_H */
