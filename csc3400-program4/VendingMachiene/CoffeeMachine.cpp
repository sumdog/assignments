#include "CoffeeMachine.hpp"
#include "Coffee.hpp"

/**
 *CoffeeMachine() -- constructs a coffee machine
 *
 *  extends a VendingMachine and fills its
 *  items** with various Coffee items
 */
CoffeeMachine::CoffeeMachine() {
  Item **temp = new (Item*)[3];
  temp[0] = new Coffee();
  temp[1] = new Decaff();
  temp[2] = new Expresso();
  
  items->items = &temp[0];
  items->num_items = 3;

  image = "coffee.gif";
}

/**
 *~CoffeeMachie() -- deconstructs a coffee machine
 *
 *  frees memeory allocated to coffee machine
 *  and it's items (sodas).
 */
CoffeeMachine::~CoffeeMachine() {
  
  Item **temp = items->items;

  delete temp[2];
  delete temp[1];
  delete temp[0];
  delete[] items->items;

}
