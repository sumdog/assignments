#include "Item.hpp"


Item::Item(double price, std::string name) {
  this->price = price;
  this->name = new std::string(name);
}

Item::~Item() {
  delete name;
}

double Item::getPrice() {
  return price;
}


