#ifndef VMACHIENE_H
#define VMACHIENE_H


enum money { PENNY=1, NICKEL=5, QUARTER=25, DIME=10, HALF_DOLLAR=50, DOLLAR=100 };

class VendingMachine {

public:
  VendingMachine();
  void insertCoin(money m);
  double getCurrentMoney();
  double coinReturn();


protected:
  double total_money;
  double current_money;
  
};


#endif
