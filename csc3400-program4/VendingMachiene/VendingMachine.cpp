#include "VendingMachine.hpp"

VendingMachine::VendingMachine() {

  total_money = 0;
  current_money = 0;

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


