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
  std::string getName();
};




#endif /* ITEM_H */
