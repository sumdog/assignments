#include "SodaMachine.hpp"
#include "Soda.hpp"

/**
 *SodaMachine() -- constructs a soda machine
 *
 *  extends a VendingMachine and fills its
 *  items** with various Soda items such as
 *  Sprite, Coke and Water
 */
SodaMachine::SodaMachine() {
  Item **temp = new (Item*)[3];
  temp[0] = new Coke();
  temp[1] = new Sprite();
  temp[2] = new Water();
  
  items->items = &temp[0];
  items->num_items = 3;

  image = "coke.jpg";
}

/**
 *~SodaMachie() -- deconstructs a soda machine
 *
 *  frees memeory allocated to soda machine
 *  and it's items (sodas).
 */
SodaMachine::~SodaMachine() {
  
  Item **temp = items->items;

  delete temp[2];
  delete temp[1];
  delete temp[0];
  delete[] items->items;

}
