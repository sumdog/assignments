#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item {

private:
  double price;
  std::string *name;

public:
  Item(double price, std::string name);
  ~Item();
  double getPrice();

};


class Coke :  public Item {

public:
  Coke() : Item(1.00,std::string("Coke")) {}

};

#endif /* ITEM_H */
