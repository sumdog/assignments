#include "Item.hpp"

/**
 *Item()  -- constructs a vending machine item
 *
 *PARMS:    price - cost of item
 *          name  - name of item
 */
Item::Item(double price, std::string name) {
  this->price = price;
  this->name = new std::string(name);
}


/**
 *~Item() -- destructs Item
 *
 *       deallocates memory allocated for name
 */
Item::~Item() {
  delete name;
}

/**
 *getPrint() -- returns price of item
 */
double Item::getPrice() {
  return price;
}

/**
 *getName() -- returns name of item
 */
std::string Item::getName() {
  return *name;
}
