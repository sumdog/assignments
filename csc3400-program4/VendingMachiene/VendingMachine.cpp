#include "VendingMachine.hpp"

/**
 *VendingMachine() -- constructs a vending machine
 *
 *   do not call this directly. Extend vending machine
 *   first and be sure to add some items in your constructor
 */
VendingMachine::VendingMachine() {

  items = new items_t;
  total_money = 0;
  current_money = 0;
  image = "default.jpg";
}

/**
 *getImage() -- returns image
 *
 *  returns an image for the face of the vending machine
 */
std::string VendingMachine::getImage() {
  return image;
}

/**
 *~VendingMahcine() -- destructs a Vending Machine
 *
 *  frees memeory allocated to the items struct
 */
VendingMachine::~VendingMachine() {
  delete items;
}

/**
 *insertCoin() - inserts a coin in the machine
 *
 *PARMS:       m - an element of the enum type money
 */
void VendingMachine::insertCoin(money m) {
  current_money += m;
}

/**
 *getCurrentMoney() -- gets the current amount of money in machine
 *
 *     returns the amount of money the curent user has inserted
 */
double VendingMachine::getCurrentMoney() {
  return current_money;
}

/**
 *coinReturn() -- returns coins from machine
 *
 *   resets the amount in the machine to zero
 *   and returns coins to user
 */
double VendingMachine::coinReturn() {
  double temp = current_money;
  current_money = 0;
  return temp;
}

/**
 *selectItem() -- selects an Item
 *
 *PARAMS:      e - Item that was selected
 *RETURNS:     double indicating the ammount of change
 *THROWS:      char* if we need more money
 */
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

/**
 *peekMoneyTray() -- shows how much money is in tray
 *
 *RETURNS:        total amount of money gained from
 *                selling Items to users
 */
double VendingMachine::peekMoneyTray() {
  return total_money;
}

/**
 *emptyMoneyTray() -- empties the money try
 *
 *RETURNS:         amount of money in tray fromall
 *                 transactions and then sets that count to zero
 */
double VendingMachine::emptyMoneyTray() {
  double temp = total_money;
  total_money = 0;
  return temp;
}

/**
 *getItems()  -- items currently avaiable in machine
 *
 *RETURNS:    current avaiable items in machiene
 */
items_t VendingMachine::getItems() {
  return *items;
}
