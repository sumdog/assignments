#ifndef VMACHIENE_H
#define VMACHIENE_H
#include "Item.hpp"

enum money { PENNY=1, NICKEL=5, QUARTER=25, DIME=10, HALF_DOLLAR=50, DOLLAR=100 };

class VendingMachine {

public:
  VendingMachine();

  //user functions
  void insertCoin(money m);
  double getCurrentMoney();
  double coinReturn();
  double selectItem(Item e);

  //vending machiene administrator
  double peekMoneyTray();
  double emptyMoneyTray();

protected:
  Item *items;

private:
  double total_money;
  double current_money;
  
};


#endif //VMACHIENE_H
