#ifndef ITEMCOMM_H
#define ITEMCOMM_H

class ItemComm {

public:
  virtual double buyItem(double price) = 0;
  virtual void insertMoney(double amount) = 0;

};


#endif //ITEMCOMM_H
