#include "VendingMachine.hpp"

VendingMachine::VendingMachine() {

  items = new items_t;
  total_money = 0;
  current_money = 0;

}

VendingMachine::~VendingMachine() {
  delete items;
}

void VendingMachine::insertCoin(money m) {
  current_money += m;
}

double VendingMachine::getCurrentMoney() {
  return current_money;
}

double VendingMachine::coinReturn() {
  double temp = current_money;
  current_money = 0;
  return temp;
}

double VendingMachine::selectItem(Item e) {
  if( e.getPrice() < current_money ) {
    throw "Need More Money";
  }
  else {
    double change = current_money - e.getPrice();
    total_money += e.getPrice();
    current_money = 0;
    return change;
  }
}

double VendingMachine::peekMoneyTray() {
  return total_money;
}

double VendingMachine::emptyMoneyTray() {
  double temp = total_money;
  total_money = 0;
  return temp;
}

items_t VendingMachine::getItems() {
  return *items;
}
