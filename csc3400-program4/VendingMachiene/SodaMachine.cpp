#include "SodaMachine.hpp"
#include "Soda.hpp"

SodaMachine::SodaMachine() {
  items = new (Item*)[3];
  items[0] = new Coke();
  items[1] = new Sprite();
  items[2] = new Water();
}

SodaMachine::~SodaMachine() {
  delete items[2];
  delete items[1];
  delete items[0];
  delete[] items;

}
