#include "SodaMachine.hpp"
#include "Soda.hpp"

SodaMachine::SodaMachine() {
  Item **temp = new (Item*)[3];
  temp[0] = new Coke();
  temp[1] = new Sprite();
  temp[2] = new Water();
  
  items->items = &temp[0];
  items->num_items = 3;
}

SodaMachine::~SodaMachine() {
  
  Item **temp = items->items;

  delete temp[2];
  delete temp[1];
  delete temp[0];
  delete[] items->items;

}
