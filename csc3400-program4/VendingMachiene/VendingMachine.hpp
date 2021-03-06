#ifndef VMACHIENE_H
#define VMACHIENE_H
#include "Item.hpp"
#include <string>

enum money { PENNY=1, NICKEL=5, QUARTER=25, DIME=10, HALF_DOLLAR=50, DOLLAR=100 };

class VendingMachine {

protected:
  VendingMachine();


public:
  virtual ~VendingMachine();
  std::string getImage();

  //user functions
  void insertCoin(money m);
  double getCurrentMoney();
  double coinReturn();
  double selectItem(Item e);
  items_t getItems();

  //vending machiene administrator
  double peekMoneyTray();
  double emptyMoneyTray();

protected:
  items_t *items;
  std::string image;

private:
  double total_money;
  double current_money;
  
};


#endif //VMACHIENE_H
