/*********************************
 *  Items for Coffee Machine
 *********************************/

#ifndef COFFEE_H
#define COFFEE_H
#include "Item.hpp"


class Coffee : public Item {
public:
  Coffee();
};

class Decaff : public Item {
public:
  Decaff();
};

class Expresso : public Item {
public:
  Expresso();
};


#endif // COFFEE_H
